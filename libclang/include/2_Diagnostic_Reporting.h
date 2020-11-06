#pragma once

#include "UtilityFunctions.h"
#include "11_String_manipulation_routines.h"
#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

using std::to_string;

/*
    Used:

        1.  unsigned                    clang_getNumDiagnosticsInSet            (CXDiagnosticSet Diags)
        2.  CXDiagnostic                clang_getDiagnosticInSet                (CXDiagnosticSet Diags, unsigned Index)
        4.  void                        clang_disposeDiagnosticSet              (CXDiagnosticSet Diags)
        6.  unsigned                    clang_getNumDiagnostics                 (CXTranslationUnit Unit)
        7.  CXDiagnostic                clang_getDiagnostic                     (CXTranslationUnit Unit, unsigned Index)
        8.  CXDiagnosticSet             clang_getDiagnosticSetFromTU            (CXTranslationUnit Unit)
        9.  void                        clang_disposeDiagnostic                 (CXDiagnostic Diagnostic)
        10. CXString                    clang_formatDiagnostic                  (CXDiagnostic Diagnostic, unsigned Options)
        11. unsigned                    clang_defaultDiagnosticDisplayOptions   (void)
        12. enum CXDiagnosticSeverity   clang_getDiagnosticSeverity             (CXDiagnostic)
        13. CXSourceLocation            clang_getDiagnosticLocation             (CXDiagnostic)
        14. CXString                    clang_getDiagnosticSpelling             (CXDiagnostic)
        15. CXString                    clang_getDiagnosticOption               (CXDiagnostic Diag, CXString * Disable)
        16. unsigned                    clang_getDiagnosticCategory             (CXDiagnostic)
        18. CXString                    clang_getDiagnosticCategoryText         (CXDiagnostic)
        19. unsigned                    clang_getDiagnosticNumRanges            (CXDiagnostic)
        20. CXSourceRange               clang_getDiagnosticRange                (CXDiagnostic Diagnostic, unsigned Range)
        21. unsigned                    clang_getDiagnosticNumFixIts            (CXDiagnostic Diagnostic)
        22. CXString                    clang_getDiagnosticFixIt                (CXDiagnostic Diagnostic, unsigned FixIt, CXSourceRange * ReplacementRange)

    Unused:

        3.  CXDiagnosticSet             clang_loadDiagnostics                   (const char* file, enum CXLoadDiag_Error* error, CXString* errorString)
        5.  CXDiagnosticSet             clang_getChildDiagnostics               (CXDiagnostic D)                                                                    // ??
        17. CXString                    clang_getDiagnosticCategoryName         (unsigned Category)                                                                 // DEPRECATED
*/

// Print Function

void _2_diagnostic_reporting(CXTranslationUnit& translationUnit, const string& filePath);
void _2_printDiagnostic(OutputTree& outputTree, const CXDiagnostic& diagnostic);

// Clang Functions

unsigned                    _2_getNumDiagnosticsInSet               (CXDiagnosticSet Diags);                                                            // 1.
CXDiagnostic                _2_getDiagnosticInSet                   (CXDiagnosticSet Diags, unsigned Index);                                            // 2.
CXDiagnosticSet             _2_loadDiagnostics                      (const char *file, enum CXLoadDiag_Error *error, CXString *errorString);            // 3.
void                        _2_disposeDiagnosticSet                 (CXDiagnosticSet Diags);                                                            // 4.
CXDiagnosticSet             _2_getChildDiagnostics                  (CXDiagnostic D);                                                                   // 5.
unsigned                    _2_getNumDiagnostics                    (CXTranslationUnit Unit);                                                           // 6.
CXDiagnostic                _2_getDiagnostic                        (CXTranslationUnit Unit, unsigned Index);                                           // 7.
CXDiagnosticSet             _2_getDiagnosticSetFromTU               (CXTranslationUnit Unit);                                                           // 8.
void                        _2_disposeDiagnostic                    (CXDiagnostic Diagnostic);                                                          // 9.
CXString                    _2_formatDiagnostic                     (CXDiagnostic Diagnostic, unsigned Options);                                        // 10.
unsigned                    _2_defaultDiagnosticDisplayOptions      (void);                                                                             // 11.
enum CXDiagnosticSeverity   _2_getDiagnosticSeverity                (CXDiagnostic Diagnostic);                                                          // 12.
CXSourceLocation            _2_getDiagnosticLocation                (CXDiagnostic Diagnostic);                                                          // 13.
CXString                    _2_getDiagnosticSpelling                (CXDiagnostic Diagnostic);                                                          // 14.
CXString                    _2_getDiagnosticOption                  (CXDiagnostic Diagnostic, CXString *Disable);                                       // 15.
unsigned                    _2_getDiagnosticCategory                (CXDiagnostic Diagnostic);                                                          // 16.
CXString                    _2_getDiagnosticCategoryText            (CXDiagnostic Diagnostic);                                                          // 18.
unsigned                    _2_getDiagnosticNumRanges               (CXDiagnostic Diagnostic);                                                          // 19.
CXSourceRange               _2_getDiagnosticRange                   (CXDiagnostic Diagnostic, unsigned Range);                                          // 20.
unsigned                    _2_getDiagnosticNumFixIts               (CXDiagnostic Diagnostic);                                                          // 21.
CXString                    _2_getDiagnosticFixIt                   (CXDiagnostic Diagnostic, unsigned FixIt, CXSourceRange *ReplacementRange);         // 22.
