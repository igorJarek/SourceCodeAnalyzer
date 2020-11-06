#include "1_Name_Mangling_API_Functions.h"

void _1_printMangling(OutputTree& astExtOutputTree, const CXCursor& cursor, const uint32_t curLevel)
{
    CXString     mangling     = clang_Cursor_getMangling(cursor);                                             // 1.
    CXStringSet* CXXManglings = clang_Cursor_getCXXManglings(cursor);                                         // 2.

    astExtOutputTree.addString(curLevel + 1, "1. Mangling : ");
    astExtOutputTree.addString(curLevel + 2, "clang_Cursor_getMangling : ", mangling);

    astExtOutputTree.addCXStringSet(curLevel + 2, "clang_Cursor_getCXXManglings : ", CXXManglings);
}

CXString        _1_getMangling          (CXCursor C) 
                                        { return clang_Cursor_getMangling(C); }

CXStringSet*    _1_getCXXManglings      (CXCursor C)
                                        { return clang_Cursor_getCXXManglings(C); }

CXStringSet*    _1_getObjCManglings     (CXCursor C)
                                        { return clang_Cursor_getObjCManglings(C); }