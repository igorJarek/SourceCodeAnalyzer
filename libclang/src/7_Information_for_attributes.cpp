#include "7_Information_for_attributes.h"

void _7_printInformationForAttributes(OutputTree& astExtOutputTree, const CXCursor& cursor, uint32_t curLevel)
{
    CXType outletCollectionType = clang_getIBOutletCollectionType(cursor);                                                          // 1.

    astExtOutputTree.addString(curLevel + 1, "7. Information_for attributes : ");
    astExtOutputTree.addString(curLevel + 2, "clang_getIBOutletCollectionType : ", outletCollectionType);
}

CXType _7_getIBOutletCollectionType (CXCursor C)
                                    { return clang_getIBOutletCollectionType(C); }