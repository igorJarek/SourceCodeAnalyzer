#include "ClangUtilityFunctions.h"

CXChildVisitResult visitor(CXCursor cursor, CXCursor /* parent */, CXClientData client_data)
{
    ClientData* clientDataPtr = reinterpret_cast<ClientData*>(client_data);
    CXTranslationUnit translationUnit = clientDataPtr->translationUnit;
    string& astStringData = clientDataPtr->astStringData;
    string& astExtStringData = clientDataPtr->astExtStringData;
    uint32_t curLevel = clientDataPtr->treeLevel;

    astStringData    += tabOffset(curLevel);
    astExtStringData += tabOffset(curLevel);

    dumpAST(astStringData, cursor);
    printCursor(translationUnit, astExtStringData, cursor, curLevel);

    ClientData nextClientData(translationUnit, curLevel + 1);
    clang_visitChildren(cursor, visitor, &nextClientData);

    astStringData    += nextClientData.astStringData;
    astExtStringData += nextClientData.astExtStringData;

    return CXChildVisit_Continue;
}

void dumpAST(string& strData, const CXCursor& cursor)
{
    CXFile cursorFile,   startFile,    endFile;
    uint32_t cursorLine, cursorColumn, cursorOffset;
    uint32_t startLine,  startColumn,  startOffset;
    uint32_t endLine,    endColumn,    endOffset;

    CXCursorKind        cursorKind          = _19_getCursorKind(cursor);
    CXString            kindSpelling        = _17_getCursorKindSpelling(cursorKind);

    CXSourceLocation    cursorLocation      = _10_getCursorLocation(cursor);
    CXSourceRange       cursorRange         = _10_getCursorExtent(cursor);
    CXSourceLocation    locationStart       = _21_getRangeStart(cursorRange);
    CXSourceLocation    locationEnd         = _21_getRangeEnd(cursorRange);

    _21_getExpansionLocation(cursorLocation, &cursorFile, &cursorLine, &cursorColumn, &cursorOffset);
    _21_getExpansionLocation(locationStart,  &startFile,  &startLine,  &startColumn,  &startOffset);
    _21_getExpansionLocation(locationEnd, &endFile, &endLine, &endColumn /* endColumn -= 1; */, &endOffset);

    --endColumn;

    CXString            fileName            = _8_getFileName(startFile);                 // relative path
    CXString            fileFullName        = _8_File_tryGetRealPathName(startFile);     // full path

    CXString            cursorSpelling      = _9_getCursorSpelling(cursor);
    CXType              cursorType          = _15_getCursorType(cursor);
    CXString            cursorTypeSpelling  = _15_getTypeSpelling(cursorType);

    strData += CXString2String(kindSpelling) + " ";
    strData += "<" + CXString2String(fileName) + ":" + to_string(startLine) + ":" + to_string(startColumn) + ", col:" + to_string(endColumn) + ">" + " col:" + to_string(cursorColumn);
    strData += " used " + CXString2String(cursorSpelling) + " '" + CXString2String(cursorTypeSpelling) + "'\n";
}

void printCursor(const CXTranslationUnit& translationUnit, string& strData, const CXCursor& cursor, uint32_t curLevel)
{
    CXCursorKind cursorKind   = _19_getCursorKind(cursor);
    CXString     kindSpelling = _17_getCursorKindSpelling(cursorKind);

    ADD_STRING_OUT_CURSOR_KIND(CXString2String(kindSpelling))

    _0_1_printCommentIntrospection              (strData, cursor, curLevel);
    _1_printMangling                            (strData, cursor, curLevel);
    _3_printASTIntrospection                    (translationUnit, strData, cursor, curLevel);
    _7_printInformationForAttributes            (strData, cursor, curLevel);
    _9_printCrossReferencingInTheAST            (translationUnit, strData, cursor, curLevel);
    _10_printMappingBetweenCursorsAndSourceCode (strData, cursor, curLevel);
    _15_printTypeInformationForCXCursors        (translationUnit, strData, cursor, curLevel);
    _18_printMiscellaneousUtilityFunctions      (strData, cursor, curLevel);
    _19_printCursorManipulations                (translationUnit, strData, cursor, curLevel);

    ADD_STRING_OUT_NEWLINE()
}

uint64_t getBaseCXCursorInfo(const CXTranslationUnit* translationUnit, const CXCursor* cursor, bool saveFile /* = false */)
{
    static string  strStaticData;
    static int64_t staticLinesCounter { 1 };

    if(!saveFile)
    {
        if(!translationUnit && !cursor)
            return 0;

        string strData;

        ADD_STRING_OUT_TEXT(0, "------------------------------------------------------------")

        if(cursor->kind == CXCursor_NoDeclFound)
            ADD_STRING_OUT_TEXT(0, "Cursor == CXCursor_NoDeclFound")
        else
        {
            _0_1_printCommentIntrospection              (strData, *cursor, 0);
            _1_printMangling                            (strData, *cursor, 0);
            _3_printASTIntrospection                    (*translationUnit, strData, *cursor, 0, false);
            _7_printInformationForAttributes            (strData, *cursor, 0);
            _9_printCrossReferencingInTheAST            (*translationUnit, strData, *cursor, 0, false);
            _10_printMappingBetweenCursorsAndSourceCode (strData, *cursor, 0);
            _15_printTypeInformationForCXCursors        (*translationUnit, strData, *cursor, 0, false);
            _18_printMiscellaneousUtilityFunctions      (strData, *cursor, 0);
            _19_printCursorManipulations                (*translationUnit, strData, *cursor, 0, false);
        }

        ADD_STRING_OUT_TEXT(0, "------------------------------------------------------------")

        strStaticData += strData;

        int64_t outLinesCount = countStringLines(strData);
        staticLinesCounter += outLinesCount;

        return staticLinesCounter - outLinesCount;
    }
    else
    {   
        if (!saveToFile(CURSORS_REF_PATH, strStaticData))
            cout << "Couldn't save file : " << CURSORS_REF_PATH << endl;

        return 0;
    }
}

string getBaseCXFileInfo(const CXTranslationUnit& translationUnit, const CXFile& file, uint32_t curLevel)
{
    string strData;

    char            timeBuff[255] = { 0 };
    CXFileUniqueID  fileUniqueIDStruct;
    size_t          size;

    time_t          fileTime                = _8_getFileTime(file);
    int32_t         fileUniqueID            = _8_getFileUniqueID(file, &fileUniqueIDStruct);
    uint32_t        multipleIncludeGuarded  = _8_isFileMultipleIncludeGuarded(translationUnit, file);
    const char*     fileContents            = _8_getFileContents(translationUnit, file, &size);

    ctime_s(timeBuff, sizeof(timeBuff), &fileTime);

    ADD_STRING_OUT_NL(curLevel, "_8_getFileName : ",                    CXString2String(_8_getFileName(file)))
    ADD_STRING_OUT_NL(curLevel, "_8_getFileTime : ",                    timeBuff)
    ADD_STRING_OUT_NL(curLevel, "_8_getFileUniqueID [return value] : ", to_string(fileUniqueID))
    ADD_STRING_OUT_NL(curLevel, "_8_getFileUniqueID [outID] : ",        to_string(fileUniqueIDStruct.data[0]) + ", " +
                                                                        to_string(fileUniqueIDStruct.data[1]) + ", " +
                                                                        to_string(fileUniqueIDStruct.data[2]))
    ADD_STRING_OUT_NL(curLevel, "_8_isFileMultipleIncludeGuarded : ",   to_string(multipleIncludeGuarded))
    ADD_STRING_OUT_NL(curLevel, "_8_getFileContents [size] : ",         to_string(size))
    ADD_STRING_OUT_NL(curLevel, "_8_getFileContents [return] : ",       fileContents)
    ADD_STRING_OUT_NL(curLevel, "_8_File_tryGetRealPathName : ",        CXString2String(_8_File_tryGetRealPathName(file)))

    return strData;
}
