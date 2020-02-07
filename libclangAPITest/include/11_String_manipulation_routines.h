#pragma once

#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/*
	1. const char*  clang_getCString        (CXString string)
    2. void         clang_disposeString     (CXString string)
    3. void         clang_disposeStringSet  (CXStringSet *set)      // ?????????
*/

string _11_CXString2String(const CXString& str);
ostream& operator<<(ostream& stream, const CXString& str);