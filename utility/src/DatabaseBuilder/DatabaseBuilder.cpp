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
    m_database.openDatabase(DatabaseOptions::READ_WRITE_DB_FILE |
                            DatabaseOptions::IN_MEMORY_DB_FILE
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

void DatabaseBuilder::createInsertTokensTableData(const string& filePath, const Token& token)
{
    CXSourceLocation rangeStart = clang_getRangeStart(token.tokenRange);
    CXSourceLocation rangeEnd   = clang_getRangeEnd(token.tokenRange);

    uint32_t startExpansionLine, startExpansioColumn;
    uint32_t endExpansionLine, endExpansioColumn;

    clang_getExpansionLocation(rangeStart, nullptr, &startExpansionLine, &startExpansioColumn, nullptr);
    clang_getExpansionLocation(rangeEnd,   nullptr, &endExpansionLine,   &endExpansioColumn,   nullptr);

    DatabaseInsertQuery insertQueryBuilder;
    insertQueryBuilder.newQuery(filePath + "\\tokens", g_tokenColumnDict);

    insertQueryBuilder.addColumnValue(TokenID,            token.tokenID);
    insertQueryBuilder.addColumnValue(TokenKind,          (uint32_t)token.tokenKind);
    insertQueryBuilder.addColumnValue(TokenSpelling,      token.tokenSpelling);
    insertQueryBuilder.addColumnValue(TokenStartPos_Line, startExpansionLine);
    insertQueryBuilder.addColumnValue(TokenStartPos_Col,  startExpansioColumn);
    insertQueryBuilder.addColumnValue(TokenEndPos_Line,   endExpansionLine);
    insertQueryBuilder.addColumnValue(TokenEndPos_Col,    endExpansioColumn);

    const string& query = insertQueryBuilder.buildQuery();
    DatabaseQueryErrMsg tokenQueryErrMsg = m_database.sendQuery(query);
    if(m_database.isNotOK())
    {
        cout << "sendQuery() error in query : " << query << endl;
        cout << "Error message : " << tokenQueryErrMsg << endl;
    }
}

void DatabaseBuilder::createInsertCallingTableData(const string& filePath, const DatabaseBuilderCalling& calling)
{
    DatabaseInsertQuery insertQueryBuilder;
    insertQueryBuilder.newQuery(filePath + "\\calling", g_callingColumnDict);

    insertQueryBuilder.addColumnValue(CalllingID,         calling.callingID);
    insertQueryBuilder.addColumnValue(CallingNameTokenID, calling.functionNameTokenID);
    insertQueryBuilder.addColumnValue(CallingFilePath,    calling.functionDefinitionPath);
    insertQueryBuilder.addColumnValue(CallingFunctionID,  calling.functionDefinitionID);

    const string& query = insertQueryBuilder.buildQuery();
    DatabaseQueryErrMsg tokenQueryErrMsg = m_database.sendQuery(query);
    if(m_database.isNotOK())
    {
        cout << "sendQuery() error in query : " << query << endl;
        cout << "Error message : " << tokenQueryErrMsg << endl;
    }
}

void DatabaseBuilder::createInsertFunctionsTableData(const string& filePath, const DatabaseBuilderFunction& function)
{
    DatabaseInsertQuery insertQueryBuilder;
    insertQueryBuilder.newQuery(filePath + "\\functions", g_functionsColumnDict);

    insertQueryBuilder.addColumnValue(FunctionsID,             function.functionID);
    insertQueryBuilder.addColumnValue(FunctionsNameTokenID,    function.functionNameTokenID);
    insertQueryBuilder.addColumnValue(FunctionOpenDefTokenID,  function.openDefinitionTokenID);
    insertQueryBuilder.addColumnValue(FunctionCloseDefTokenID, function.closeDefinitionTokenID);

    const string& query = insertQueryBuilder.buildQuery();
    DatabaseQueryErrMsg tokenQueryErrMsg = m_database.sendQuery(query);
    if(m_database.isNotOK())
    {
        cout << "sendQuery() error in query : " << query << endl;
        cout << "Error message : " << tokenQueryErrMsg << endl;
    }
}

void DatabaseBuilder::buildDatabase(function<void (const string& filePath, size_t fileIndex, size_t fileCount)> buildState)
{
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

    const list<string>&                 fileList    = m_folderBrowser.getFileList();
    map<string, shared_ptr<SourceCode>> headerSourceFileMap;
    size_t                              fileCounter = 0;

    for(const string& filePath : fileList)
        headerSourceFileMap.emplace(filePath, make_shared<SourceCode>(filePath, m_compilationArgs, m_argsCount));

    for(const auto& [filePath, SourceCodePtr] : headerSourceFileMap)
    {
        buildState(filePath, fileCounter++, m_folderBrowser.getFileCount());

        shared_ptr<SourceCode>   sourceCode = SourceCodePtr;
        AST&                     ast        = sourceCode->getAST();
        list<Token>&             tokens     = sourceCode->getTokens();

        createDatabaseTables(filePath);

        for(Token& token : tokens)
        {
            if(token.tokenID == 0)
                token.tokenID = m_database.allocTokenID();

            createInsertTokensTableData(filePath, token);
        }

        ast.traversingAST
        (
            [this, &tokens, &headerSourceFileMap](shared_ptr<ASTNode> astNode) -> void
            {
                CXCursor     cursor     = astNode->cursor;
                CXCursorKind cursorKind = clang_getCursorKind(cursor);

                if(cursorKind == CXCursor_FunctionDecl ||
                   cursorKind == CXCursor_CXXMethod)
                {
                    if(clang_isCursorDefinition(cursor))
                    {
                        DatabaseBuilderFunction dbFunction;
                        dbFunction.functionID = m_database.allocFunctionsID();
                        dbFunction.functionName = to_string(clang_getCursorSpelling(cursor));
                        dbFunction.functionNamePos.setCXSourceLocation(clang_getCursorLocation(cursor));
                        dbFunction.functionDefRange.setCXSourceRange(clang_getCursorExtent(cursor));

                        for(Token& token : tokens)
                        {
                            if(token.getTokenPos() == dbFunction.functionNamePos)
                                dbFunction.functionNameTokenID = token.tokenID;
                            else if(token.isStartsEqual(dbFunction.functionDefRange))
                                dbFunction.openDefinitionTokenID = token.tokenID;
                            else if(token.isEndsEqual(dbFunction.functionDefRange))
                                dbFunction.closeDefinitionTokenID = token.tokenID;
                        }

                        m_functionsMap.insert( {to_string(clang_getCursorUSR(cursor)), dbFunction} );
                    }
                }
                else if(cursorKind == CXCursor_CallExpr)
                {
                    CXCursor              cursorRef     = clang_getCursorReferenced(cursor);
                    CXCursorKind          cursorRefKind = clang_getCursorKind(cursorRef);

                    if(!clang_isInvalid(cursorRefKind)        &&
                        cursorRefKind != CXCursor_Constructor &&
                        cursorRefKind != CXCursor_Destructor)
                    {
                        if(!clang_equalCursors(cursor, cursorRef))
                        {
                            if(clang_isCursorDefinition(cursorRef))
                            {
                                if(cursorRefKind == CXCursor_FunctionDecl) // template after included is function
                                {
                                    DatabaseBuilderFunction dbFunction;
                                    dbFunction.functionID = m_database.allocFunctionsID();
                                    dbFunction.functionName = to_string(clang_getCursorSpelling(cursorRef));
                                    dbFunction.functionNamePos.setCXSourceLocation(clang_getCursorLocation(cursorRef)); 
                                    dbFunction.functionDefRange.setCXSourceRange(clang_getCursorExtent(cursorRef));

                                    map<string, shared_ptr<SourceCode>>::iterator refFileTokensIter = headerSourceFileMap.find(dbFunction.functionNamePos.fileName);
                                    if(refFileTokensIter != headerSourceFileMap.end())
                                    {
                                        list<Token>& refFileTokens = refFileTokensIter->second->getTokens();

                                        for(Token& token : refFileTokens)
                                        {
                                            if(token.tokenID == 0)
                                                token.tokenID = m_database.allocTokenID();

                                            if(token.getTokenPos() == dbFunction.functionNamePos)
                                                dbFunction.functionNameTokenID = token.tokenID;
                                            else if(token.isStartsEqual(dbFunction.functionDefRange))
                                                dbFunction.openDefinitionTokenID = token.tokenID;
                                            else if(token.isEndsEqual(dbFunction.functionDefRange))
                                                dbFunction.closeDefinitionTokenID = token.tokenID;
                                        }

                                        m_functionsMap.insert( {to_string(clang_getCursorUSR(cursorRef)), dbFunction} );
                                    }
                                }
                            }

                            DatabaseBuilderCalling dbCalling;
                            dbCalling.callingID = m_database.allocCallingID();
                            dbCalling.functionName = to_string(clang_getCursorSpelling(cursor));

                            if(cursorRefKind == CXCursor_CXXMethod)
                            {
                                shared_ptr<ASTNode> memberRefExp = astNode->findChild(CXCursor_MemberRefExpr);
                                if(memberRefExp)
                                    dbCalling.functionNamePos.setCXSourceLocation(clang_getCursorLocation(memberRefExp->cursor));
                            }
                            else
                            {
                                dbCalling.functionNamePos.setCXSourceLocation(clang_getCursorLocation(cursor));
                            }

                            for(Token& token : tokens)
                            {
                                if(token.tokenSpelling == dbCalling.functionName)
                                if(token.getTokenPos() == dbCalling.functionNamePos)
                                    dbCalling.functionNameTokenID = token.tokenID;
                            }

                            m_callingMap.insert( {to_string(clang_getCursorUSR(cursorRef)), dbCalling} );
                        }
                    }
                }
            }
        );
    }

    for(const string& filePath : fileList)
    {
        for(auto& [usr, dbCalling] : m_callingMap)
        {
            if(dbCalling.functionNamePos.fileName == filePath)
            {
                map<string, DatabaseBuilderFunction>::iterator it = m_functionsMap.find(usr);
                if(it != m_functionsMap.end())
                {
                    const DatabaseBuilderFunction& definition = it->second;
                    dbCalling.functionDefinitionID = definition.functionID;
                    dbCalling.functionDefinitionPath = definition.functionNamePos.fileName;

                    createInsertCallingTableData(filePath, dbCalling);
                }
            }
        }

        for(const auto& [usr, dbFunction] : m_functionsMap)
        {
            if(dbFunction.functionNamePos.fileName == filePath)
                createInsertFunctionsTableData(filePath, dbFunction);
        }
    }

    /*
    for(const string& filePath : fileList)
    {
        cout << "Result " << filePath << " : " << endl; 

        for(const auto& [usr, dbCalling] : m_callingMap)
        {
            if(dbCalling.functionNamePos.fileName == filePath)
            {
                map<string, DatabaseBuilderFunction>::iterator it = m_functionsMap.find(usr);
                if(it != m_functionsMap.end())
                {
                    cout << "\tInvoke : " << endl;
                    cout << "\t\tFunctionName : " << dbCalling.functionName << ' ' << endl;
                    cout << "\t\tFunctionPath : " << dbCalling.functionNamePos.fileName << endl;
                    cout << "\t\tTokenID : " << dbCalling.functionNameTokenID << endl;
                    cout << "\t\tUSR : " << usr << endl;
                }
            }
        }

        for(const auto& [usr, dbFunction] : m_functionsMap)
        {
            if(dbFunction.functionNamePos.fileName == filePath)
            {
                cout << "\tDefinition : " << endl;
                cout << "\t\tFunctionName : " << dbFunction.functionName << ' ' << endl;
                cout << "\t\tFunctionPath : " << dbFunction.functionNamePos.fileName << endl;
                cout << "\t\tTokenID : " << dbFunction.functionNameTokenID << endl;
                cout << "\t\tUSR : " << usr << endl;
            }
        }
    }
    */
}
