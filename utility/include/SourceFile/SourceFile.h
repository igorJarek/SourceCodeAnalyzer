#pragma once

#include "LibClangStruct2Str/LibClangStruct2Str.h"

#include "clang-c/Index.h"

#include <list>
#include <string>
#include <memory>
#include <functional>
#include <filesystem>

using std::list;
using std::string;
using std::to_string;
using std::shared_ptr;
using std::function;
namespace fs = std::filesystem;

enum class SourceFileType
{
    HEADER_FILE,
    SOURCE_FILE,

    UNKNOWN
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

        fileName = fs::path(to_string(clang_getFileName(file))).make_preferred();
    }

    bool operator==(const TokenPos& right) const
    {
        return linePos == right.linePos && colPos == right.colPos;
    }

    fs::path fileName;

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

        fileName = fs::path(to_string(clang_getFileName(file))).make_preferred();
    }

    fs::path fileName;

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

    TokenPos   getTokenPos()   const { return TokenPos(tokenLocation); }
    TokenRange getTokenRange() const { return TokenRange(tokenRange);  }

    bool       isStartsEqual(const TokenRange& range) const
    {
        const TokenRange tmpTokenRange = getTokenRange();

        return (
                    tmpTokenRange.startLine == range.startLine &&
                    tmpTokenRange.startCol  == range.startCol
               );
    }

    bool       isEndsEqual(const TokenRange& range) const
    {
        const TokenRange tmpTokenRange = getTokenRange();

        return (
                    tmpTokenRange.endLine == range.endLine &&
                    tmpTokenRange.endCol  == range.endCol
               );
    }

    uint32_t         tokenID       = 0;
    CXTokenKind      tokenKind     = CXToken_Comment;
    string           tokenSpelling;
    CXSourceLocation tokenLocation = clang_getNullLocation();
    CXSourceRange    tokenRange    = clang_getNullRange();
};

/*         TraversingClientData         */

struct TraversingClientData
{
    TraversingClientData(function<CXChildVisitResult (CXCursor cursor)> traversingFunc) :
        m_traversingFunc(traversingFunc)
    { }

    function<CXChildVisitResult (CXCursor cursor)> m_traversingFunc;
};

/*         FindClientData         */

struct FindCursorClientData
{
    FindCursorClientData(enum CXCursorKind cursorKind, function<void (CXCursor cursor)> foundCursor) :
        m_cursorKind(cursorKind),
        m_foundCursor(foundCursor)
    { }

    enum CXCursorKind                m_cursorKind;
    function<void (CXCursor cursor)> m_foundCursor;
};

/*         HeaderFile         */

class HeaderFile
{
public:
    HeaderFile(const string& filePath, const char* compilation_args[] = nullptr, uint16_t argsCount = 0);
    ~HeaderFile();

    static int64_t      countFileLines(const string& filePath);
    static int64_t      countFileLineColumns(const string& filePath, int64_t line);
    static SourceFileType getSourceFileType(const string& filePath);

public:
    CXTranslationUnit&  getTranslationUnit() { return m_translationUnit; }

    const list<Token>&  getTokens() const { return m_tokens; }
    list<Token>&        getTokens()       { return m_tokens; }

protected:
    const string&       m_filePath;

    CXTranslationUnit   m_translationUnit;
    CXIndex             m_index                       = nullptr;
    CXErrorCode         m_compilationErrorCode        = CXError_Success;
    uint32_t            m_compilationErrorCount       = 0;
    uint32_t            m_compilationIgnoreErrorCount = 0;

    Tokens              m_rawTokens;
    list<Token>         m_tokens;
};

/*         SourceFile         */

class SourceFile : public HeaderFile
{
public:
    SourceFile(const string& filePath, const char* compilation_args[], uint16_t argsCount);
    ~SourceFile();

public:
    void traversingAST(function<CXChildVisitResult (CXCursor cursor)> traversingFunc);
    void traversingCursor(CXCursor cursor, function<CXChildVisitResult (CXCursor cursor)> traversingFunc);
    void findCursor(CXCursor cursor, enum CXCursorKind cursorKind, function<void (CXCursor cursor)> foundCursor);

protected:
    static CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData client_data);
    static CXChildVisitResult findVisitor(CXCursor cursor, CXCursor parent, CXClientData client_data);
};
