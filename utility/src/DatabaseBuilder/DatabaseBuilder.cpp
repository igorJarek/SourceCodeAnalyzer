#include <DatabaseBuilder/DatabaseBuilder.hpp>

#include <Database/DatabaseColumnDict.h>
#include <Database/ColumnDefinition.h>

DatabaseBuilder::DatabaseBuilder(Database& database, 
                                 const string& appName, const string& appVersion, 
                                 const FolderBrowser& folderBrowser, 
                                 const char* compilationArgs[], uint32_t argsCount) :
    m_database(database),

    m_appName(appName),
    m_appVersion(appVersion),

    m_folderBrowser(folderBrowser),

    m_compilationArgs(compilationArgs),
    m_argsCount(argsCount)
{
    m_database.openDatabase(DatabaseOptions::TRUNCATE_DB_FILE   |
                            DatabaseOptions::READ_WRITE_DB_FILE |
                            DatabaseOptions::FILE_DB_FILE
                            );


}

DatabaseBuilder::~DatabaseBuilder()
{
    
}

void DatabaseBuilder::createDatabaseTables(const string& filePath)
{
    string dbErrMsg = m_database.createSourceCodeTables(filePath);
    if(m_database.isNotOK())
    {
        cout << dbErrMsg;
        return;
    }
}

void DatabaseBuilder::createInsertTokensTableData(const string& filePath, uint32_t tokenID, const CXTokenKind& tokenKind, const CXString& tokenSpelling, const CXSourceRange& tokenRange)
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

    DatabaseQueryErrMsg tokenQueryErrMsg = m_database.sendQuery(insertQueryBuilder.buildQuery());
    if(m_database.isNotOK())
        cout << "sendQuery() error : " << tokenQueryErrMsg << endl;
}

void DatabaseBuilder::buildDatabase(function<void (const string& filePath, size_t fileIndex, size_t fileCount)> buildState)
{
    const list<string>& fileList    = m_folderBrowser.getFileList();
    size_t              fileCounter = 0;

    string dbErrMsg = m_database.createGlobalTable(clang_getClangVersion(), m_appName, m_appVersion);
    if(m_database.isNotOK())
    {
        cout << dbErrMsg << endl;
        return;
    }

    dbErrMsg = m_database.createFileListTable();
    if(m_database.isNotOK())
    {
        cout << dbErrMsg << endl;
        return;
    }

    for(const string& filePath : fileList)
    {
        buildState(filePath, fileCounter++, m_folderBrowser.getFileCount());

        SourceCode sourceCode(filePath, m_compilationArgs, m_argsCount);
        const CXTranslationUnit& tu     = sourceCode.getTranslationUnit(); 
        const AST&               ast    = sourceCode.getAST();
        const Tokens&            tokens = sourceCode.getTokens();

        createDatabaseTables(filePath);

        if(tokens.tokensCount)
        {
            for (uint32_t index{ 0 }; index < tokens.tokensCount; ++index)
            {
                const CXToken&   token = tokens.tokens[index];

                CXTokenKind      tokenKind     = clang_getTokenKind(token);
                CXString         tokenSpelling = clang_getTokenSpelling(tu, token);
                CXSourceRange    tokenRange    = clang_getTokenExtent(tu, token);

                uint32_t         tokenID       = m_database.allocTokenID();

                createInsertTokensTableData(filePath, tokenID, tokenKind, tokenSpelling, tokenRange);
            }
        }

        /*
        ExecutionTimeMeasurement timeMeasurement("Parsing " + filePath + " file in");

        map<string, Function> functionsDefMap;

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
        */
    }
}