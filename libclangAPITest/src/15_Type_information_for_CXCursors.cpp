string _15_CXCursorType2String(const CXCursor& cursor)
{
	CXType		cursorType	= clang_getCursorType		(cursor);	// 1.
	return _15_CXType2String(cursorType);
}

string _15_CXType2String(const CXType& type)
{
	CXString	typeSpelling = clang_getTypeSpelling	(type);		// 2.
	return _11_CXString2String(typeSpelling);
}