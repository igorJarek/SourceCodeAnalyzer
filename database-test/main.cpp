#include <iostream>
#include <string>
#include <fstream>

#include <clang-c/Index.h>

#include "FolderBrowser.h"
#include "Database.h"
#include "DatabaseColumnDict.h"
#include "ColumnDefinition.h"

using namespace std;

void createDatabaseTables(Database& database, const string& filePath, const CXTranslationUnit& translationUnit);

int64_t countFileLines(const string& filePath);
int64_t countFileLineColumns(const string& filePath, int64_t line);

int main()
{
    const string APP_NAME("database-test");
    const string APP_VERSION("1.0");

    const string libPath("..\\lib\\");
    const string databasePath("..\\lib\\lib.sqlite3");

    const char* argsIncludePrefix       = "-I";
    const char* argsIncludePath         = "..\\lib\\include\\";
    const char* COMPILATION_ARGS[2]     = { argsIncludePrefix, argsIncludePath };

    FolderBrowser fb;
    fb.clearFileList();
    fb.setFileTypeBrowser(FileType::SOURCE_AND_HEADER_FILE);
    fb.startFolderBrowse(libPath);

    const size_t        fileCount = fb.getFileCount();
    const list<string>& fileFile  = fb.getFileList();

    Database database(databasePath);
    database.openDatabase(DatabaseFileMode::TRUNCATE_DB_FILE   | 
                          DatabaseFileMode::READ_WRITE_DB_FILE | 
                          DatabaseFileMode::FILE_DB_FILE);

    string dbErrMsg = database.createGlobalTable(clang_getClangVersion(), APP_NAME, APP_VERSION);
    if(database.isNotOK())
        cout << "Database error : " << dbErrMsg << endl;
    else
    {
        for(const string& filePath : fileFile)
        {
            CXIndex index = clang_createIndex(0, 0);

            CXTranslationUnit translationUnit;
            CXErrorCode       errorCode = clang_parseTranslationUnit2(index, 
                                                                      filePath.c_str(), 
                                                                      COMPILATION_ARGS, 
                                                                      sizeof(COMPILATION_ARGS) / sizeof(const char*),
                                                                      nullptr,
                                                                      0,
                                                                      CXTranslationUnit_None,
                                                                      &translationUnit);

            if (errorCode == CXError_Success)
            {
                cout << "Parsing " << filePath << " file ... ";

                if(database.isOK())
                {
                    createDatabaseTables(database, filePath, translationUnit);
                    cout << "Done";
                }
                else
                    break;

                cout << endl;

                clang_disposeTranslationUnit(translationUnit);
            }

            clang_disposeIndex(index);
        }
    }
}

void createDatabaseTables(Database& database, const string& filePath, const CXTranslationUnit& translationUnit)
{
    string dbErrMsg = database.createSourceCodeTables(filePath);
    if(database.isNotOK())
    {
        cout << dbErrMsg;
        return;
    }

    CXFile           file            = clang_getFile(translationUnit, filePath.c_str());

    const int64_t    lineCount       = countFileLines(filePath);
    const int64_t    lastLineColumns = countFileLineColumns(filePath, lineCount);

    CXSourceLocation beginLocation   = clang_getLocation(translationUnit, file, 1, 1);
    CXSourceLocation endLocation     = clang_getLocation(translationUnit, file, static_cast<unsigned int>(lineCount), static_cast<unsigned int>(lastLineColumns));
    CXSourceRange    tokenizerRange  = clang_getRange(beginLocation, endLocation);

    CXToken*         tokensOut       = nullptr;
    uint32_t         tokensNum       = 0;

    clang_tokenize(translationUnit, tokenizerRange, &tokensOut, &tokensNum);

    if (tokensNum > 0)
    {
        for (uint32_t index{ 0 }; index < tokensNum; ++index)
        {
            const CXToken&   token = tokensOut[index];

            CXTokenKind      tokenKind     = clang_getTokenKind(token);
            CXString         tokenSpelling = clang_getTokenSpelling(translationUnit, token);
            CXSourceRange    tokenRange    = clang_getTokenExtent(translationUnit, token);

            CXSourceLocation tokenLocation = clang_getTokenLocation(translationUnit, token);
            CXCursor         cursor        = clang_getCursor(translationUnit, tokenLocation);

            // Database Data Preparing
            // Tokens
            CXSourceLocation rangeStart = clang_getRangeStart(tokenRange);
            CXSourceLocation rangeEnd   = clang_getRangeEnd(tokenRange);

            int64_t tokenStartPos, tokenEndPos;

            uint32_t startExpansionLine, startExpansioColumn;
            uint32_t endExpansionLine, endExpansioColumn;

            clang_getExpansionLocation(rangeStart, nullptr, &startExpansionLine, &startExpansioColumn, nullptr);
            clang_getExpansionLocation(rangeEnd,   nullptr, &endExpansionLine,   &endExpansioColumn,   nullptr);

            tokenStartPos = startExpansionLine << 31 | startExpansioColumn;
            tokenEndPos   = endExpansionLine   << 31 | endExpansioColumn;

            // Cursor

            CXString mangling = clang_Cursor_getMangling(cursor);

            // Add Data To Token Table

            DatabaseInsertQuery insertQueryBuilder;
            insertQueryBuilder.newQuery(filePath + "\\tokens", g_tokenColumnDict);

            insertQueryBuilder.addColumnValue(TokenKind,     (int64_t)tokenKind);
            insertQueryBuilder.addColumnValue(TokenSpelling, tokenSpelling);
            insertQueryBuilder.addColumnValue(TokenStartPos, tokenStartPos);
            insertQueryBuilder.addColumnValue(TokenEndPos,   tokenEndPos);

            DatabaseQueryErrMsg tokenQueryErrMsg = database.sendQuery(insertQueryBuilder.buildQuery());
            if(database.isNotOK())
                cout << "sendQuery() error : " << tokenQueryErrMsg << endl;

            insertQueryBuilder.clear();
            insertQueryBuilder.newQuery(filePath + "\\cursors", g_sourceCodeColumnDict);

            insertQueryBuilder.addColumnValue(TokenTable_TokenID, (int64_t)index + 1);
            insertQueryBuilder.addColumnValue(CursorMangling,     mangling);

            DatabaseQueryErrMsg cursorQueryErrMsg = database.sendQuery(insertQueryBuilder.buildQuery());
            if(database.isNotOK())
                cout << "sendQuery() error : " << cursorQueryErrMsg << endl;
        }
    }

    if (tokensOut)
        clang_disposeTokens(translationUnit, tokensOut, tokensNum);
}

int64_t countFileLines(const string& filePath)
{
    fstream stream;
    int64_t lines{ -1 };

    stream.open(filePath, std::fstream::in);
    if (stream.is_open())
    {
        lines = 0;

        string s;
        while (getline(stream, s))
            ++lines;

        stream.close();
    }

    return lines;
}

int64_t countFileLineColumns(const string& filePath, int64_t line)
{
    if (line < 0)
        return -1;

    fstream stream;
    int64_t columns{ -1 };
    int64_t lines{ -1 };

    stream.open(filePath, std::fstream::in);
    if (stream.is_open())
    {
        string str;
        lines = 0;

        while (getline(stream, str))
        {
            ++lines;
            if (lines == line)
                break;
        }

        if(lines == line) // file lines < line
            columns = str.size();

        stream.close();
    }

    return columns;
}
