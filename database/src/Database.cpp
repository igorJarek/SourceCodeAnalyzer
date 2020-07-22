#include "Database.h"

Database::Database(const std::string& databaseName) :
    m_databaseName(databaseName)
{
    m_lastError = sqlite3_open_v2(
                                      m_databaseName.c_str(), 
                                      &m_database, 
                                      SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_MEMORY, 
                                      nullptr
                                  );
}

Database::~Database()
{
    sqlite3_close(m_database);
}

void Database::buildDatabaseTables()
{
    
}

void Database::sendQuery(const std::string& query)
{

}
