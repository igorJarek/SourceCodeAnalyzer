#include "ClangUtilityFunctions.h"
#include <LibClangStruct2Str/LibClangStruct2Str.h>

CXChildVisitResult visitor(CXCursor cursor, CXCursor /* parent */, CXClientData client_data)
{
    ClientData* clientDataPtr = reinterpret_cast<ClientData*>(client_data);

    CXTranslationUnit translationUnit = clientDataPtr->translationUnit;
    OutputTree& astOutputTree = clientDataPtr->astOutputTree;
    OutputTree& astExtOutputTree = clientDataPtr->astExtOutputTree;
    uint32_t curLevel = clientDataPtr->treeLevel;

    dumpAST(astExtOutputTree.getNodesCount(), astOutputTree, cursor, curLevel);
    printCursor(translationUnit, astExtOutputTree, cursor, curLevel);

    ClientData nextClientData(clientDataPtr);
    nextClientData.treeLevel++;

    clang_visitChildren(cursor, visitor, &nextClientData);

    astOutputTree += nextClientData.astOutputTree;
    astExtOutputTree += nextClientData.astExtOutputTree;

    return CXChildVisit_Continue;
}

void dumpAST(uint64_t astExtNode, OutputTree& astOutputTree, const CXCursor& cursor, uint32_t curLevel)
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

    string output;

    output += to_string(kindSpelling) + " (" + to_string(astExtNode + 1) + ") " + " ";
    output += "<" + to_string(fileName) + ":" + to_string(startLine) + ":" + to_string(startColumn) + ", col:" + to_string(endColumn) + ">" + " col:" + to_string(cursorColumn);
    output += " used " + to_string(cursorSpelling) + " '" + to_string(cursorTypeSpelling);

    astOutputTree.addString(curLevel, output);
}

void printCursor(const CXTranslationUnit& translationUnit, OutputTree& astExtOutputTree, const CXCursor& cursor, uint32_t curLevel)
{
    CXCursorKind cursorKind      = _19_getCursorKind(cursor);
    CXString     kindSpelling    = _17_getCursorKindSpelling(cursorKind);

    astExtOutputTree.addString(curLevel, "Cursor : ", kindSpelling);

    _0_1_printCommentIntrospection              (astExtOutputTree, cursor, curLevel);
    _1_printMangling                            (astExtOutputTree, cursor, curLevel);
    _3_printASTIntrospection                    (translationUnit, astExtOutputTree, cursor, curLevel, true);
    _7_printInformationForAttributes            (astExtOutputTree, cursor, curLevel);
    _9_printCrossReferencingInTheAST            (translationUnit, astExtOutputTree, cursor, curLevel, true);
    _10_printMappingBetweenCursorsAndSourceCode (astExtOutputTree, cursor, curLevel);
    _15_printTypeInformationForCXCursors        (translationUnit, astExtOutputTree, cursor, curLevel, true);
    _18_printMiscellaneousUtilityFunctions      (astExtOutputTree, cursor, curLevel);
    _19_printCursorManipulations                (translationUnit, astExtOutputTree, cursor, curLevel, true);
}

uint64_t saveBaseCXCursorInfo(const CXTranslationUnit* translationUnit, const CXCursor* cursor, InfoAction action)
{
    static OutputTree   treeStaticCursorData;
    static stringstream sstreamStaticCursorInfoData;

    static int64_t      staticCurFileLinesCounter { 1 };

    if(action == InfoAction::ADD_INFO)
    {
        if(!translationUnit && !cursor)
            return 0;

        uint64_t startOutLinesCount = treeStaticCursorData.getNodesCount();

        treeStaticCursorData.addString(0, "-------------------- " + to_string(_17_getCursorKindSpelling(cursor->kind)) + " --------------------");

        if(_19_isInvalid(cursor->kind))
            treeStaticCursorData.addString(0, "Cursor == Invalid");
        else
        {
            _0_1_printCommentIntrospection              (treeStaticCursorData, *cursor, 0);
            _1_printMangling                            (treeStaticCursorData, *cursor, 0);
            _3_printASTIntrospection                    (*translationUnit, treeStaticCursorData, *cursor, 0, false);
            _7_printInformationForAttributes            (treeStaticCursorData, *cursor, 0);
            _9_printCrossReferencingInTheAST            (*translationUnit, treeStaticCursorData, *cursor, 0, false);
            _10_printMappingBetweenCursorsAndSourceCode (treeStaticCursorData, *cursor, 0);
            _15_printTypeInformationForCXCursors        (*translationUnit, treeStaticCursorData, *cursor, 0, false);
            _18_printMiscellaneousUtilityFunctions      (treeStaticCursorData, *cursor, 0);
            _19_printCursorManipulations                (*translationUnit, treeStaticCursorData, *cursor, 0, false);
        }

        treeStaticCursorData.addString(0, "------------------------------------------------------------");

        uint64_t outLinesCount = treeStaticCursorData.getNodesCount() - startOutLinesCount;
        staticCurFileLinesCounter += outLinesCount;

        return staticCurFileLinesCounter - outLinesCount;
    }
    else if(action == InfoAction::ADD_INFO_LINESTAMP)
    {
        if(!translationUnit)
            return 0;

        CXString sourceCodeFileName = _6_getTranslationUnitSpelling(*translationUnit);

        sstreamStaticCursorInfoData.width(64);
        sstreamStaticCursorInfoData << std::left << to_string(sourceCodeFileName);

        sstreamStaticCursorInfoData.width(0);
        sstreamStaticCursorInfoData << " : " << to_string(staticCurFileLinesCounter) << endl;

        return 0;
    }
    else if(action == InfoAction::SAVE_FILE)
    {
        if (!treeStaticCursorData.saveToFile(CURSORS_REF_PATH))
            cout << "Couldn't save file : " << CURSORS_REF_PATH << endl;

        return 0;
    }
    else if(action == InfoAction::SAVE_LINESTAMPS_FILE)
    {   
        if (!saveToFile(CURSORS_INFO_REF_PATH, sstreamStaticCursorInfoData))
            cout << "Couldn't save file : " << CURSORS_INFO_REF_PATH << endl;

        return 0;
    }

    return 0;
}

uint64_t saveBaseCXTypeInfo(const CXTranslationUnit* translationUnit, const CXType* type, InfoAction action)
{
    static OutputTree   treeStaticTypeData;
    static stringstream sstreamStaticTypeInfoData;

    static int64_t      staticTypeFileLinesCounter { 1 };

    if(action == InfoAction::ADD_INFO)
    {
        if(!type)
            return 0;

        const CXType& typeRef = *type;
        uint64_t startOutLinesCount = treeStaticTypeData.getNodesCount();

        treeStaticTypeData.addString(0, "-------------------- " + to_string(_15_getTypeKindSpelling(typeRef.kind)) + " --------------------");

        if(type->kind == CXType_Invalid)
            treeStaticTypeData.addString(1, "TypeKind == CXType_Invalid");
        else
            _15_printTypeInformationForCXType(treeStaticTypeData, *type, 1);

        treeStaticTypeData.addString(0, "------------------------------------------------------------");

        uint64_t outLinesCount = treeStaticTypeData.getNodesCount() - startOutLinesCount;
        staticTypeFileLinesCounter += outLinesCount;

        return staticTypeFileLinesCounter - outLinesCount;
    }
    else if(action == InfoAction::ADD_INFO_LINESTAMP)
    {
        if(!translationUnit)
            return 0;

        CXString sourceCodeFileName = _6_getTranslationUnitSpelling(*translationUnit);

        sstreamStaticTypeInfoData.width(64);
        sstreamStaticTypeInfoData << std::left << to_string(sourceCodeFileName);

        sstreamStaticTypeInfoData.width(0);
        sstreamStaticTypeInfoData << " : " << to_string(staticTypeFileLinesCounter) << endl;

        return 0;
    }
    else if(action == InfoAction::SAVE_FILE)
    {
        if (!treeStaticTypeData.saveToFile(TYPES_REF_PATH))
            cout << "Couldn't save file : " << TYPES_REF_PATH << endl;

        return 0;
    }
    else if(action == InfoAction::SAVE_LINESTAMPS_FILE)
    {   
        if (!saveToFile(TYPES_INFO_REF_PATH, sstreamStaticTypeInfoData))
            cout << "Couldn't save file : " << TYPES_INFO_REF_PATH << endl;

        return 0;
    }

    return 0;
}
