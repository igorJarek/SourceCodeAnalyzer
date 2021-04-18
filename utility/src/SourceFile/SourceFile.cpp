#include "SourceFile/SourceFile.h"

#include <fstream>

/*         HeaderFile         */

HeaderFile::HeaderFile(const string& filePath, const char* compilation_args[], uint16_t argsCount) :
    m_filePath(filePath)
{
    m_index = clang_createIndex(0, 0);

    m_compilationErrorCode = clang_parseTranslationUnit2(m_index, 
                                                         m_filePath.c_str(),
                                                         compilation_args, argsCount,
                                                         nullptr, 0,
                                                         CXTranslationUnit_None,
                                                         &m_translationUnit);

    m_compilationErrorCount = clang_getNumDiagnostics(m_translationUnit);

    if (m_compilationErrorCode == CXError_Success)
    {
        // tokenize whole file

        m_rawTokens.fileLines = countFileLines(filePath);
        if (m_rawTokens.fileLines != -1 /* && m_compilationErrorCount == 0 */)
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
}

HeaderFile::~HeaderFile()
{
    clang_disposeTokens(m_translationUnit, m_rawTokens.tokens, m_rawTokens.tokensCount);
    clang_disposeTranslationUnit(m_translationUnit);
    clang_disposeIndex(m_index);
}

int64_t HeaderFile::countFileLines(const string& filePath)
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

int64_t HeaderFile::countFileLineColumns(const string& filePath, int64_t line)
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

/*         SourceFile         */

SourceFile::SourceFile(const string& filePath, const char* compilation_args[], uint16_t argsCount) :
    HeaderFile(filePath, compilation_args, argsCount)
{
    if(m_compilationErrorCount)
    {
        std::fstream stream;
        stream.open(m_filePath + ".error", std::fstream::out | std::fstream::trunc);

        if(stream.is_open())
            stream << m_filePath << '(' << m_compilationErrorCount << ')' << std::endl;

        for (uint32_t errorIndex = 0; errorIndex < m_compilationErrorCount; ++errorIndex)
        {
            CXDiagnostic diagnostic = clang_getDiagnostic(m_translationUnit, errorIndex);

            CXDiagnosticSeverity diagnosticSeverity = clang_getDiagnosticSeverity(diagnostic);

            if( diagnosticSeverity < CXDiagnostic_Error)
            {
                clang_disposeDiagnostic(diagnostic);

                ++m_compilationIgnoreErrorCount;
                continue;
            }

            CXString formatDiagnostic = clang_formatDiagnostic(diagnostic, CXDiagnostic_DisplaySourceLocation | CXDiagnostic_DisplayColumn |
                                                                           CXDiagnostic_DisplaySourceRanges   | CXDiagnostic_DisplayOption |
                                                                           CXDiagnostic_DisplayCategoryId     | CXDiagnostic_DisplayCategoryName);

            // print this message to cerr ?
            string errorMessage =  to_string(diagnosticSeverity) + " : " + to_string(formatDiagnostic);

            if(stream.is_open())
                stream << '\t' << errorMessage << std::endl << std::endl;

            clang_disposeDiagnostic(diagnostic);
        }

        m_compilationErrorCount -= m_compilationIgnoreErrorCount;

        stream.close();
    }
}

SourceFile::~SourceFile()
{

}

void SourceFile::traversingAST(function<void (CXCursor cursor)> traversingFunc)
{
    if (m_compilationErrorCode == CXError_Success /* && m_compilationErrorCount == 0 */)
    {
        TraversingClientData traversingClientData(traversingFunc);

        CXCursor cursor = clang_getTranslationUnitCursor(m_translationUnit);
        clang_visitChildren(cursor, visitor, &traversingClientData);
    }
}

void SourceFile::findCursor(CXCursor cursor, enum CXCursorKind cursorKind, function<void (CXCursor cursor)> foundCursor)
{
    FindClientData findClientData(cursorKind, foundCursor);

    clang_visitChildren(cursor, findVisitor, &findClientData);
}

CXChildVisitResult SourceFile::visitor(CXCursor cursor, CXCursor /* parent */, CXClientData client_data)
{
    TraversingClientData* traversingClientDataPtr = reinterpret_cast<TraversingClientData*>(client_data);

    traversingClientDataPtr->m_traversingFunc(cursor);
    return CXChildVisit_Recurse;
}

CXChildVisitResult SourceFile::findVisitor(CXCursor cursor, CXCursor /* parent */, CXClientData client_data)
{
    FindClientData* findClientDataPtr = reinterpret_cast<FindClientData*>(client_data);

    if(cursor.kind == findClientDataPtr->m_cursorKind)
    {
        findClientDataPtr->m_foundCursor(cursor);
        return CXChildVisit_Break;
    }

    return CXChildVisit_Recurse;
}
