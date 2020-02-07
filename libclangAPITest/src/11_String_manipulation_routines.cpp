#include "11_String_manipulation_routines.h"

string _11_CXString2String(const CXString& str)
{
    string s{ clang_getCString(str) };  // 1
    clang_disposeString(str);           // 2
    return s;
}

ostream& operator<<(ostream& stream, const CXString& str)
{
    stream << clang_getCString(str);    // 1
    clang_disposeString(str);           // 2
    return stream;
}