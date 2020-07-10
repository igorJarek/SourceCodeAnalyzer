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
        _1_printMangling(out, cursor, 0);

        _3_printASTIntrospection(translationUnit, out, cursor, 0, false);

        _7_printInformationForAttributes(out, cursor, 0);

        _9_printCrossReferencingInTheAST(translationUnit, out, cursor, 0, false);

        _10_printMappingBetweenCursorsAndSourceCode(out, cursor, 0);

        _15_printTypeInformationForCXCursors(translationUnit, out, cursor, 0, false);

        _18_printMiscellaneousUtilityFunctions(out, cursor, 0);

        // 19. Cursor manipulations

        int32_t  alwaysDeprecated, alwaysUnavailable;
        CXString deprecatedMessage, unavailableMessage;
        CXPlatformAvailability platformAvailability;
    
        int32_t cursorPlatformAvailabilityReturn = _19_getCursorPlatformAvailability(cursor, &alwaysDeprecated, &deprecatedMessage, 
                                                                                     &alwaysUnavailable, &unavailableMessage, &platformAvailability, 0);    // check last parameter
        CXCursorKind cursorKind = _19_getCursorKind(cursor);

        CXCursor* overriddens = nullptr;
        uint32_t  num_overridden;
        _19_getOverriddenCursors(cursor, &overriddens, &num_overridden);

        CXFile includedFile = _19_getIncludedFile(cursor);

        out += tabOffset(1) + "Cursor manipulations : \n";

        out += tabOffset(2) + "_19_hashCursor : "                            + to_string(_19_hashCursor(cursor))                                            + '\n';
        out += tabOffset(2) + "_19_getCursorKind : "                         + CXCursorKind2String(cursorKind)                                              + '\n';
        out += tabOffset(2) + "_19_isDeclaration : "                         + to_string(_19_isDeclaration(cursorKind))                                     + '\n';
        out += tabOffset(2) + "_19_isInvalidDeclaration : "                  + to_string(_19_isInvalidDeclaration(cursor))                                  + '\n';
        out += tabOffset(2) + "_19_isReference : "                           + to_string(_19_isReference(cursorKind))                                       + '\n';
        out += tabOffset(2) + "_19_isExpression : "                          + to_string(_19_isExpression(cursorKind))                                      + '\n';
        out += tabOffset(2) + "_19_isStatement : "                           + to_string(_19_isStatement(cursorKind))                                       + '\n';
        out += tabOffset(2) + "_19_isAttribute : "                           + to_string(_19_isAttribute(cursorKind))                                       + '\n';
        out += tabOffset(2) + "_19_hasAttrs : "                              + to_string(_19_hasAttrs(cursor))                                              + '\n';
        out += tabOffset(2) + "_19_isInvalid : "                             + to_string(_19_isInvalid(cursorKind))                                         + '\n';
        out += tabOffset(2) + "_19_isTranslationUnit : "                     + to_string(_19_isTranslationUnit(cursorKind))                                 + '\n';
        out += tabOffset(2) + "_19_isPreprocessing : "                       + to_string(_19_isPreprocessing(cursorKind))                                   + '\n';
        out += tabOffset(2) + "_19_isUnexposed : "                           + to_string(_19_isUnexposed(cursorKind))                                       + '\n';
        out += tabOffset(2) + "_19_getCursorLinkage : "                      + CXLinkageKind2String(_19_getCursorLinkage(cursor))                           + '\n';
        out += tabOffset(2) + "_19_getCursorVisibility : "                   + CXVisibilityKind2String(_19_getCursorVisibility(cursor))                     + '\n';
        out += tabOffset(2) + "_19_getCursorAvailability : "                 + CXAvailabilityKind2String(_19_getCursorAvailability(cursor))                 + '\n';

        out += tabOffset(2) + "_19_getCursorPlatformAvailability [return] : " + to_string(cursorPlatformAvailabilityReturn)                                 + '\n';
        if(cursorPlatformAvailabilityReturn > 0)
        {
            out += tabOffset(2) + "_19_getCursorPlatformAvailability [always_deprecated] : "   + to_string(alwaysDeprecated)                                + '\n';
            out += tabOffset(2) + "_19_getCursorPlatformAvailability [deprecated_message] : "  + CXString2String(deprecatedMessage)                         + '\n';
            out += tabOffset(2) + "_19_getCursorPlatformAvailability [always_unavailable] : "  + to_string(alwaysUnavailable)                               + '\n';
            out += tabOffset(2) + "_19_getCursorPlatformAvailability [unavailable_message] : " + CXString2String(unavailableMessage)                        + '\n';
            out += tabOffset(2) + "_19_getCursorPlatformAvailability [availability] : \n"      + CXPlatformAvailability2String(platformAvailability, 3)     + '\n';

            _19_disposeCXPlatformAvailability(&platformAvailability);
        }

        out += tabOffset(2)     + "_19_getCursorLanguage : "                 + CXLanguageKind2String(_19_getCursorLanguage(cursor))                         + '\n';
        out += tabOffset(2)     + "_19_getCursorTLSKind : "                  + CXTLSKind2String(_19_getCursorTLSKind(cursor))                               + '\n';

        out += tabOffset(2)     + "_19_getOverriddenCursors [num_overridden] : " + to_string(num_overridden)                                                + '\n';
        if(num_overridden > 0)
        {
            for(uint32_t index { 0 }; index < num_overridden; ++index)
            {
                const CXCursor& overridden = overriddens[index];
                if(!clang_Cursor_isNull(overridden))
                    out += tabOffset(2) + "_19_getOverriddenCursors [" + to_string(index + 1) + "] : " + CXCursorKind2String(_19_getCursorKind(overridden)) + '\n';
            }

            _19_disposeOverriddenCursors(overriddens);
        }

        if(includedFile)
            out += tabOffset(2) + "_19_getIncludedFile : \n"                                   + getBaseCXFileInfo(translationUnit, includedFile, 3)        + '\n';
        else
            out += tabOffset(2) + "_19_getIncludedFile : -NULL-\n";
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