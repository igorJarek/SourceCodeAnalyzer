#include "7_Information_for_attributes.h"

void _7_printInformationForAttributes(string& strData, const CXCursor& cursor, uint32_t curLevel)
{
    CXType outletCollectionType = clang_getIBOutletCollectionType(cursor);	// 1.

    strData += tabOffset(curLevel + 1) + "Information_for attributes : \n";
    strData += tabOffset(curLevel + 2) + "clang_getIBOutletCollectionType : " + _15_CXType2String(outletCollectionType) + '\n';
}

CXType _7_getIBOutletCollectionType (CXCursor C)
                                    { return clang_getIBOutletCollectionType(C); }