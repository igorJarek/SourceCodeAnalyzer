#pragma once

#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/*
	1. CXString 		clang_Cursor_getMangling		(CXCursor)
	2. CXStringSet* 	clang_Cursor_getCXXManglings	(CXCursor)
	3. CXStringSet* 	clang_Cursor_getObjCManglings	(CXCursor)	// Only for ObjC
*/

