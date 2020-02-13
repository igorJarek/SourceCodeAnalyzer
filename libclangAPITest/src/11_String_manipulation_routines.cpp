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

vector<string> _11_CXStringSet2StringVec(CXStringSet* stringSet)
{
    if (stringSet != nullptr)
    {  
        uint32_t CXStringSetCount{ stringSet->Count };
        vector<string> output(CXStringSetCount);

        for (uint32_t index{ 0 }; index < CXStringSetCount; ++index)
        {
            CXString string = stringSet->Strings[index];
            output.at(index) = move(_11_CXString2String(string));
        }

        return output;
    }

    return {};
}

void _11_releaseCXStringSet(CXStringSet* stringSet)
{
    clang_disposeStringSet(stringSet); // 3
}