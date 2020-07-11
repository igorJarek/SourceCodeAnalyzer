#include "ClangUtilityFunctions.h"

void dumpAST(string& strData, const CXCursor& cursor)
{
    CXCursorKind kind = clang_getCursorKind(cursor);
    CXString kindSpelling = clang_getCursorKindSpelling(kind);
    strData += CXString2String(kindSpelling) + " ";

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

    strData += "<" + CXString2String(fileName) + ":" + to_string(startLine) + ":" + to_string(startColumn) + ", col:" + to_string(endColumn) + ">" + " col:" + to_string(cursorColumn);
    strData += " used " + CXString2String(cursorSpelling) + " '" + CXString2String(cursorTypeSpelling) + "'\n";
}

void printCursor(const CXTranslationUnit& translationUnit, string& strData, const CXCursor& cursor, uint32_t curLevel)
{
    strData += "Token str : \n";
    _1_printMangling(strData, cursor, curLevel);
    _3_printASTIntrospection(translationUnit, strData, cursor, curLevel);
    _7_printInformationForAttributes(strData, cursor, curLevel);
    _9_printCrossReferencingInTheAST(translationUnit, strData, cursor, curLevel);
    _10_printMappingBetweenCursorsAndSourceCode(strData, cursor, curLevel);
    _15_printTypeInformationForCXCursors(translationUnit, strData, cursor, curLevel);
    _18_printMiscellaneousUtilityFunctions(strData, cursor, curLevel);
    _19_printCursorManipulations(translationUnit, strData, cursor, curLevel);

    strData += '\n';
}

uint64_t saveBaseCXCursorInfo(const CXTranslationUnit& translationUnit, const CXCursor& cursor)
{
    string out;

    out += "------------------------------------------------------------\n";

    if(cursor.kind == CXCursor_NoDeclFound)
        out += tabOffset(1) + "cursor.kind = CXCursor_NoDeclFound\n";
    else
    {
        _1_printMangling                            (out, cursor, 0);
        _3_printASTIntrospection                    (translationUnit, out, cursor, 0, false);
        _7_printInformationForAttributes            (out, cursor, 0);
        _9_printCrossReferencingInTheAST            (translationUnit, out, cursor, 0, false);
        _10_printMappingBetweenCursorsAndSourceCode (out, cursor, 0);
        _15_printTypeInformationForCXCursors        (translationUnit, out, cursor, 0, false);
        _18_printMiscellaneousUtilityFunctions      (out, cursor, 0);
        _19_printCursorManipulations                (translationUnit, out, cursor, 0, false);
    }

    out += "------------------------------------------------------------\n";

    const string cursorFilePath { "../lib//cursors.cur" };

    // clear cursors.cur file
    static bool firstFunctionRun { true };
    if(firstFunctionRun)
    {
        saveToFile(cursorFilePath, "");
        firstFunctionRun = false;
    }

    // append data out
    if(!appendToFile(cursorFilePath, out))
        cout << "Couldn't append to cursors.c file !" << endl;

    static int64_t functionLinesCounter { 1 };
    int64_t outLineCount = countStringLines(out);
    functionLinesCounter += outLineCount;

    return functionLinesCounter - outLineCount;
}

string getBaseCXFileInfo(const CXTranslationUnit& translationUnit, const CXFile& file, uint32_t curLevel)
{
    string out;

    time_t fileTime = _8_getFileTime(file);
    char timeBuff[255] = { 0 };
    ctime_s(timeBuff, sizeof(timeBuff), &fileTime);

    CXFileUniqueID fileUniqueIDStruct;
    int32_t fileUniqueID = _8_getFileUniqueID(file, &fileUniqueIDStruct);

    uint32_t multipleIncludeGuarded = _8_isFileMultipleIncludeGuarded(translationUnit, file);

    size_t size;
    const char* fileContents = _8_getFileContents(translationUnit, file, &size);

    out += tabOffset(curLevel) + "_8_getFileName : "                    + CXString2String(_8_getFileName(file))                 + '\n';
    out += tabOffset(curLevel) + "_8_getFileTime : "                    + timeBuff                                              + '\n';
    out += tabOffset(curLevel) + "_8_getFileUniqueID [return value] : " + to_string(fileUniqueID)                               + '\n';
    out += tabOffset(curLevel) + "_8_getFileUniqueID [outID] : "        + to_string(fileUniqueIDStruct.data[0]) + ", " +
                                                                          to_string(fileUniqueIDStruct.data[1]) + ", " +
                                                                          to_string(fileUniqueIDStruct.data[2]) + ", "          + '\n';
    out += tabOffset(curLevel) + "_8_isFileMultipleIncludeGuarded : "   + to_string(multipleIncludeGuarded)                     + '\n';
    out += tabOffset(curLevel) + "_8_getFileContents [size] : "         + to_string(size)                                       + '\n';
    out += tabOffset(curLevel) + "_8_getFileContents [return] : "       + fileContents                                          + '\n';
    out += tabOffset(curLevel) + "_8_File_tryGetRealPathName : "        + CXString2String(_8_File_tryGetRealPathName(file))     + '\n';

    return out;
}