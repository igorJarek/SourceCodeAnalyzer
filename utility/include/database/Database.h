#pragma once

#include "clang-c/CXString.h"
#include "sqlite3.h"

#include <string>
#include <map>
#include <list>
#include <vector>
#include <fstream>

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

    DatabaseQueryErrMsg& operator=(DatabaseQueryErrMsg&& queryErr) noexcept
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

    template<typename T>
    void                                   addColumnValue( uint32_t columnIndex, const T value)
    {
        std::string str = std::to_string(value);
        std::size_t pos = 0;
        while ((pos = str.find('\'', pos)) != std::string::npos) 
        {
             str.replace(pos, 1, "\'\'");
             pos += 2;
        }

        m_colValueList.push_back(str);

        auto iter = m_colDefMap->find(columnIndex);

        if (iter != m_colDefMap->cend())
            m_colNameList.push_back(iter->second);
        else
            m_colNameList.push_back(std::string("--ColumnMissing--"));
    }

    void                                   addStringColumnValue( uint32_t columnIndex, const std::string& value);
    void                                   addCXStringColumnValue( uint32_t columnIndex, const CXString& value);

    std::string&                           buildQuery();

private:
    std::string                            m_tableName;
    const std::map<uint32_t, std::string>* m_colDefMap;

    std::list<std::string>                 m_colNameList;
    std::list<std::string>                 m_colValueList;

    std::string                            m_query;
};

struct QueryResults
{
    std::vector<std::string>            columns;
    std::list<std::vector<std::string>> rows;

    void clear()
    {
        columns.clear();
        rows.clear();
    }
};

enum DatabaseOptions
{
    TRUNCATE_DB_FILE     = (1 << 1),

    READONLY_DB_FILE     = (1 << 2),
    READ_WRITE_DB_FILE   = (1 << 3),

    IN_MEMORY_DB_FILE    = (1 << 4),
    FILE_DB_FILE         = (1 << 5),

    DUMP_QUERIES_TO_FILE = (1 << 6)
};

// in the future that class may be base class for another database engines
class Database
{
public:
    Database(const std::string& databasePath);
    ~Database();

public:
    void                            openDatabase(uint32_t databaseOptions /* DatabaseOptions enum */);
    DatabaseQueryErrMsg             sendQuery(const std::string& query);
    DatabaseQueryErrMsg             recvQuery(const std::string& query, QueryResults& results);

    std::string                     createGlobalTable(const CXString& clangVersion, const std::string& appName, const std::string& appVersion);
    std::string                     createFileListTable();
    std::string                     createSourceCodeTables(const std::string& tableName);

    uint32_t                        getTokenID()    const { return m_tokenTableIdAllocator; }
    uint32_t                        getFileListID()  const { return m_fileListTableIdAllocator; }

    uint32_t                        allocTokenID()    { return ++m_tokenTableIdAllocator;  }
    uint32_t                        allocFileListID()  { return ++m_fileListTableIdAllocator;  }

public:
    bool                            isOK()              const { return m_lastError == SQLITE_OK; }
    bool                            isNotOK()           const { return m_lastError != SQLITE_OK; }
    int32_t                         lastErrorCode()     const { return m_lastError; }
    std::string                     lastErrorMsg()      const { return sqlite3_errmsg(m_database); }

private:
    void                            createGlobalTableTemplateQuery();
    void                            createFileListTableTemplateQuery();
    void                            createTokenTableTemplateQuery();

    void                            dumpQueryToFile(const std::string& query, const char* comment = nullptr);

private:
    static int32_t                  recvQueryCallback(void* data, int32_t colCount, char** rowValues, char** columnsName);

private:
    sqlite3*                        m_database      = nullptr;
    const std::string               m_databasePath;
    std::fstream                    m_dumpQueryFile;

    uint32_t                        m_databaseOptions = 0;

    int32_t                         m_lastError = SQLITE_ERROR;

    std::string                     m_globalTableTemplateQuery;
    std::string                     m_fileListTableTemplateQuery;
    std::string                     m_tokenTableTemplateQuery;

    uint32_t                        m_tokenTableIdAllocator = 0;
    uint32_t                        m_fileListTableIdAllocator = 0;
};
