#pragma once

#include "ExecutionTimeMeasurement/ExecutionTimeMeasurement.h"
#include "LibClangStruct2Str/LibClangStruct2Str.h"
#include "FolderBrowser/FolderBrowser.h"
#include "SourceFile/SourceFile.h"
#include "Database/Database.h"

#include <iostream>
#include <map>

using std::map;
using std::to_string;

struct DatabaseBuilderCalling
{
    // DB Elements
    uint32_t callingID            = 0; 
    uint32_t functionNameTokenID  = 0;
    uint32_t functionDefinitionID = 0;
    string   functionDefinitionPath;

    //uint32_t openingArgumentsBracketTokenID;
    //uint32_t closingArgumentsBracketTokenID;

    // Internal Use
    string   functionName;
    TokenPos functionNamePos;
};

struct DatabaseBuilderFunction
{
    // DB Elements
    uint32_t functionID               = 0;
    uint32_t functionNameTokenID      = 0;

    uint32_t openDefinitionTokenID    = 0;
    uint32_t closeDefinitionTokenID   = 0;

    // Internal Use
    string     functionName;
    TokenPos   functionNamePos; 
    TokenRange functionDefRange; 
};

class DatabaseBuilder
{
    public:
        using CallingMap   = map<string, DatabaseBuilderCalling>;
        using FunctionsMap = map<string, DatabaseBuilderFunction>;

    public:
        DatabaseBuilder(Database& database,
                        const string& appName, const string& appVersion,
                        const FolderBrowser& folderBrowser,
                        const char* compilationArgs[], uint32_t argsCount);
        ~DatabaseBuilder();

    public:
        void buildDatabase(function<void (const string& filePath, size_t fileIndex, size_t fileCount)> buildState);

    private:
        void createDatabaseTables(const string& filePath);

        void createInsertTokensTableData(const string& filePath, const Token& token);
        void createInsertCallingTableData(const string& filePath, const DatabaseBuilderCalling& calling);
        void createInsertFunctionsTableData(const string& filePath, const DatabaseBuilderFunction& function);

    private:
        const string&        m_appName;
        const string&        m_appVersion;
        const FolderBrowser& m_folderBrowser;
        const char**         m_compilationArgs = nullptr;
        uint32_t             m_argsCount       = 0;

        Database&            m_database;
        CallingMap           m_callingMap;
        FunctionsMap         m_functionsMap;
};