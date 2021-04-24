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
    void fillTokensInfo(const list<Token>& tokens)
    {
        for(const Token& token : tokens)
        {
            if(token.tokenSpelling == functionName)
            if(token.getTokenPos() == functionNamePos)
                functionNameTokenID = token.tokenID;
        }
    }

    // DB Elements
    uint32_t callingID            = 0; 
    uint32_t functionNameTokenID  = 0;
    uint32_t functionDefinitionID = 0;
    fs::path functionDefinitionPath;

    //uint32_t openingArgumentsBracketTokenID;
    //uint32_t closingArgumentsBracketTokenID;

    // Internal Use
    string   functionName;
    TokenPos functionNamePos;
};

struct DatabaseBuilderFunction
{
    DatabaseBuilderFunction(Database& database, CXCursor cursor)
    {
        functionID = database.allocFunctionsID();
        functionName = to_string(clang_getCursorSpelling(cursor));
        functionNamePos.setCXSourceLocation(clang_getCursorLocation(cursor));
        functionDefRange.setCXSourceRange(clang_getCursorExtent(cursor));

        sourceFileType = HeaderFile::getSourceFileType(functionNamePos.fileName.string());
    }

    void fillTokensInfo(const list<Token>& tokens)
    {
        for(const Token& token : tokens)
        {
            if(token.getTokenPos() == functionNamePos)
                functionNameTokenID = token.tokenID;

            else if(token.isStartsEqual(functionDefRange))
                openDefinitionTokenID = token.tokenID;

            else if(token.isEndsEqual(functionDefRange))
                closeDefinitionTokenID = token.tokenID;
        }
    }

    // DB Elements
    uint32_t       functionID               = 0;
    uint32_t       functionNameTokenID      = 0;

    uint32_t       openDefinitionTokenID    = 0;
    uint32_t       closeDefinitionTokenID   = 0;

    // Internal Use
    SourceFileType sourceFileType = SourceFileType::UNKNOWN;
    string         functionName;
    TokenPos       functionNamePos;
    TokenRange     functionDefRange;
};

class DatabaseBuilderClass
{
    
};

class DatabaseBuilder
{
    public:
        using CallingMap    = map<string, DatabaseBuilderCalling>;
        using FunctionsMap  = map<string, DatabaseBuilderFunction>;
        using ClassesMap    = map<string, DatabaseBuilderClass>;

        using HeaderFileMap = map<string, shared_ptr<HeaderFile>>;
        using SourceFileMap = map<string, shared_ptr<SourceFile>>;

    public:
        DatabaseBuilder(Database& database,
                        const string& appName, const string& appVersion,
                        const FolderBrowser& folderBrowser,
                        const char* compilationArgs[], uint32_t argsCount);
        ~DatabaseBuilder();

    public:
        void buildDatabase(function<void (const string& filePath, size_t fileIndex, size_t fileCount)> buildState);

    protected:
        CXChildVisitResult classDef(CXCursor cursor, shared_ptr<SourceFile> sourceFile);
        CXChildVisitResult functionDef(CXCursor cursor, shared_ptr<SourceFile> sourceFile);
        CXChildVisitResult methodDef(CXCursor cursor, shared_ptr<SourceFile> sourceFile);
        CXChildVisitResult callExp(CXCursor cursor, shared_ptr<SourceFile> sourceFile);

    protected:
        void createDatabaseTables(const string& filePath);

        void createInsertTokensTableData(const string& filePath, const Token& token);
        void createInsertCallingTableData(const string& filePath, const DatabaseBuilderCalling& calling);
        void createInsertFunctionsTableData(const string& filePath, const DatabaseBuilderFunction& function);

    protected:
        const string&        m_appName;
        const string&        m_appVersion;
        const FolderBrowser& m_folderBrowser;
        const char**         m_compilationArgs = nullptr;
        uint32_t             m_argsCount       = 0;

        Database&            m_database;

        HeaderFileMap        m_headerFileMap;
        SourceFileMap        m_sourceFileMap;

        ClassesMap           m_classesMap;
        CallingMap           m_callingMap;
        FunctionsMap         m_functionsMap;
};