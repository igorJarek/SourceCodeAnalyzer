#include <SourceCode/SourceCode.hpp>

#include <iostream>
#include <map>
#include <FolderBrowser/FolderBrowser.h>
#include <ExecutionTimeMeasurement/ExecutionTimeMeasurement.h>
#include <LibClangStruct2Str/LibClangStruct2Str.h>

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

    fb.addIgnoreFilePath("..\\lib\\src\\TestPrimitives.cpp");

    fb.startFolderBrowse(libPath);

    const size_t        fileCount = fb.getFileCount();
    const list<string>& fileList  = fb.getFileList();

    for(const string& filePath : fileList)
    {
        ExecutionTimeMeasurement timeMeasurement("Parsing " + filePath + " file in");

        map<string, Function> functionsDefMap;

        SourceCode sourceCode(filePath, COMPILATION_ARGS, 2);
        AST&       ast    = sourceCode.getAST();
        Tokens&    tokens = sourceCode.getTokens();

        ast.traversingAST
        (
            [&functionsDefMap](shared_ptr<ASTNode> astNode) -> void
            {
                CXCursor     cursor     = astNode->cursor;
                CXCursorKind cursorKind = clang_getCursorKind(cursor);

                if(cursorKind == CXCursor_FunctionDecl)
                {
                    if(clang_isCursorDefinition(cursor))
                    {
                        Function function;

                        function.kind     = 1;

                        function.usr      = to_string(clang_getCursorUSR(cursor));
                        function.mangling = to_string(clang_Cursor_getMangling(cursor));
                        function.pos.setCXSourceRange(clang_getCursorExtent(cursor));

                        function.name     = to_string(clang_getCursorSpelling(cursor));
                        function.argCount = clang_Cursor_getNumArguments(cursor);

                        functionsDefMap.insert( {function.usr, function} );
                    }
                }
                else if(cursorKind == CXCursor_CXXMethod)
                {
                    if(clang_isCursorDefinition(cursor))
                    {
                        Function function;

                        function.kind     = 2;

                        function.usr      = to_string(clang_getCursorUSR(cursor));
                        function.mangling = to_string(clang_Cursor_getMangling(cursor));
                        function.pos.setCXSourceRange(clang_getCursorExtent(cursor));

                        function.name     = to_string(clang_getCursorSpelling(cursor));
                        function.argCount = clang_Cursor_getNumArguments(cursor);

                        functionsDefMap.insert( {function.usr, function} );
                    }
                }
                else if(cursorKind == CXCursor_CallExpr)
                {
                    Function function;

                    function.kind     = 3;

                    function.pos.setCXSourceRange(clang_getCursorExtent(cursor));

                    function.name     = to_string(clang_getCursorSpelling(cursor));
                    function.argCount = clang_Cursor_getNumArguments(cursor);

                    CXCursor     ref        = clang_getCursorReferenced(cursor);
                    CXCursorKind cursorRefKind = clang_getCursorKind(ref);

                    if(!clang_isInvalid(cursorRefKind) && cursorRefKind != CXCursor_Constructor && cursorRefKind != CXCursor_Destructor)
                    {
                        if(!clang_equalCursors(cursor, ref))
                        {
                            function.usr      = to_string(clang_getCursorUSR(ref));
                            function.mangling = to_string(clang_Cursor_getMangling(ref));

                            functionsDefMap.insert( {function.usr, function} );
                        }
                    }
                }
            }
        );

        if(functionsDefMap.size())
        {
            cout << "\tResult : " << endl; 

            for(auto& elem : functionsDefMap)
            {
                cout << "\t\t";
                cout << (elem.second.kind == 3 ? "Invoke : " : "Def : ");
                cout << elem.first << " -> " << elem.second.name << endl;
            }
        }
    }

    return EXIT_SUCCESS;
}

