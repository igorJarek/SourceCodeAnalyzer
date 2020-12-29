#pragma once

#include <LibClangStruct2Str/LibClangStruct2Str.h>

#include <clang-c/Index.h>

#include <list>
#include <string>
#include <memory>
#include <functional>

using std::list;
using std::string;
using std::to_string;
using std::shared_ptr;
using std::function;

/*         AST         */

struct ASTNode
{
    shared_ptr<ASTNode>       findChild(enum CXCursorKind cursorKind);

    shared_ptr<ASTNode>       parent;
    list<shared_ptr<ASTNode>> childrens;

    CXCursor                  cursor;
};

struct AST
{
    public:
        AST();
        ~AST();

    public:
        uint32_t getNodesCount() const { return m_nodes; }

        void     addCXCursor(uint32_t level, CXCursor cursor);
        void     traversingAST(function<void (shared_ptr<ASTNode>)> traversingFunc);

        uint32_t getNestingLevel()      const { return m_nestingLevel; }
        void     increaseNestingLevel()       { m_nestingLevel++; }
        void     decreaseNestingLevel()       { m_nestingLevel--; }

    private:
        void     traversingNode(function<void (shared_ptr<ASTNode>)> traversingFunc, shared_ptr<ASTNode>& node);

    private:
        shared_ptr<ASTNode> m_root;
        uint32_t            m_nodes = 0;

        uint32_t            m_nestingLevel = 0;
};

/*         ClientData         */

class ClientData
{
public:
    ClientData(AST* ast) :
        m_ast(ast) 
    { }

    AST* m_ast;
};

/*         Tokens         */

struct TokenPos
{
    TokenPos() {}
    TokenPos(const CXSourceLocation& location)
    {
        setCXSourceLocation(location);
    }

    void setCXSourceLocation(const CXSourceLocation& location)
    {
        CXFile file;
        clang_getExpansionLocation(location, &file, &linePos, &colPos, nullptr);

        fileName = to_string(clang_getFileName(file)); 
    }

    bool operator==(const TokenPos& right) const
    {
        return linePos == right.linePos && colPos == right.colPos;
    }

    string   fileName;

    uint32_t linePos = 0;
    uint32_t colPos  = 0;
};

struct TokenRange
{
    TokenRange() {}
    TokenRange(const CXSourceRange& range)
    {
        setCXSourceRange(range);
    }

    void setCXSourceRange(const CXSourceRange& range)
    {
        CXSourceLocation locStart  = clang_getRangeStart(range);
        CXSourceLocation locEnd    = clang_getRangeEnd(range);

        CXFile file;

        clang_getExpansionLocation(locStart, &file,   &startLine, &startCol, nullptr);
        clang_getExpansionLocation(locEnd,   nullptr, &endLine,   &endCol,   nullptr);

        fileName = to_string(clang_getFileName(file)); 
    }

    string   fileName;

    uint32_t startLine = 0;
    uint32_t startCol  = 0;

    uint32_t endLine   = 0;
    uint32_t endCol    = 0;
};

struct Tokens
{
    int64_t  fileLines           = 0;
    int64_t  fileLastLineColumns = 0;
    CXToken* tokens              = nullptr;
    uint32_t tokensCount         = 0;
};

struct Token
{
    Token() {}
    Token(uint32_t id, CXTokenKind kind, string spelling, CXSourceLocation location, CXSourceRange range) :
        tokenID(id), tokenKind(kind), tokenSpelling(spelling), tokenLocation(location), tokenRange(range)
    {

    }

    TokenPos   getTokenPos()      { return TokenPos(tokenLocation);  }
    TokenRange getTokenRange()    { return TokenRange(tokenRange);   }

    bool       isStartsEqual(const TokenRange& range)
    {
        const TokenRange tokenRange = getTokenRange();

        return (
                    tokenRange.startLine == range.startLine &&
                    tokenRange.startCol  == range.startCol
               );
    }

    bool       isEndsEqual(const TokenRange& range)
    {
        const TokenRange tokenRange = getTokenRange();

        return (
                    tokenRange.endLine == range.endLine &&
                    tokenRange.endCol  == range.endCol
               );
    }

    uint32_t         tokenID       = 0;
    CXTokenKind      tokenKind;
    string           tokenSpelling;
    CXSourceLocation tokenLocation;
    CXSourceRange    tokenRange;
};

/*         SourceCode         */

class SourceCode
{
    public:
        SourceCode(const string& filePath, const char* compilation_args[], uint16_t argsCount);
        ~SourceCode();

        static int64_t countFileLines(const string& filePath);
        static int64_t countFileLineColumns(const string& filePath, int64_t line);

    public:
        CXTranslationUnit&  getTranslationUnit() { return m_translationUnit; }

        AST&                getAST()          { return m_ast; }
        const list<Token>&  getTokens() const { return m_tokens; }
        list<Token>&        getTokens()       { return m_tokens; }


    private:
        const string&       m_filePath;

        CXIndex             m_index;
        CXErrorCode         m_compilationErrorCode;
        CXTranslationUnit   m_translationUnit;
        uint32_t            m_compilationErrorCount;

        AST                 m_ast;
        Tokens              m_rawTokens;
        list<Token>         m_tokens;
};