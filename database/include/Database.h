#pragma once

#include "clang-c/CXString.h"
#include "sqlite3.h"

#include <string>
#include <map>
#include <list>

class DatabaseQueryErrMsg
{
public:
    DatabaseQueryErrMsg() {}
    DatabaseQueryErrMsg(DatabaseQueryErrMsg&& queryErr) 
    {
        m_errorMessagePtr = queryErr.m_errorMessagePtr;
        queryErr.m_errorMessagePtr = nullptr;
    }

    ~DatabaseQueryErrMsg()
    { 
        if(m_errorMessagePtr)
            sqlite3_free(reinterpret_cast<void*>(m_errorMessagePtr));
    }

    DatabaseQueryErrMsg& operator=(DatabaseQueryErrMsg&& queryErr)
    {
        if(m_errorMessagePtr)
            sqlite3_free(reinterpret_cast<void*>(m_errorMessagePtr));

        m_errorMessagePtr = queryErr.m_errorMessagePtr;
        queryErr.m_errorMessagePtr = nullptr;

        return *this;
    }

    operator char**()       { return &m_errorMessagePtr; }
    operator const char*()  { return reinterpret_cast<const char*>(m_errorMessagePtr); }

    std::string getString()
    {
        if(m_errorMessagePtr)
            return std::string(*this);

        return {};
    }

private:
    DatabaseQueryErrMsg(const DatabaseQueryErrMsg&) {}
    DatabaseQueryErrMsg& operator=(DatabaseQueryErrMsg&) {}

private:
    char* m_errorMessagePtr = nullptr;
};

class DatabaseInsertQuery
{
public:
    DatabaseInsertQuery();
    ~DatabaseInsertQuery();

public:
    void                                   clear();
    void                                   clearForNewQuery();

    void                                   newQuery(const std::string& tableName, const std::map<uint32_t, std::string>& columnDefMap);

    void                                   addColumnValue( uint32_t columnIndex, const int64_t& value);
    void                                   addColumnValue( uint32_t columnIndex, const std::string& value);
    void                                   addColumnValue( uint32_t columnIndex, const double& value);
    void                                   addColumnValue( uint32_t columnIndex, const CXString& value);

    std::string&                           buildQuery();

private:
    std::string                            m_tableName;
    const std::map<uint32_t, std::string>* m_colDefMap;

    std::list<std::string>                 m_colNameList;
    std::list<std::string>                 m_colValueList;

    std::string                            m_query;
};

enum DatabaseFileMode
{
    TRUNCATE_DB_FILE    = (1 << 1),

    READONLY_DB_FILE    = (1 << 2),
    READ_WRITE_DB_FILE  = (1 << 3),

    IN_MEMORY_DB_FILE   = (1 << 4),
    FILE_DB_FILE        = (1 << 5)
};

// in the future that class may be base class for another database engines
class Database
{
public:
    Database(const std::string& databasePath);
    ~Database();

public:
    void                            openDatabase(uint32_t databaseFileMode /* DatabaseFileMode enum */);
    DatabaseQueryErrMsg             sendQuery(const std::string& query);

    std::string                     createGlobalTable(const CXString& clangVersion, const std::string& appName, const std::string& appVersion);
    std::string                     createSourceCodeTables(const std::string& tableName);

public:
    bool                            isOK()              const { return m_lastError == SQLITE_OK; }
    bool                            isNotOK()           const { return m_lastError != SQLITE_OK; }
    int32_t                         lastErrorCode()     const { return m_lastError; }
    std::string                     lastErrorMsg()      const { return sqlite3_errmsg(m_database); }

private:
    void                            createGlobalTableTemplateQuery();
    void                            createTokenTableTemplateQuery();
    void                            createSourceCodeTableTemplateQuery();

private:
    sqlite3*                        m_database      = nullptr;
    const std::string               m_databasePath;

    int32_t                         m_lastError = SQLITE_ERROR;

    std::string                     m_globalTableTemplateQuery;
    std::string                     m_tokenTableTemplateQuery;
    std::string                     m_sourceCodeTableTemplateQuery;
};
