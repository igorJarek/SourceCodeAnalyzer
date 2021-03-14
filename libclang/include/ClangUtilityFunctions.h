#pragma once

#include <clang-c/Index.h>

#include <string>
#include <iostream>
#include <sstream>

#include <OutputTree/OutputTree.h>

#include "UtilityFunctions.h"
#include "Paths.h"

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

using std::to_string;

class ClientData
{
public:

    ClientData(CXTranslationUnit tu) :
        translationUnit(tu)
    {
        
    }

    ClientData(const ClientData* clientData)
    {
        translationUnit = clientData->translationUnit;
        treeLevel = clientData->treeLevel;

        astOutputTree = clientData->astOutputTree;
        astExtOutputTree = clientData->astExtOutputTree;
    }

    CXTranslationUnit   translationUnit = nullptr;
    uint32_t            treeLevel{ 0 };

    OutputTree          astOutputTree;
    OutputTree          astExtOutputTree;
};

enum class InfoAction
{
    ADD_INFO,
    ADD_INFO_LINESTAMP,

    SAVE_FILE,
    SAVE_LINESTAMPS_FILE,
};

CXChildVisitResult visitor                  (CXCursor cursor, CXCursor parent, CXClientData client_data);

void               dumpAST                  (uint64_t astExtNode, OutputTree& astOutputTree, const CXCursor& cursor, uint32_t curLevel);
void               printCursor              (const CXTranslationUnit& translationUnit, OutputTree& astExtOutputTree, const CXCursor& cursor, uint32_t curLevel);

uint64_t           saveBaseCXCursorInfo     (const CXTranslationUnit* translationUnit, const CXCursor* cursor, InfoAction action);
uint64_t           saveBaseCXTypeInfo       (const CXTranslationUnit* translationUnit, const CXType*   type,   InfoAction action);
