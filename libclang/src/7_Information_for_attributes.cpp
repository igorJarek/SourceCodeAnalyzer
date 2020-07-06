#include "7_Information_for_attributes.h"

void _7_printInformationForAttributes(string& strData, const CXCursor& cursor, uint32_t curLevel)
{
    CXType outletCollectionType = clang_getIBOutletCollectionType(cursor);                                                          // 1.

    ADD_STRING_OUT_NAME(curLevel + 1, "7. Information_for attributes : ")
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getIBOutletCollectionType : ", CXType2String(outletCollectionType))
}

CXType _7_getIBOutletCollectionType (CXCursor C)
                                    { return clang_getIBOutletCollectionType(C); }