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

void createInsertTokensTableData(Database& database, const string& filePath, uint32_t tokenID, const CXTokenKind& tokenKind, const CXString& tokenSpelling, const CXSourceRange& tokenRange);
void createInsertCursorsTableData(Database& database, const string& filePath, uint32_t cursorID, uint32_t cursorRefID, uint32_t tokenID, uint32_t typeID, const CXCursor& cursor);
void createInsertTypesTableData(Database& database, const string& filePath, uint32_t typeID, const CXType& cursorType);

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
    const list<string>& fileFile  = fb.getFileList();

    Database database(databasePath);
    database.openDatabase(DatabaseOptions::TRUNCATE_DB_FILE   | 
                          DatabaseOptions::READ_WRITE_DB_FILE | 
                          DatabaseOptions::FILE_DB_FILE       |
                          DatabaseOptions::DUMP_QUERIES_TO_FILE);

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

            uint32_t         typeID           = database.allocTypeID();
            uint32_t         typeRefID        = database.allocTypeID();

            createInsertTokensTableData (database, filePath, tokenID, tokenKind, tokenSpelling, tokenRange);

            createInsertCursorsTableData(database, filePath, cursorID,    cursorRefID, tokenID, typeID,    cursor);
            createInsertCursorsTableData(database, filePath, cursorRefID, 0          , 0,       typeRefID, cursorReferenced);

            createInsertTypesTableData  (database, filePath, typeID,    cursorType);
            createInsertTypesTableData  (database, filePath, typeRefID, cursorRefType);
        }
    }

    if (tokensOut)
        clang_disposeTokens(translationUnit, tokensOut, tokensNum);
}

void createInsertTokensTableData(Database& database, const string& filePath, uint32_t tokenID, const CXTokenKind& tokenKind, const CXString& tokenSpelling, const CXSourceRange& tokenRange)
{
    CXSourceLocation rangeStart = clang_getRangeStart(tokenRange);
    CXSourceLocation rangeEnd   = clang_getRangeEnd(tokenRange);

    int64_t tokenStartPos, tokenEndPos;

    uint32_t startExpansionLine, startExpansioColumn;
    uint32_t endExpansionLine, endExpansioColumn;

    clang_getExpansionLocation(rangeStart, nullptr, &startExpansionLine, &startExpansioColumn, nullptr);
    clang_getExpansionLocation(rangeEnd,   nullptr, &endExpansionLine,   &endExpansioColumn,   nullptr);

    tokenStartPos = startExpansionLine << 31 | startExpansioColumn;
    tokenEndPos   = endExpansionLine   << 31 | endExpansioColumn;

    DatabaseInsertQuery insertQueryBuilder;
    insertQueryBuilder.newQuery(filePath + "\\tokens", g_tokenColumnDict);

    insertQueryBuilder.addColumnValue(TokenID,                        tokenID);
    insertQueryBuilder.addColumnValue(TokenKind,                      (uint32_t)tokenKind);
    insertQueryBuilder.addCXStringColumnValue(TokenSpelling,          tokenSpelling);
    insertQueryBuilder.addColumnValue(TokenStartPos,                  tokenStartPos);
    insertQueryBuilder.addColumnValue(TokenEndPos,                    tokenEndPos);

    DatabaseQueryErrMsg tokenQueryErrMsg = database.sendQuery(insertQueryBuilder.buildQuery());
    if(database.isNotOK())
        cout << "sendQuery() error : " << tokenQueryErrMsg << endl;
}

void createInsertCursorsTableData(Database& database, const string& filePath, uint32_t cursorID, uint32_t cursorRefID, uint32_t tokenID, uint32_t typeID, const CXCursor& cursor)
{
    CXString              mangling                            = clang_Cursor_getMangling(cursor);
    CXCursorKind          templateCursorKind                  = clang_getTemplateCursorKind(cursor);
    CXString              cursorUSR                           = clang_getCursorUSR(cursor);
    CXString              cursorDisplayName                   = clang_getCursorDisplayName(cursor);
    int64_t               cursorEnumConstantDeclValue         = clang_getEnumConstantDeclValue(cursor);
    uint64_t              cursorEnumConstantDeclUnsignedValue = clang_getEnumConstantDeclUnsignedValue(cursor);
    int32_t               cursorFieldDeclBitWidth             = clang_getFieldDeclBitWidth(cursor);
    int32_t               cursorExceptionSpecificationType    = clang_getCursorExceptionSpecificationType(cursor);
    int64_t               cursorOffsetOfField                 = clang_Cursor_getOffsetOfField(cursor);
    CX_CXXAccessSpecifier cursorAccessSpecifier               = clang_getCXXAccessSpecifier(cursor);
    CX_StorageClass       cursorStorageClass                  = clang_Cursor_getStorageClass(cursor);
    CXEvalResultKind      cursorEvalResultKind                = clang_EvalResult_getKind(clang_Cursor_Evaluate(cursor));
    uint32_t              cursorHash                          = clang_hashCursor(cursor);
    CXCursorKind          cursorKind                          = clang_getCursorKind(cursor);
    uint32_t              hasAttrs                            = clang_Cursor_hasAttrs(cursor);
    CXLinkageKind         linkageKind                         = clang_getCursorLinkage(cursor);
    CXVisibilityKind      visibilityKind                      = clang_getCursorVisibility(cursor);
    CXAvailabilityKind    availabilityKind                    = clang_getCursorAvailability(cursor);
    CXLanguageKind        cursorLanguageKind                  = clang_getCursorLanguage(cursor);
    CXTLSKind             tlsKind                             = clang_getCursorTLSKind(cursor);

    DatabaseInsertQuery insertQueryBuilder;
    insertQueryBuilder.newQuery(filePath + "\\cursors", g_sourceCodeColumnDict);

    insertQueryBuilder.addColumnValue(CursorID,                       cursorID);
    insertQueryBuilder.addColumnValue(TokenTable_TokenID,             tokenID);
    insertQueryBuilder.addCXStringColumnValue(CursorMangling,         mangling);
    insertQueryBuilder.addColumnValue(CursorIsBits,                   0);
    insertQueryBuilder.addColumnValue(CursorTemplateCursorKind,       (uint32_t)templateCursorKind);
    insertQueryBuilder.addCXStringColumnValue(CursorUSR,              cursorUSR);
    insertQueryBuilder.addCXStringColumnValue(CursorDisplayName,      cursorDisplayName);
    insertQueryBuilder.addColumnValue(CursorTable_CursorReferenced,   cursorRefID);
    insertQueryBuilder.addColumnValue(TypeTable_CursorType,           typeID);
    insertQueryBuilder.addColumnValue(CursorEnumConstantDeclValue,    cursorEnumConstantDeclValue);
    insertQueryBuilder.addColumnValue(CursorEnumConstantDeclUValue,   cursorEnumConstantDeclUnsignedValue);
    insertQueryBuilder.addColumnValue(CursorFieldDeclBitWidth,        cursorFieldDeclBitWidth);
    insertQueryBuilder.addColumnValue(CursorExceptionSpecification,   cursorExceptionSpecificationType);
    insertQueryBuilder.addColumnValue(CursorOffsetOfField,            cursorOffsetOfField);
    insertQueryBuilder.addColumnValue(CursorAccessSpecifier,          (uint32_t)cursorAccessSpecifier);
    insertQueryBuilder.addColumnValue(CursorStorageClass,             (uint32_t)cursorStorageClass);
    insertQueryBuilder.addColumnValue(CursorEvalResultKind,           (uint32_t)cursorEvalResultKind);
    insertQueryBuilder.addColumnValue(CursorHash,                     cursorHash);
    insertQueryBuilder.addColumnValue(CursorKind,                     (uint32_t)cursorKind);
    insertQueryBuilder.addColumnValue(CursorAttr,                     hasAttrs);
    insertQueryBuilder.addColumnValue(CursorLinkageKind,              (uint32_t)linkageKind);
    insertQueryBuilder.addColumnValue(CursorVisibilityKind,           (uint32_t)visibilityKind);
    insertQueryBuilder.addColumnValue(CursorAvailabilityKind,         (uint32_t)availabilityKind);
    insertQueryBuilder.addColumnValue(CursorLanguageKind,             (uint32_t)cursorLanguageKind);
    insertQueryBuilder.addColumnValue(CursorTLSKind,                  (uint32_t)tlsKind);

    DatabaseQueryErrMsg cursorQueryErrMsg = database.sendQuery(insertQueryBuilder.buildQuery());
    if(database.isNotOK())
        cout << "sendQuery() error : " << cursorQueryErrMsg << endl;
}

void createInsertTypesTableData(Database& database, const string& filePath, uint32_t typeID, const CXType& cursorType)
{
    CXString              typeSpelling = clang_getTypeSpelling(cursorType);
    uint32_t              typeAddressSpace  = 0;
    CXString              typeTypedefName;
    CXString              typeKindSpelling;
    CXCallingConv         typeFunctionTypeCallingConv = CXCallingConv_Invalid;
    int32_t               typeExceptionSpecification = 0;
    int64_t               typeArraySize = 0;
    CXTypeNullabilityKind typeNullability = CXTypeNullability_Invalid;
    int64_t               typeAlignOf = 0;
    int64_t               typeSizeOf = 0;
    CXRefQualifierKind    typeRefQualifier = CXRefQualifier_None;
            
    if( cursorType.kind != CXType_Invalid)
    if( cursorType.kind != CXType_Unexposed)
    {
        typeAddressSpace            = clang_getAddressSpace(cursorType);
        typeTypedefName             = clang_getTypedefName(cursorType);
        typeKindSpelling            = clang_getTypeKindSpelling(cursorType.kind);
        typeFunctionTypeCallingConv = clang_getFunctionTypeCallingConv(cursorType);
        typeExceptionSpecification  = clang_getExceptionSpecificationType(cursorType);
        typeArraySize               = clang_getArraySize(cursorType);
        typeNullability             = clang_Type_getNullability(cursorType);
        typeAlignOf                 = clang_Type_getAlignOf(cursorType);
        typeSizeOf                  = clang_Type_getSizeOf(cursorType);
        typeRefQualifier            = clang_Type_getCXXRefQualifier(cursorType);
    }

    DatabaseInsertQuery insertQueryBuilder;
    insertQueryBuilder.newQuery(filePath + "\\types", g_typeColumnDict);

    insertQueryBuilder.addColumnValue(TypeID,                         typeID);
    insertQueryBuilder.addCXStringColumnValue(TypeSpelling,           typeSpelling);

    if( cursorType.kind != CXType_Invalid)
    if( cursorType.kind != CXType_Unexposed)
    {
        insertQueryBuilder.addColumnValue(TypeIsBits,                     0);
        insertQueryBuilder.addColumnValue(TypeAddressSpace,               typeAddressSpace);
        insertQueryBuilder.addCXStringColumnValue(TypeTypedefName,        typeTypedefName);
        insertQueryBuilder.addCXStringColumnValue(TypeKindSpelling,       typeKindSpelling);
        insertQueryBuilder.addColumnValue(TypeFuncCallingConv,            (uint32_t)typeFunctionTypeCallingConv);
        insertQueryBuilder.addColumnValue(TypeExceptionSpecification,     typeExceptionSpecification);
        insertQueryBuilder.addColumnValue(TypeArraySize,                  typeArraySize);
        insertQueryBuilder.addColumnValue(TypeNullabilityKind,            (uint32_t)typeNullability);
        insertQueryBuilder.addColumnValue(TypeAlignOf,                    typeAlignOf);
        insertQueryBuilder.addColumnValue(TypeSizeOf,                     typeSizeOf);
        insertQueryBuilder.addColumnValue(TypeRefQualifierKind,           (uint32_t)typeRefQualifier);
    }

    DatabaseQueryErrMsg typeQueryErrMsg = database.sendQuery(insertQueryBuilder.buildQuery());
    if(database.isNotOK())
        cout << "sendQuery() error : " << typeQueryErrMsg << endl;
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
