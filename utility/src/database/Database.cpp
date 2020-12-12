#include <Database/Database.h>
#include <Database/ColumnDefinition.h>
#include <Database/DatabaseColumnDict.h>

#include <filesystem>

// ***************** DatabaseInsertQuery *****************

DatabaseInsertQuery::DatabaseInsertQuery()
{
    
}

DatabaseInsertQuery::~DatabaseInsertQuery()
{
    
}

void DatabaseInsertQuery::clear()
{
    m_tableName.clear();
    m_colDefMap = nullptr;

    clearForNewQuery();
}

void DatabaseInsertQuery::clearForNewQuery()
{
    m_colValueList.clear();
    m_colNameList.clear();

    m_query.clear();
}

void DatabaseInsertQuery::newQuery(const std::string& tableName, const std::map<uint32_t, std::string>& columnDefMap)
{
    clear();

    m_tableName = tableName;
    m_colDefMap = &columnDefMap;
}

void DatabaseInsertQuery::addStringColumnValue(uint32_t columnIndex, const std::string& value)
{
    string inputCopy;

    for(size_t index {0}; index < value.size(); ++index)
    {
        char c = value.at(index);
            
        inputCopy += c;

        if(c == '\'')
            inputCopy += '\'';
    }

    m_colValueList.push_back(inputCopy);

    auto iter = m_colDefMap->find(columnIndex);

    if (iter != m_colDefMap->cend())
        m_colNameList.push_back(iter->second);
    else
        m_colNameList.push_back(std::string("--ColumnMissing--"));
}

void DatabaseInsertQuery::addCXStringColumnValue( uint32_t columnIndex, const CXString& value)
{
    string str("-NULL-");

    if(value.data)
    {
        str = clang_getCString(value);
        clang_disposeString(value);
    }

    addStringColumnValue(columnIndex, str);
}

std::string& DatabaseInsertQuery::buildQuery()
{
    m_query.clear();

    if(m_colNameList.size() == m_colValueList.size())
    if(!m_tableName.empty())
    {
        m_query += "INSERT INTO \'" + m_tableName + "\' ("; 

        auto colNameIter = m_colNameList.cbegin();
        bool iteratorCompare = colNameIter != m_colNameList.cend();

        while( iteratorCompare)
        {
            m_query += *colNameIter;

            ++colNameIter;
            if(iteratorCompare = (colNameIter != m_colNameList.cend()))
                m_query += ", ";
        }

        m_query += ") VALUES (";

        auto colValueIter = m_colValueList.cbegin();
        iteratorCompare = colValueIter != m_colValueList.cend();

        while( iteratorCompare)
        {
            m_query += '\'' + *colValueIter + '\'';

            ++colValueIter;
            if(iteratorCompare = (colValueIter != m_colValueList.cend()))
                m_query += ", ";
        }

        m_query += ");";
    }

    return m_query;
}

// *********************** Database ***********************

Database::Database(const std::string& databasePath) :
    m_databasePath(databasePath)
{
    createGlobalTableTemplateQuery();
    createFileListTableTemplateQuery();
    createTokenTableTemplateQuery();
}

Database::~Database()
{
    if(m_databaseOptions & DUMP_QUERIES_TO_FILE)
    if(m_dumpQueryFile.is_open())
        m_dumpQueryFile.close();

    sqlite3_close(m_database);
}

void Database::openDatabase(uint32_t databaseOptions)
{
    if(m_databasePath.empty())
        return;

    if(databaseOptions == 0)
        return;

    m_databaseOptions = databaseOptions;

    const bool    inMemory    = m_databaseOptions & DatabaseOptions::IN_MEMORY_DB_FILE;

    const bool    readOnly    = m_databaseOptions & DatabaseOptions::READONLY_DB_FILE;
    const bool    readWrite   = m_databaseOptions & DatabaseOptions::READ_WRITE_DB_FILE;

    const int32_t sqliteFlags =  (readOnly  ? SQLITE_OPEN_READONLY : (readWrite ? (SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE) : 0)) | 
                                 (inMemory  ? SQLITE_OPEN_MEMORY : 0);

    const std::filesystem::path path(m_databasePath);

    if (std::filesystem::exists(path))
    {
        if(m_databaseOptions & TRUNCATE_DB_FILE)
        {
            if(std::filesystem::is_regular_file(path))
                std::filesystem::remove(path);
        }
    }

    m_lastError = sqlite3_open_v2(
                                    m_databasePath.c_str(), 
                                    &m_database, 
                                    sqliteFlags, 
                                    nullptr
                                 );

    if(m_databaseOptions & DUMP_QUERIES_TO_FILE)
        m_dumpQueryFile.open("dumpQueries.txt", std::ios::out | std::ios::trunc);
}

void Database::createGlobalTableTemplateQuery()
{
    m_globalTableTemplateQuery =
    {
        "CREATE TABLE \'..\\global\'"
        "("
            "ClangVersion VARCHAR(255),"
            "AppName VARCHAR(255),"
            "AppVersion VARCHAR(255)"
        ");"
    };
}

void Database::createFileListTableTemplateQuery()
{
    m_fileListTableTemplateQuery =
    {
        "CREATE TABLE \'..\\file_list\'"
        "("
            "FileListID INT PRIMARY KEY,"
            "FileListFileName VARCHAR(255)"
        ");"
    };
}

void Database::createTokenTableTemplateQuery()
{
    m_tokenTableTemplateQuery =
    {
        "CREATE TABLE \"<?filePath?>\\tokens\""
        "("
            "TokenID INT PRIMARY KEY,"
            "TokenKind TINYINT NOT NULL,"
            "TokenSpelling VARCHAR(255) NOT NULL,"
            "TokenStartPos_Line BIGINT NOT NULL,"
            "TokenStartPos_Col BIGINT NOT NULL,"
            "TokenEndPos_Line BIGINT NOT NULL,"
            "TokenEndPos_Col BIGINT NOT NULL"
        ");"
    };
}

std::string Database::createGlobalTable(const CXString& clangVersion, const std::string& appName, const std::string& appVersion)
{
    DatabaseQueryErrMsg queryErrMsg;
    std::string         queryErrMsgStr;

    if(isOK())
    {
        queryErrMsg = sendQuery(m_globalTableTemplateQuery);
        if(isNotOK())
            queryErrMsgStr += queryErrMsg;

        if(isOK())
        {
            DatabaseInsertQuery insertQueryBuilder;
            insertQueryBuilder.newQuery("..\\global", g_globalColumnDict);

            insertQueryBuilder.addCXStringColumnValue(GlobalTableColName::ClangVersion, clangVersion);
            insertQueryBuilder.addStringColumnValue(GlobalTableColName::AppName,        appName);
            insertQueryBuilder.addStringColumnValue(GlobalTableColName::AppVersion,     appVersion);

            queryErrMsg = sendQuery(insertQueryBuilder.buildQuery());
            if(isNotOK())
                queryErrMsgStr += queryErrMsg;
        }
    }
    else
        return lastErrorMsg();

    return queryErrMsgStr;
}

std::string Database::createFileListTable()
{
    DatabaseQueryErrMsg queryErrMsg;
    std::string         queryErrMsgStr;

    if(isOK())
    {
        queryErrMsg = sendQuery(m_fileListTableTemplateQuery);
        if(isNotOK())
            queryErrMsgStr += queryErrMsg;
    }
    else
        return lastErrorMsg();

    return queryErrMsgStr;
}

std::string Database::createSourceCodeTables(const std::string& tableName)
{
    DatabaseQueryErrMsg queryErrMsg;
    std::string         queryErrMsgStr;
    std::string         tokenTableQuery = m_tokenTableTemplateQuery;

    if(isOK())
    {
        DatabaseInsertQuery insertQueryBuilder;
        insertQueryBuilder.newQuery("..\\file_list", g_fileListColumnDict);

        insertQueryBuilder.addColumnValue(FileListTableColName::FileListID,             allocFileListID());
        insertQueryBuilder.addStringColumnValue(FileListTableColName::FileListFileName, tableName);

        queryErrMsg = sendQuery(insertQueryBuilder.buildQuery());
        if(isNotOK())
        {
            queryErrMsgStr += queryErrMsg;
            return queryErrMsgStr;
        }
        else
        {
            const std::string keyword = "<?filePath?>";

            size_t pos = tokenTableQuery.find(keyword);
            if (pos != std::string::npos)
            {
                tokenTableQuery.erase(pos, keyword.size());
                tokenTableQuery.insert(pos, tableName);
            }

            queryErrMsg = sendQuery(tokenTableQuery);
            if(isNotOK())
                return queryErrMsg.getString();
        }
    }
    else
        return lastErrorMsg();

    return {};
}

DatabaseQueryErrMsg Database::sendQuery(const std::string& query)
{
    dumpQueryToFile(query, "Send query");

    DatabaseQueryErrMsg errMsg;

    m_lastError = sqlite3_exec(
                                m_database,
                                query.c_str(),
                                nullptr,
                                nullptr,
                                errMsg
                              );

    return errMsg;
}

DatabaseQueryErrMsg Database::recvQuery(const std::string& query, QueryResults& results)
{
    dumpQueryToFile(query, "Recv query");

    DatabaseQueryErrMsg errMsg;

    m_lastError = sqlite3_exec(
                                m_database,
                                query.c_str(),
                                &Database::recvQueryCallback,
                                &results,
                                errMsg
                              );

    return errMsg;
}

int32_t Database::recvQueryCallback(void* data, int32_t colCount, char** rowValues, char** columnsName)
{
    QueryResults* results = reinterpret_cast<QueryResults*>(data);

    if(results->columns.empty())
        for(int32_t colIndex = 0; colIndex < colCount; ++colIndex)
        results->columns.push_back(columnsName[colIndex]);

    std::list<string> row;
    for(int32_t colIndex = 0; colIndex < colCount; ++colIndex)
        row.push_back(rowValues[colIndex]);

    results->rows.push_back(row);

    return 0;
}

void Database::dumpQueryToFile(const std::string& query, const char* comment /* = nullptr */)
{
    if(m_databaseOptions & DUMP_QUERIES_TO_FILE)
    {
        if(m_dumpQueryFile.is_open())
        {
            if(comment)
                m_dumpQueryFile << "!-- " << comment << " --!" << std::endl;

            m_dumpQueryFile << query << std::endl << std::endl;
        }
    }
}
