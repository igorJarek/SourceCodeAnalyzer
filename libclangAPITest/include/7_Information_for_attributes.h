#pragma once

#include <clang-c/Index.h>
#include "UtilityFunctions.h"
#include "15_Type_information_for_CXCursors.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/*
	1. CXType	clang_getIBOutletCollectionType		(CXCursor)
*/

void _7_printInformationForAttributes(string& strData, const CXCursor& cursor, uint32_t curLevel);