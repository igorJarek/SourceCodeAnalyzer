#pragma once

#include <clang-c/Index.h>

#include <string>
#include <iostream>

#include "UtilityFunctions.h"
#include "LibPath.h"

#include "0_1_Comment_introspection.h"
#include "1_Name_Mangling_API_Functions.h"
#include "3_C++_AST_introspection.h"
#include "7_Information_for_attributes.h"
#include "9_Cross-referencing_in_the_AST.h"
#include "10_Mapping_between_cursors_and_source_code.h"
#include "13_Module_introspection.h"
#include "15_Type_information_for_CXCursors.h"
#include "17_Debugging_facilities.h"
#include "18_Miscellaneous_utility_functions.h"
#include "19_Cursor_manipulations.h"

using namespace std;

class ClientData
{
public:

    ClientData(CXTranslationUnit tu, uint32_t level = 0)
    {
        translationUnit = tu;
        treeLevel       = level;
    }

    CXTranslationUnit   translationUnit;
    uint32_t            treeLevel{ 0 };
    string              astStringData{};
    string              astExtStringData{};
};

CXChildVisitResult visitor                  (CXCursor cursor, CXCursor parent, CXClientData client_data);

void               dumpAST                  (string& strData, const CXCursor& cursor);
void               printCursor              (const CXTranslationUnit& translationUnit, string& strData, const CXCursor& cursor, uint32_t curLevel);

uint64_t           getBaseCXCursorInfo      (const CXTranslationUnit* translationUnit, const CXCursor* cursor, bool saveFile = false);
string             getBaseCXFileInfo        (const CXTranslationUnit& translationUnit, const CXFile& file, uint32_t curLevel);
