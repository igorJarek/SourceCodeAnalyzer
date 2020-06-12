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
    _10_printMappingBetweenCursorsAndSourceCode(strData, cursor, curLevel);
    _15_printTypeInformationForCXCursors(strData, cursor, curLevel);

    strData += '\n';
}

uint64_t saveBaseCXCursorInfo(const CXCursor& cursor)
{
    string out;

    out += "------------------------------------------------------------\n";

// Start

    // 1. Manglings

    out += tabOffset(1) + "Mangling : " + '\n';
	out += tabOffset(2) + "_1_getMangling : "                            + _11_CXString2String(_1_getMangling(cursor))                                  + '\n';

    // 3. C++ AST introspection

    out += tabOffset(1) + "AST introspection : " + '\n';
    out += tabOffset(2) + "_3_CXXConstructor_isConvertingConstructor : " + to_string(_3_CXXConstructor_isConvertingConstructor(cursor))                 + '\n';
    out += tabOffset(2) + "_3_CXXConstructor_isCopyConstructor : "       + to_string(_3_CXXConstructor_isCopyConstructor(cursor))                       + '\n';
    out += tabOffset(2) + "_3_CXXConstructor_isDefaultConstructor : "    + to_string(_3_CXXConstructor_isDefaultConstructor(cursor))                    + '\n';
    out += tabOffset(2) + "_3_CXXConstructor_isMoveConstructor : "       + to_string(_3_CXXConstructor_isMoveConstructor(cursor))                       + '\n';
    out += tabOffset(2) + "_3_CXXField_isMutable : "                     + to_string(_3_CXXField_isMutable(cursor))                                     + '\n';
    out += tabOffset(2) + "_3_CXXMethod_isDefaulted : "                  + to_string(_3_CXXMethod_isDefaulted(cursor))                                  + '\n';
    out += tabOffset(2) + "_3_CXXMethod_isPureVirtual : "                + to_string(_3_CXXMethod_isPureVirtual(cursor))                                + '\n';
    out += tabOffset(2) + "_3_CXXMethod_isStatic : "                     + to_string(_3_CXXMethod_isStatic(cursor))                                     + '\n';
    out += tabOffset(2) + "_3_CXXMethod_isVirtual : "                    + to_string(_3_CXXMethod_isVirtual(cursor))                                    + '\n';
    out += tabOffset(2) + "_3_CXXRecord_isAbstract : "                   + to_string(_3_CXXRecord_isAbstract(cursor))                                   + '\n';
    out += tabOffset(2) + "_3_EnumDecl_isScoped : "                      + to_string(_3_EnumDecl_isScoped(cursor))                                      + '\n';
    out += tabOffset(2) + "_3_CXXMethod_isConst : "                      + to_string(_3_CXXMethod_isConst(cursor))                                      + '\n';

    out += tabOffset(2) + "_3_getTemplateCursorKind : "                  + CXCursorKind2String(_3_getTemplateCursorKind(cursor))                        + '\n';

    // 7. Information for attributes

    out += tabOffset(1) + "Information for attributes : " + '\n';
    out += tabOffset(2) + "_7_getIBOutletCollectionType : "              +  _15_CXType2String(_7_getIBOutletCollectionType(cursor))                     + '\n';

    // 9. Cross-referencing in the AST

    CXString language, definedIn;
    uint32_t isGenerated;
    unsigned int _9_isExternalSymbolRet = _9_isExternalSymbol(cursor, &language, &definedIn, &isGenerated);

    out += tabOffset(1) + "Cross-referencing in the AST : " + '\n';

    out += tabOffset(2) + "_9_getCursorUSR : "                           +  _11_CXString2String(_9_getCursorUSR(cursor))                                + '\n';
    out += tabOffset(2) + "_9_getCursorSpelling : "                      +  _11_CXString2String(_9_getCursorSpelling(cursor))                           + '\n';
    out += tabOffset(2) + "_9_Cursor_getSpellingNameRange : \n"          +  CXSourceRange2String(_9_Cursor_getSpellingNameRange(cursor, 0, 0), 3);                  // check last 2 parameters (..., 0, 0)
    out += tabOffset(2) + "_9_getCursorDisplayName : "                   +  _11_CXString2String(_9_getCursorDisplayName(cursor))                        + '\n';
    out += tabOffset(2) + "_9_isCursorDefinition : "                     +  to_string(_9_isCursorDefinition(cursor))                                    + '\n';
    out += tabOffset(2) + "_9_isDynamicCall : "                          +  to_string(_9_isDynamicCall(cursor))                                         + '\n';
    //out += tabOffset(2) + "_9_getReceiverType : "                        +  _15_CXType2String(_9_getReceiverType(cursor))                             + '\n';
    out += tabOffset(2) + "_9_isVariadic : "                             +  to_string(_9_isVariadic(cursor))                                            + '\n';

    out += tabOffset(2) + "_9_isExternalSymbol [ret] : "                 + to_string(_9_isExternalSymbolRet)                                            + '\n';
    if(_9_isExternalSymbolRet)
    {
        out += tabOffset(2) + "_9_isExternalSymbol [language] : "        + _11_CXString2String(language)                                                + '\n';
        out += tabOffset(2) + "_9_isExternalSymbol [definedIn] : "       + _11_CXString2String(definedIn)                                               + '\n';
        out += tabOffset(2) + "_9_isExternalSymbol [isGenerated] : "     + to_string(isGenerated)                                                       + '\n';
    }

    out += tabOffset(2) + "_9_getCommentRange : \n"                      +  CXSourceRange2String(_9_getCommentRange(cursor), 3);
    out += tabOffset(2) + "_9_getRawCommentText : "                      + _11_CXString2String(_9_getRawCommentText(cursor))                            + '\n';
    out += tabOffset(2) + "_9_getBriefCommentText : "                    + _11_CXString2String(_9_getBriefCommentText(cursor))                          + '\n';

    // 10. Mapping between cursors and source code

    out += tabOffset(1) + "Mapping between cursors and source code : \n";

    out += tabOffset(2) + "_10_getCursorLocation : \n"                   + CXSourceLocation2String(_10_getCursorLocation(cursor), 3);
    out += tabOffset(2) + "_10_getCursorExtent : \n"                     + CXSourceRange2String(_10_getCursorExtent(cursor), 3);

    // 13. Module interspection

    // 15. Type information for CXCursors

// End

    out += "------------------------------------------------------------\n";

    const string cursorFilePath { "../lib//cursors.cur" };

    // clear cursors.cur file
    static bool firstFunctionRun { true };
    if(firstFunctionRun)
    {
        saveToFile(cursorFilePath, "");
        firstFunctionRun = false;
    }

    if(!appendToFile(cursorFilePath, out))
        cout << "Couldn't append to cursors.c file !" << endl;

    static int64_t functionRunCounter { -1 };
    ++functionRunCounter;

    return functionRunCounter * countStringLines(out);
}