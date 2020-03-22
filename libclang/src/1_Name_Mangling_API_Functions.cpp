#include "1_Name_Mangling_API_Functions.h"

void _1_printMangling(shared_ptr<HTMLBuilder> html, uint32_t curLevel, const CXCursor& cursor)
{
	html->addTable("1. Mangling", "MANGLING", { "ID", "Function name", "Value type", "Value" });

	CXString mangling = clang_Cursor_getMangling(cursor);				// 1.
	CXStringSet* CXXManglings = clang_Cursor_getCXXManglings(cursor);	// 2.

	html->addTableRow("MANGLING", {"1", "clang_Cursor_getMangling", "Return", _11_CXString2String(mangling) });
	html->addTableRow("MANGLING", {"2", "clang_Cursor_getCXXManglings", "", ""});


	vector<string> CXXManglingsStrings = _11_CXStringSet2StringVec(CXXManglings);
	for (string str : CXXManglingsStrings)
		strData += tabOffset(curLevel + 3) + str + '\n';

	_11_releaseCXStringSet(CXXManglings);
}

