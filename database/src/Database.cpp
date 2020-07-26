#include "Database.h"

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
    m_globalTableColNameMap.emplace(GlobalTableColName::ClangVersion, "ClangVersion");
    m_globalTableColNameMap.emplace(GlobalTableColName::AppVersion,   "AppVersion");

    m_globalTableTemplateQuery =
    {
        "CREATE TABLE Global"
        "("
            "ClangVersion VARCHAR(255),"
            "AppVersion VARCHAR(255)"
        ");"
    };
}

void Database::createTokenTableTemplateQuery()
{
    m_tokenTableColNameMap.emplace(TokenTableColName::TokenID,       "TokenID");
    m_tokenTableColNameMap.emplace(TokenTableColName::TokenKind,     "TokenKind");
    m_tokenTableColNameMap.emplace(TokenTableColName::TokenSpelling, "TokenSpelling");
    m_tokenTableColNameMap.emplace(TokenTableColName::TokenStartPos, "TokenStartPos");
    m_tokenTableColNameMap.emplace(TokenTableColName::TokenEndPos,   "TokenEndPos");

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

void Database::createSourceCodeTableTemplateQuery()
{
    m_sourceCodeTableColNameMap.emplace(SourceCodeTableColName::CursorID,              "CursorID");
    m_sourceCodeTableColNameMap.emplace(SourceCodeTableColName::TokenID,               "TokenID");
    m_sourceCodeTableColNameMap.emplace(SourceCodeTableColName::CursorMangling,        "CursorMangling");
    m_sourceCodeTableColNameMap.emplace(SourceCodeTableColName::CursorIsBits,          "CursorIsBits");
    m_sourceCodeTableColNameMap.emplace(SourceCodeTableColName::CursorUSR,             "CursorUSR");
    m_sourceCodeTableColNameMap.emplace(SourceCodeTableColName::CursorAccessSpecifier, "CursorAccessSpecifier");
    m_sourceCodeTableColNameMap.emplace(SourceCodeTableColName::CursorStorageClass,    "CursorStorageClass");
    m_sourceCodeTableColNameMap.emplace(SourceCodeTableColName::CursorDisplayName,     "CursorDisplayName");
    m_sourceCodeTableColNameMap.emplace(SourceCodeTableColName::CursorHash,            "CursorHash");
    m_sourceCodeTableColNameMap.emplace(SourceCodeTableColName::CursorKind,            "CursorKind");
    m_sourceCodeTableColNameMap.emplace(SourceCodeTableColName::CursorAttr,            "CursorAttr");
    m_sourceCodeTableColNameMap.emplace(SourceCodeTableColName::CursorLinkage,         "CursorLinkage");
    m_sourceCodeTableColNameMap.emplace(SourceCodeTableColName::CursorVisibility,      "CursorVisibility");
    m_sourceCodeTableColNameMap.emplace(SourceCodeTableColName::CursorAvailability,    "CursorAvailability");
    m_sourceCodeTableColNameMap.emplace(SourceCodeTableColName::CursorTLSKind,         "CursorTLSKind");

    m_sourceCodeTableTemplateQuery =
    {
        "CREATE TABLE \"<?filePath?>\\cursors\""
        "("
            "CursorID INT PRIMARY KEY,"
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

std::string Database::createGlobalTable()
{
    DatabaseQueryErrMsg queryErrMsg;
    std::string         queryErrMsgStr;

    if(isOK())
    {
        queryErrMsg = sendQuery(m_globalTableTemplateQuery);
        if(isNotOK())
            queryErrMsgStr += queryErrMsg;
    }
    else
        return lastErrorMsg();

    return queryErrMsgStr;
}

std::string Database::createSourceCodeTable(const std::string& tableName)
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
            return queryErrMsg.string();

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
            return queryErrMsg.string();
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
