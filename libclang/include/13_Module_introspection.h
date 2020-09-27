#pragma once

#include <clang-c/Index.h>
#include <UtilityFunctions.h>
#include <fstream>
#include <string>
#include <iostream>

/*
    https://clang.llvm.org/docs/Modules.html
    Modules are useful insted #include
*/

/*

    Used:

    Unused:

        1. CXModule                 clang_Cursor_getModule                                      (CXCursor C)
        2. CXModule                 clang_getModuleForFile                                      (CXTranslationUnit, CXFile)
        3. CXFile                   clang_Module_getASTFile                                     (CXModule Module)
        4. CXModule                 clang_Module_getParent                                      (CXModule Module)
        5. CXString                 clang_Module_getName                                        (CXModule Module)
        6. CXString                 clang_Module_getFullName                                    (CXModule Module)
        7. int                      clang_Module_isSystem                                       (CXModule Module)
        8. unsigned                 clang_Module_getNumTopLevelHeaders                          (CXTranslationUnit, CXModule Module)
        9. CXFile                   clang_Module_getTopLevelHeader                              (CXTranslationUnit, CXModule Module, unsigned Index)

*/

// Clang Functions

CXModule        _13_Cursor_getModule                (CXCursor C);                                                           // 1.
CXModule        _13_getModuleForFile                (CXTranslationUnit TranslationUnit, CXFile File);                       // 2.
CXFile          _13_Module_getASTFile               (CXModule Module);                                                      // 3.
CXModule        _13_Module_getParent                (CXModule Module);                                                      // 4.
CXString        _13_Module_getName                  (CXModule Module);                                                      // 5.
CXString        _13_Module_getFullName              (CXModule Module);                                                      // 6.
int             _13_Module_isSystem                 (CXModule Module);                                                      // 7.
unsigned        _13_Module_getNumTopLevelHeaders    (CXTranslationUnit TranslationUnit, CXModule Module);                   // 8.
CXFile          _13_Module_getTopLevelHeader        (CXTranslationUnit TranslationUnit, CXModule Module, unsigned Index);   // 9.
