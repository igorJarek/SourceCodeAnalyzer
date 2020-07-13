#include "10_Mapping_between_cursors_and_source_code.h"

void _10_printMappingBetweenCursorsAndSourceCode(string& strData, const CXCursor& cursor, uint32_t curLevel)
{
    CXSourceLocation cursorLocation = clang_getCursorLocation(cursor);      // 2.
    CXSourceRange    cursorExtent   = clang_getCursorExtent(cursor);        // 3.

    ADD_STRING_OUT_TEXT(curLevel + 1, "10. Mapping between cursors and source code : ")

    ADD_STRING_OUT(curLevel + 2, "clang_getCursorLocation : \n", CXSourceLocation2String(cursorLocation, curLevel + 3))
    ADD_STRING_OUT(curLevel + 2, "clang_getCursorExtent : \n",   CXSourceRange2String(cursorExtent, curLevel + 3))
}

CXCursor            _10_getCursor               (CXTranslationUnit TU, CXSourceLocation SourceLocation)
                                                { return clang_getCursor(TU, SourceLocation); }

CXSourceLocation    _10_getCursorLocation       (CXCursor C)
                                                { return clang_getCursorLocation(C); }

CXSourceRange       _10_getCursorExtent         (CXCursor C)
                                                { return clang_getCursorExtent(C); }
