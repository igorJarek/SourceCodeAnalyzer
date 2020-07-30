#include "Database.h"
#include "ColumnDefinition.h"
#include "DatabaseColumnDict.h"

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

void DatabaseInsertQuery::addColumnValue(uint32_t columnIndex, const int64_t& value)
{
    m_colValueList.push_back(std::to_string(value));

    auto iter = m_colDefMap->find(columnIndex);

    if (iter != m_colDefMap->cend())
        m_colNameList.push_back(iter->second);
    else
        m_colNameList.push_back(std::string("--ColumnMissing--"));
}

void DatabaseInsertQuery::addColumnValue(uint32_t columnIndex, const double& value)
{
    m_colValueList.push_back(std::to_string(value));

    auto iter = m_colDefMap->find(columnIndex);

    if (iter != m_colDefMap->cend())
        m_colNameList.push_back(iter->second);
    else
        m_colNameList.push_back(std::string("--ColumnMissing--"));
}

void DatabaseInsertQuery::addColumnValue(uint32_t columnIndex, const std::string& value)
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

Database::Database(const std::string& databaseName) :
    m_databaseName(databaseName)
{
    m_lastError = sqlite3_open_v2(
                                      m_databaseName.c_str(), 
                                      &m_database, 
                                      SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE /* | SQLITE_OPEN_MEMORY */, 
                                      nullptr
                                  );

    createGlobalTableTemplateQuery();
    createTokenTableTemplateQuery();
    createSourceCodeTableTemplateQuery();
}

Database::~Database()
{
    sqlite3_close(m_database);
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
            "TokenID INTEGER PRIMARY KEY AUTOINCREMENT,"
            "TokenKind TINYINT NOT NULL,"
            "TokenSpelling VARCHAR(255) NOT NULL,"
            "TokenStartPos BIGINT NOT NULL,"
            "TokenEndPos BIGINT NOT NULL"
        ");"
    };
}

void Database::createSourceCodeTableTemplateQuery()
{
    m_sourceCodeTableTemplateQuery =
    {
        "CREATE TABLE \"<?filePath?>\\cursors\""
        "("
            "CursorID INTEGER PRIMARY KEY AUTOINCREMENT,"
            "TokenID INT, "
            "CursorMangling VARCHAR(255),"
            "CursorIsBits INT,"
            "CursorUSR VARCHAR(255),"
            "CursorAccessSpecifier TINYINT,"
            "CursorStorageClass TINYINT,"
            "CursorDisplayName VARCHAR(255),"
            "CursorHash INT,"
            "CursorKind SMALLINT,"
            "CursorAttr INT,"
            "CursorLinkage TINYINT,"
            "CursorVisibility TINYINT,"
            "CursorAvailability TINYINT,"
            "CursorTLSKind TINYINT,"

            "FOREIGN KEY (TokenID) REFERENCES \"<?filePath?>\\tokens\"(TokenID)"
        ");"
    };
}

std::string Database::createGlobalTable(const std::string& clangVersion, const std::string& appName, const std::string& appVersion)
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

            insertQueryBuilder.addColumnValue(GlobalTableColName::ClangVersion, clangVersion);
            insertQueryBuilder.addColumnValue(GlobalTableColName::AppName,      appName);
            insertQueryBuilder.addColumnValue(GlobalTableColName::AppVersion,   appVersion);

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
    std::string sourceCodeTableQuery = m_sourceCodeTableTemplateQuery;

    if(isOK())
    {
        std::string keyword = "<?filePath?>";

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

        pos = sourceCodeTableQuery.rfind(keyword);
        if (pos != std::string::npos)
        {
            sourceCodeTableQuery.erase(pos, keyword.size());
            sourceCodeTableQuery.insert(pos, tableName);
        }

        queryErrMsg = sendQuery(sourceCodeTableQuery);
        if(isNotOK())
            return queryErrMsg.getString();
    }
    else
        return lastErrorMsg();

    return {};
}

DatabaseQueryErrMsg Database::sendQuery(const std::string& query)
{
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
