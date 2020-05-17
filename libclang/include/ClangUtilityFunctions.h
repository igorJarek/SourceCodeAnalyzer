#pragma once

#include <clang-c/Index.h>

#include <string>

#include "1_Name_Mangling_API_Functions.h"
#include "3_C++_AST_introspection.h"
#include "7_Information_for_attributes.h"
#include "9_Cross-referencing_in_the_AST.h"
#include "15_Type_information_for_CXCursors.h"

using namespace std;

void dumpAST(string& strData, const CXCursor& cursor);

void printCursor(string& strData, const CXCursor& cursor, uint32_t curLevel);
void saveBaseCXCursorInfo(const CXCursor& cursor);