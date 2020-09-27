#pragma once

#include <vector>
#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

/*
    Used:

    Unused:

        1. const char*  clang_getCString        (CXString string)
        2. void         clang_disposeString     (CXString string)
        3. void         clang_disposeStringSet  (CXStringSet *set)

*/

const char *    _11_getCString          (CXString string);          // 1.
void            _11_disposeString       (CXString string);          // 2.
void            _11_disposeStringSet    (CXStringSet *set);         // 3.
