#include "7_Information_for_attributes.h"

void _7_printInformationForAttributes(string& strData, const CXCursor& cursor, uint32_t curLevel)
{
	strData += tabOffset(curLevel + 1) + "Information_for attributes : \n";
	CXType outletCollectionType = clang_getIBOutletCollectionType(cursor);
}