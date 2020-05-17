#pragma once

#include <vector>
#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/*
    Used:

            1. const char*  clang_getCString        (CXString string)
            2. void         clang_disposeString     (CXString string)
            3. void         clang_disposeStringSet  (CXStringSet *set)

    Unused:

*/

string _11_CXString2String(const CXString& str);
void _11_releaseCXStringSet(CXStringSet* stringSet);
vector<string> _11_CXStringSet2StringVec(CXStringSet* stringSet);
ostream& operator<<(ostream& stream, const CXString& str);

const char *    _11_getCString          (CXString string);
void            _11_disposeString       (CXString string);
void            _11_disposeStringSet    (CXStringSet *set);
