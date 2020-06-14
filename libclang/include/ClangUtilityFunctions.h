#pragma once

#include <clang-c/Index.h>

#include <string>
#include <iostream>

#include "UtilityFunctions.h"

#include "1_Name_Mangling_API_Functions.h"
#include "3_C++_AST_introspection.h"
#include "7_Information_for_attributes.h"
#include "9_Cross-referencing_in_the_AST.h"
#include "10_Mapping_between_cursors_and_source_code.h"
#include "13_Module_introspection.h"
#include "15_Type_information_for_CXCursors.h"
#include "18_Miscellaneous_utility_functions.h"
#include "19_Cursor_manipulations.h"

using namespace std;

void dumpAST(string& strData, const CXCursor& cursor);

void printCursor(const CXTranslationUnit& translationUnit, string& strData, const CXCursor& cursor, uint32_t curLevel);
uint64_t saveBaseCXCursorInfo(const CXCursor& cursor);
string getBaseCXFileInfo(const CXTranslationUnit& translationUnit, const CXFile& file, uint32_t curLevel);
