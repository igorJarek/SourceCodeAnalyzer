#pragma once

#include "sqlite3.h"

#include <string>

// in the future that class may be base class for another database engines
class Database
{
public:
    Database(const std::string& databaseName);
    ~Database();

    void                sendQuery(const std::string& query);
    void                buildDatabaseTables();

    bool                isOK()          const { m_lastError == SQLITE_OK; }
    int32_t             lastErrorCode() const { return m_lastError; }
    std::string         lastErrorMsg()  const { sqlite3_errmsg(m_database); }

private:
    sqlite3*            m_database      = nullptr;
    const std::string   m_databaseName;

    int32_t             m_lastError;
};
