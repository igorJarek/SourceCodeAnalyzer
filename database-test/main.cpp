#include <iostream>
#include <string>
#include <fstream>

#include <clang-c/Index.h>

#include <FolderBrowser/FolderBrowser.h>

#include <ExecutionTimeMeasurement/ExecutionTimeMeasurement.h>

#include <Database/Database.h>
#include <Database/DatabaseColumnDict.h>
#include <Database/ColumnDefinition.h>

using namespace std;

void createDatabaseTables(Database& database, const string& filePath, const CXTranslationUnit& translationUnit);

void createInsertTokensTableData(Database& database, const string& filePath, uint32_t tokenID, const CXTokenKind& tokenKind, const CXString& tokenSpelling, const CXSourceRange& tokenRange);
void createInsertCursorsTableData(Database& database, const string& filePath, uint32_t cursorID, uint32_t cursorRefID, uint32_t tokenID, const CXCursor& cursor);

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
    fb.setFileTypeBrowser(FileType::SOURCE_FILE);
    fb.startFolderBrowse(libPath);

    const size_t        fileCount = fb.getFileCount();
    const list<string>& fileList  = fb.getFileList();

    Database database(databasePath);
    database.openDatabase(DatabaseOptions::TRUNCATE_DB_FILE   | 
                          DatabaseOptions::READ_WRITE_DB_FILE | 
                          DatabaseOptions::FILE_DB_FILE       |
                          DatabaseOptions::DUMP_QUERIES_TO_FILE);

    string dbErrMsg = database.createGlobalTable(clang_getClangVersion(), APP_NAME, APP_VERSION);
    if(database.isNotOK())
    {
        cout << "createGlobalTable() Error : " << dbErrMsg << endl;
        return EXIT_SUCCESS;
    }

    dbErrMsg = database.createLinkingTable();
    if(database.isNotOK())
    {
        cout << "createLinkingTable() Error : " << dbErrMsg << endl;
        return EXIT_SUCCESS;
    }

    for(const string& filePath : fileList)
    {
        CXIndex           index     = clang_createIndex(0, 0);

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
            if(database.isOK())
            {
                ExecutionTimeMeasurement timeMeasurement("Parsing " + filePath + " file in");

                createDatabaseTables(database, filePath, translationUnit);
            }
            else
                break;

            clang_disposeTranslationUnit(translationUnit);
        }

        clang_disposeIndex(index);
    }

    return EXIT_SUCCESS;
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

            CXTokenKind      tokenKind        = clang_getTokenKind(token);
            CXString         tokenSpelling    = clang_getTokenSpelling(translationUnit, token);
            CXSourceRange    tokenRange       = clang_getTokenExtent(translationUnit, token);

            CXSourceLocation tokenLocation    = clang_getTokenLocation(translationUnit, token);

            CXCursor         cursor           = clang_getCursor(translationUnit, tokenLocation);
            CXCursor         cursorReferenced = clang_getCursorReferenced(cursor);

            CXType           cursorType       = clang_getCursorType(cursor);
            CXType           cursorRefType    = clang_getCursorType(cursorReferenced);

            uint32_t         tokenID          = database.allocTokenID();

            uint32_t         cursorID         = database.allocCursorID();
            uint32_t         cursorRefID      = database.allocCursorID();

            createInsertTokensTableData (database, filePath, tokenID, tokenKind, tokenSpelling, tokenRange);

            createInsertCursorsTableData(database, filePath, cursorID,    cursorRefID, tokenID,    cursor);
            createInsertCursorsTableData(database, filePath, cursorRefID, 0          , 0      , cursorReferenced);
        }
    }

    if (tokensOut)
        clang_disposeTokens(translationUnit, tokensOut, tokensNum);
}

void createInsertTokensTableData(Database& database, const string& filePath, uint32_t tokenID, const CXTokenKind& tokenKind, const CXString& tokenSpelling, const CXSourceRange& tokenRange)
{
    CXSourceLocation rangeStart = clang_getRangeStart(tokenRange);
    CXSourceLocation rangeEnd   = clang_getRangeEnd(tokenRange);

    uint32_t startExpansionLine, startExpansioColumn;
    uint32_t endExpansionLine, endExpansioColumn;

    clang_getExpansionLocation(rangeStart, nullptr, &startExpansionLine, &startExpansioColumn, nullptr);
    clang_getExpansionLocation(rangeEnd,   nullptr, &endExpansionLine,   &endExpansioColumn,   nullptr);

    DatabaseInsertQuery insertQueryBuilder;
    insertQueryBuilder.newQuery(filePath + "\\tokens", g_tokenColumnDict);

    insertQueryBuilder.addColumnValue(TokenID,                  tokenID);
    insertQueryBuilder.addColumnValue(TokenKind,                (uint32_t)tokenKind);
    insertQueryBuilder.addCXStringColumnValue(TokenSpelling,    tokenSpelling);
    insertQueryBuilder.addColumnValue(TokenStartPos_Line,       startExpansionLine);
    insertQueryBuilder.addColumnValue(TokenStartPos_Col,        startExpansioColumn);
    insertQueryBuilder.addColumnValue(TokenEndPos_Line,         endExpansionLine);
    insertQueryBuilder.addColumnValue(TokenEndPos_Col,          endExpansioColumn);

    DatabaseQueryErrMsg tokenQueryErrMsg = database.sendQuery(insertQueryBuilder.buildQuery());
    if(database.isNotOK())
        cout << "sendQuery() error : " << tokenQueryErrMsg << endl;
}

void createInsertCursorsTableData(Database& database, const string& filePath, uint32_t cursorID, uint32_t cursorRefID, uint32_t tokenID, const CXCursor& cursor)
{
    CXString              mangling                            = clang_Cursor_getMangling(cursor);
    CXCursorKind          templateCursorKind                  = clang_getTemplateCursorKind(cursor);
    CXString              cursorUSR                           = clang_getCursorUSR(cursor);
    CXString              cursorDisplayName                   = clang_getCursorDisplayName(cursor);
    uint32_t              cursorHash                          = clang_hashCursor(cursor);
    CXCursorKind          cursorKind                          = clang_getCursorKind(cursor);
    CXString              cursorKindSpelling                  = clang_getCursorKindSpelling(cursorKind);

    DatabaseInsertQuery insertQueryBuilder;
    insertQueryBuilder.newQuery(filePath + "\\cursors", g_cursorColumnDict);

    insertQueryBuilder.addColumnValue(CursorID,                       cursorID);
    insertQueryBuilder.addColumnValue(TokenTable_TokenID,             tokenID);
    insertQueryBuilder.addCXStringColumnValue(CursorMangling,         mangling);
    insertQueryBuilder.addCXStringColumnValue(CursorUSR,              cursorUSR);
    insertQueryBuilder.addCXStringColumnValue(CursorDisplayName,      cursorDisplayName);
    insertQueryBuilder.addColumnValue(CursorTable_CursorReferenced,   cursorRefID);
    insertQueryBuilder.addColumnValue(CursorHash,                     cursorHash);
    insertQueryBuilder.addColumnValue(CursorKind,                     (uint32_t)cursorKind);
    insertQueryBuilder.addCXStringColumnValue(CursorKindSpelling,     cursorKindSpelling);

    DatabaseQueryErrMsg cursorQueryErrMsg = database.sendQuery(insertQueryBuilder.buildQuery());
    if(database.isNotOK())
        cout << "sendQuery() error : " << cursorQueryErrMsg << endl;
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
