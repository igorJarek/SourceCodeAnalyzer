#pragma once

#include <clang-c/Index.h>
#include "UtilityFunctions.h"
#include "8_File_manipulation_routines.h"
#include "21_Physical_source_locations.h"
#include <fstream>
#include <string>
#include <iostream>

using std::to_string;

/*

    Used:
        2. CXTokenKind          clang_getTokenKind      (CXToken Token)
        3. CXString             clang_getTokenSpelling  (CXTranslationUnit TU, CXToken Token)
        4. CXSourceLocation     clang_getTokenLocation  (CXTranslationUnit TU, CXToken)
        5. CXSourceRange        clang_getTokenExtent    (CXTranslationUnit TU, CXToken Token)
        6. void                 clang_tokenize          (CXTranslationUnit TU, CXSourceRange Range, CXToken **Tokens, unsigned *NumTokens)
        8. void                 clang_disposeTokens     (CXTranslationUnit TU, CXToken *Tokens, unsigned NumTokens)

    Unused:

        1. CXToken *            clang_getToken          (CXTranslationUnit TU, CXSourceLocation Location)
        7. void                 clang_annotateTokens    (CXTranslationUnit TU, CXToken *Tokens, unsigned NumTokens, CXCursor *Cursors)  used _10_getCursor() insted of clang_annotateTokens()

*/

// Print Function

void _5_token_extraction(const CXTranslationUnit& translationUnit, const string& filePath);

// Clang Functions

CXToken*            _5_getToken              (CXTranslationUnit TU, CXSourceLocation Location);                                     // 1.
CXTokenKind         _5_getTokenKind          (CXToken Token);                                                                       // 2.
CXString            _5_getTokenSpelling      (CXTranslationUnit TU, CXToken Token);                                                 // 3.
CXSourceLocation    _5_getTokenLocation      (CXTranslationUnit TU, CXToken Token);                                                 // 4.
CXSourceRange       _5_getTokenExtent        (CXTranslationUnit TU, CXToken Token);                                                 // 5.
void                _5_tokenize              (CXTranslationUnit TU, CXSourceRange Range, CXToken **Tokens, unsigned *NumTokens);    // 6.
void                _5_annotateTokens        (CXTranslationUnit TU, CXToken *Tokens, unsigned NumTokens, CXCursor *Cursors);        // 7.
void                _5_disposeTokens         (CXTranslationUnit TU, CXToken *Tokens, unsigned NumTokens);                           // 8.
