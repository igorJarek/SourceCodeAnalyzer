#include "ClangUtilityFunctions.h"

void dumpAST(string& strData, const CXCursor& cursor)
{
    CXCursorKind kind = clang_getCursorKind(cursor);
    CXString kindSpelling = clang_getCursorKindSpelling(kind);
    strData += _11_CXString2String(kindSpelling) + " ";

    CXSourceLocation cursorLocation = clang_getCursorLocation(cursor);
    CXSourceRange cursorRange = clang_getCursorExtent(cursor);
    CXSourceLocation locationStart = clang_getRangeStart(cursorRange);
    CXSourceLocation locationEnd = clang_getRangeEnd(cursorRange);

    CXFile cursorFile;
    uint32_t cursorLine, cursorColumn, cursorOffset;
    clang_getExpansionLocation(cursorLocation, &cursorFile, &cursorLine, &cursorColumn, &cursorOffset);

    CXFile startFile;
    uint32_t startLine, startColumn, startOffset;
    clang_getExpansionLocation(locationStart, &startFile, &startLine, &startColumn, &startOffset);

    CXFile endFile;
    uint32_t endLine, endColumn, endOffset;
    clang_getExpansionLocation(locationEnd, &endFile, &endLine, &endColumn /* endColumn -= 1; */, &endOffset);
    --endColumn;

    CXString fileName = clang_getFileName(startFile); // relative path
    CXString fileFullName = clang_File_tryGetRealPathName(startFile); // full path

    CXString cursorSpelling = clang_getCursorSpelling(cursor);
    CXType cursorType = clang_getCursorType(cursor);
    CXString cursorTypeSpelling = clang_getTypeSpelling(cursorType);

    strData += "<" + _11_CXString2String(fileName) + ":" + to_string(startLine) + ":" + to_string(startColumn) + ", col:" + to_string(endColumn) + ">" + " col:" + to_string(cursorColumn);
    strData += " used " + _11_CXString2String(cursorSpelling) + " '" + _11_CXString2String(cursorTypeSpelling) + "'\n";
}

void printCursor(string& strData, const CXCursor& cursor, uint32_t curLevel)
{
    strData += "Token str : \n";
    _1_printMangling(strData, cursor, curLevel);
    _3_printASTIntrospection(strData, cursor, curLevel);
    _7_printInformationForAttributes(strData, cursor, curLevel);
    _9_printCrossReferencingInTheAST(strData, cursor, curLevel);
    _15_printTypeInformationForCXCursors(strData, cursor, curLevel);

    strData += '\n';
}

void saveBaseCXCursorInfo(const CXCursor& cursor)
{
    
}