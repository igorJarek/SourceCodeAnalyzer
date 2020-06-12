#pragma once

#include <clang-c/Index.h>
#include <UtilityFunctions.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/*

	Used:

		2. CXSourceLocation			clang_getCursorLocation										(CXCursor C)
		3. CXSourceRange			clang_getCursorExtent										(CXCursor C)

	Unused:

		1. CXCursor					clang_getCursor												(CXTranslationUnit, CXSourceLocation)

*/

void _10_printMappingBetweenCursorsAndSourceCode(string& strData, const CXCursor& cursor, uint32_t curLevel);

CXCursor            _10_getCursor               (CXTranslationUnit TU, CXSourceLocation SourceLocation);
CXSourceLocation    _10_getCursorLocation       (CXCursor C);
CXSourceRange       _10_getCursorExtent         (CXCursor C);
