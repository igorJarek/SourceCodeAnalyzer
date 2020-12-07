#pragma once

#include <ExecutionTimeMeasurement/ExecutionTimeMeasurement.h>
#include <LibClangStruct2Str/LibClangStruct2Str.h>
#include <FolderBrowser/FolderBrowser.h>
#include <SourceCode/SourceCode.hpp>
#include <Database/Database.h>

#include <iostream>
#include <map>

using std::map;
using std::to_string;

struct FunctionPos
{
    void setCXSourceRange(const CXSourceRange& range)
    {
        CXSourceLocation locStart  = clang_getRangeStart(range);
        CXSourceLocation locEnd    = clang_getRangeEnd(range);

        clang_getExpansionLocation(locStart, nullptr, &startLine, &startCol, nullptr);
        clang_getExpansionLocation(locEnd,   nullptr, &endLine, &endCol, nullptr);
    }

    uint32_t startLine, startCol;
    uint32_t endLine, endCol;
};

struct Function             // clang_getCursorReferenced, clang_isCursorDefinition, clang_equalCursors, clang_getCanonicalCursor (dla definicji zwroci plik .hpp)
                            // clang_getCursorResultType, clang_getNumArgTypes
{
    uint8_t     kind;       // 0 - empty, 1 - function, 2 - method, 3 - invoke

    string      usr;        // clang_getCursorUSR
    string      mangling;   // clang_Cursor_getMangling
    FunctionPos pos;        // clang_getCursorLocation ?

    string      name;       // clang_getCursorSpelling ?
    uint8_t     argCount;   // clang_Cursor_getNumArguments
};

class DatabaseBuilder
{
    public:
        DatabaseBuilder(Database& database,
                        const string& appName, const string& appVersion,
                        const FolderBrowser& folderBrowser,
                        const char* compilationArgs[], uint32_t argsCount);
        ~DatabaseBuilder();

    public:
        void buildDatabase();

    private:
        void createDatabaseTables(const string& filePath);

        void createInsertTokensTableData(const string& filePath, uint32_t tokenID, const CXTokenKind& tokenKind, const CXString& tokenSpelling, const CXSourceRange& tokenRange);

    private:
        const string&        m_appName;
        const string&        m_appVersion;
        const FolderBrowser& m_folderBrowser;
        const char**         m_compilationArgs = nullptr;
        uint32_t             m_argsCount       = 0;

        Database&            m_database;
};