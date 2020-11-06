#pragma once

#include <clang-c/Index.h>
#include "11_String_manipulation_routines.h"
#include "UtilityFunctions.h"
#include <fstream>
#include <string>
#include <iostream>

/*
    Used:

        1. CXString             clang_Cursor_getMangling        (CXCursor)
        2. CXStringSet*         clang_Cursor_getCXXManglings    (CXCursor)

    Unused:

        3. CXStringSet*         clang_Cursor_getObjCManglings   (CXCursor)      // ObjC 
*/

// Print Function

void _1_printMangling(OutputTree& astExtOutputTree, const CXCursor& cursor, const uint32_t curLevel);

// Clang Functions

CXString        _1_getMangling          (CXCursor C);       // 1.
CXStringSet*    _1_getCXXManglings      (CXCursor C);       // 2.
CXStringSet*    _1_getObjCManglings     (CXCursor C);       // 3.
