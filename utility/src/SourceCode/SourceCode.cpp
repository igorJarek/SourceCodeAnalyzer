#include "SourceCode/SourceCode.h"

#include <fstream>

CXChildVisitResult visitor(CXCursor cursor, CXCursor /* parent */, CXClientData client_data);

shared_ptr<ASTNode> ASTNode::findChild(enum CXCursorKind cursorKind)
{
    for(shared_ptr<ASTNode> elem : childrens)
    {
        if(elem->cursor.kind == cursorKind)
            return elem;
        else
        {
            shared_ptr<ASTNode> found = elem->findChild(cursorKind);
            if(found)
                return found;
        }
    }

    return nullptr;
}

AST::AST()
{
    m_root = std::make_shared<ASTNode>();
    m_root->parent = nullptr;
}

AST::~AST()
{
    
}

void AST::addCXCursor(uint32_t level, CXCursor cursor)
{
    shared_ptr<ASTNode> currentNode = m_root;

    for(uint32_t indexLevel = 0; indexLevel < level; ++indexLevel)
    {
        if(!currentNode->childrens.empty())
            currentNode = currentNode->childrens.back();
    }

    shared_ptr<ASTNode> newNode = std::make_shared<ASTNode>();
    newNode->parent = currentNode;
    newNode->cursor = cursor;

    currentNode->childrens.push_back(newNode);

    ++m_nodes;
}

void AST::traversingAST(function<void (shared_ptr<ASTNode>)> traversingFunc)
{
    auto& rootChildren = m_root->childrens;
    for(auto& elem : rootChildren)
        traversingNode(traversingFunc, elem);
}

void AST::traversingNode(function<void (shared_ptr<ASTNode>)> traversingFunc, shared_ptr<ASTNode>& node)
{
    if(traversingFunc)
        traversingFunc(node);

    auto& nodeChildren = node->childrens;
    for(auto& elem : nodeChildren)
        traversingNode(traversingFunc, elem);
}

SourceCode::SourceCode(const string& filePath, const char* compilation_args[], uint16_t argsCount) :
    m_filePath(filePath)
{
    m_index = clang_createIndex(0, 0);

    m_compilationErrorCode = clang_parseTranslationUnit2(m_index, 
                                                         m_filePath.c_str(),
                                                         compilation_args,
                                                         argsCount,
                                                         nullptr,
                                                         0,
                                                         CXTranslationUnit_None,
                                                         &m_translationUnit);

    m_compilationErrorCount = clang_getNumDiagnostics(m_translationUnit);

    if(m_compilationErrorCount)
    {
        for (uint32_t errorIndex = 0; errorIndex < m_compilationErrorCount; ++errorIndex)
        {
            CXDiagnostic         diagnostic = clang_getDiagnostic(m_translationUnit, errorIndex);

            CXDiagnosticSeverity diagnosticSeverity = clang_getDiagnosticSeverity(diagnostic);
            CXString             formatDiagnostic = clang_formatDiagnostic(diagnostic, CXDiagnostic_DisplaySourceLocation | CXDiagnostic_DisplayColumn |
                                                                                       CXDiagnostic_DisplaySourceRanges   | CXDiagnostic_DisplayOption |
                                                                                       CXDiagnostic_DisplayCategoryId     | CXDiagnostic_DisplayCategoryName);

            // print this message to cerr ?
            string errorMessage =  to_string(diagnosticSeverity) + " : " + to_string(formatDiagnostic);

            clang_disposeDiagnostic(diagnostic);
        }
    }

    // AST

    if (m_compilationErrorCode == CXError_Success /*&& m_compilationErrorCount == 0 */)
    {
        ClientData clientData(&m_ast);

        CXCursor cursor = clang_getTranslationUnitCursor(m_translationUnit);
        clang_visitChildren(cursor, visitor, &clientData);
    }

    // tokenize whole file

    m_rawTokens.fileLines = countFileLines(filePath);
    if (m_rawTokens.fileLines != -1 /*&& m_compilationErrorCount == 0 */)
    {
        m_rawTokens.fileLastLineColumns = countFileLineColumns(filePath, m_rawTokens.fileLines);
        if(m_rawTokens.fileLastLineColumns == 0)
            m_rawTokens.fileLastLineColumns = 1;

        if(m_rawTokens.fileLastLineColumns != -1)
        {
            CXFile           file           = clang_getFile(m_translationUnit, filePath.c_str());
            CXSourceLocation beginLocation  = clang_getLocation(m_translationUnit, file, 1, 1);
            CXSourceLocation endLocation    = clang_getLocation(m_translationUnit, file, static_cast<unsigned int>(m_rawTokens.fileLines), 
                                                                                         static_cast<unsigned int>(m_rawTokens.fileLastLineColumns));
            CXSourceRange    tokenizerRange = clang_getRange(beginLocation, endLocation);

            clang_tokenize(m_translationUnit, tokenizerRange, &m_rawTokens.tokens, &m_rawTokens.tokensCount);
        }
    }

    // building tokens

    if(m_rawTokens.tokensCount /* && m_compilationErrorCount == 0 */)
    {
        for (uint32_t index{ 0 }; index < m_rawTokens.tokensCount; ++index)
        {
            const CXToken&   rawToken         = m_rawTokens.tokens[index];

            CXTokenKind      rawTokenKind     = clang_getTokenKind(rawToken);
            CXString         rawTokenSpelling = clang_getTokenSpelling(m_translationUnit, rawToken);
            CXSourceLocation rawTokenLocation = clang_getTokenLocation(m_translationUnit, rawToken);
            CXSourceRange    rawTokenRange    = clang_getTokenExtent(m_translationUnit, rawToken);

            m_tokens.emplace_back(0, rawTokenKind, to_string(rawTokenSpelling), rawTokenLocation, rawTokenRange);
        }
    }
}

SourceCode::~SourceCode()
{
    clang_disposeTokens(m_translationUnit, m_rawTokens.tokens, m_rawTokens.tokensCount);
    clang_disposeTranslationUnit(m_translationUnit);
    clang_disposeIndex(m_index);
}

CXChildVisitResult visitor(CXCursor cursor, CXCursor /* parent */, CXClientData client_data)
{
    ClientData* clientDataPtr = reinterpret_cast<ClientData*>(client_data);
    AST* ast    = clientDataPtr->m_ast;

    ast->addCXCursor(ast->getNestingLevel(), cursor);

    ast->increaseNestingLevel();

    clang_visitChildren(cursor, visitor, client_data);

    ast->decreaseNestingLevel();

    return CXChildVisit_Continue;
}

int64_t SourceCode::countFileLines(const string& filePath)
{
    std::fstream stream;
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

int64_t SourceCode::countFileLineColumns(const string& filePath, int64_t line)
{
    if (line < 0)
        return -1;

    std::fstream stream;
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