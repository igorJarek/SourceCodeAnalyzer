#include <database/Database.h>
#include <database/ColumnDefinition.h>
#include <database/DatabaseColumnDict.h>

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
    createTokenTableTemplateQuery();
    createCursorTableTemplateQuery();
    createTypeTableTemplateQuery();
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

void Database::createTokenTableTemplateQuery()
{
    m_tokenTableTemplateQuery =
    {
        "CREATE TABLE \"<?filePath?>\\tokens\""
        "("
            "TokenID INT PRIMARY KEY,"
            "TokenKind TINYINT NOT NULL,"
            "TokenSpelling VARCHAR(255) NOT NULL,"
            "TokenStartPos BIGINT NOT NULL,"
            "TokenEndPos BIGINT NOT NULL"
        ");"
    };
}

void Database::createCursorTableTemplateQuery()
{
    m_cursorTableTemplateQuery =
    {
        "CREATE TABLE \"<?filePath?>\\cursors\""
        "("
            "CursorID INT PRIMARY KEY,"
            "TokenTable_TokenID INT,"
            "CursorMangling VARCHAR(255),"
            "CursorIsBits INT,"
            "CursorTemplateCursorKind SMALLINT,"
            "CursorUSR VARCHAR(255),"
            "CursorDisplayName VARCHAR(255),"
            "CursorTable_CursorReferenced INT,"
            "TypeTable_CursorType INT,"
            "CursorEnumConstantDeclValue BIGINT,"
            "CursorEnumConstantDeclUValue BIGINT,"
            "CursorFieldDeclBitWidth INT,"
            "CursorExceptionSpecification INT,"
            "CursorOffsetOfField BIGINT,"
            "CursorAccessSpecifier TINYINT,"
            "CursorStorageClass TINYINT,"
            "CursorEvalResultKind TINYINT,"
            "CursorHash INT,"
            "CursorKind SHORTINT,"
            "CursorAttr INT,"
            "CursorLinkageKind TINYINT,"
            "CursorVisibilityKind TINYINT,"
            "CursorAvailabilityKind TINYINT,"
            "CursorLanguageKind TINYINT,"
            "CursorTLSKind TINYINT"
        ");"
    };
}

void Database::createTypeTableTemplateQuery()
{
    m_typeTableTemplateQuery =
    {
        "CREATE TABLE \"<?filePath?>\\types\""
        "("
            "TypeID INT PRIMARY KEY,"
            "TypeSpelling VARCHAR(255),"
            "TypeIsBits INT,"
            "TypeAddressSpace INT,"
            "TypeTypedefName VARCHAR(255),"
            "TypeKindSpelling VARCHAR(255),"
            "TypeFuncCallingConv TINYINT,"
            "TypeExceptionSpecification INT,"
            "TypeArraySize BIGINT,"
            "TypeNullabilityKind TINYINT,"
            "TypeAlignOf BIGINT,"
            "TypeSizeOf BIGINT,"
            "TypeRefQualifierKind TINYINT"
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

std::string Database::createSourceCodeTables(const std::string& tableName)
{
    DatabaseQueryErrMsg queryErrMsg;
    std::string tokenTableQuery      = m_tokenTableTemplateQuery;
    std::string sourceCodeTableQuery = m_cursorTableTemplateQuery;
    std::string typeTableQuery       = m_typeTableTemplateQuery;

    if(isOK())
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

        pos = sourceCodeTableQuery.find(keyword);
        if (pos != std::string::npos)
        {
            sourceCodeTableQuery.erase(pos, keyword.size());
            sourceCodeTableQuery.insert(pos, tableName);
        }

        queryErrMsg = sendQuery(sourceCodeTableQuery);
        if(isNotOK())
            return queryErrMsg.getString();

        pos = typeTableQuery.find(keyword);
        if (pos != std::string::npos)
        {
            typeTableQuery.erase(pos, keyword.size());
            typeTableQuery.insert(pos, tableName);
        }

        queryErrMsg = sendQuery(typeTableQuery);
        if(isNotOK())
            return queryErrMsg.getString();
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
