#pragma once

#include <clang-c/Index.h>

#include <list>
#include <string>
#include <memory>
#include <functional>

using std::list;
using std::string;
using std::shared_ptr;
using std::function;

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

class ClientData
{
public:
    ClientData(AST* ast) : 
        m_ast(ast) 
    { }

    AST* m_ast;
};

struct Tokens
{
    int64_t  fileLines           = 0;
    int64_t  fileLastLineColumns = 0;
    CXToken* tokens              = nullptr;
    uint32_t tokensCount         = 0;
};

class SourceCode
{
    public:
        SourceCode(const string& filePath, const char* compilation_args[], uint16_t argsCount);
        ~SourceCode();

        static int64_t countFileLines(const string& filePath);
        static int64_t countFileLineColumns(const string& filePath, int64_t line);

    public:
        CXTranslationUnit&  getTranslationUnit() { return m_translationUnit; }

        AST&                getAST()             { return m_ast; }
        Tokens&             getTokens()          { return m_tokens; }

    private:
        const string&       m_filePath;

        CXIndex             m_index;
        CXErrorCode         m_compilationErrorCode;
        CXTranslationUnit   m_translationUnit;
        uint32_t            m_compilationErrorCount;

        AST                 m_ast;
        Tokens              m_tokens;
};