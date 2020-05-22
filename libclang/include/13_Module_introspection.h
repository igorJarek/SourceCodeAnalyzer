#pragma once

#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

CXModule        _13_Cursor_getModule                (CXCursor C);
CXModule        _13_getModuleForFile                (CXTranslationUnit TranslationUnit, CXFile File);
CXFile          _13_Module_getASTFile               (CXModule Module);
CXModule        _13_Module_getParent                (CXModule Module);
CXString        _13_Module_getName                  (CXModule Module);
CXString        _13_Module_getFullName              (CXModule Module);
int             _13_Module_isSystem                 (CXModule Module);
unsigned        _13_Module_getNumTopLevelHeaders    (CXTranslationUnit TranslationUnit, CXModule Module);
CXFile          _13_Module_getTopLevelHeader        (CXTranslationUnit TranslationUnit, CXModule Module, unsigned Index);
