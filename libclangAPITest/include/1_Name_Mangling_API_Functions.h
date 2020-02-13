#pragma once

#include <clang-c/Index.h>
#include "11_String_manipulation_routines.h"
#include "UtilityFunctions.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/*
	1. CXString 		clang_Cursor_getMangling		(CXCursor)
	2. CXStringSet* 	clang_Cursor_getCXXManglings	(CXCursor)
	3. CXStringSet* 	clang_Cursor_getObjCManglings	(CXCursor)	// Only for ObjC
*/

void _1_printMangling(string& strData, const CXCursor& cursor, uint32_t curLevel);