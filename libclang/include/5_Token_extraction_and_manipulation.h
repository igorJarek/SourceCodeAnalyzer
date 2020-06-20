#pragma once

#include <clang-c/Index.h>
#include "UtilityFunctions.h"
#include "StructsEnums2String.h"
#include "8_File_manipulation_routines.h"
#include "21_Physical_source_locations.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/*

    Used:
        2. CXTokenKind 	        clang_getTokenKind      (CXToken)
        3. CXString 	        clang_getTokenSpelling  (CXTranslationUnit, CXToken)
        5. CXSourceRange 	    clang_getTokenExtent    (CXTranslationUnit, CXToken)
        6. void 	            clang_tokenize          (CXTranslationUnit TU, CXSourceRange Range, CXToken **Tokens, unsigned *NumTokens)
        7. void 	            clang_annotateTokens    (CXTranslationUnit TU, CXToken *Tokens, unsigned NumTokens, CXCursor *Cursors)
        8. void 	            clang_disposeTokens     (CXTranslationUnit TU, CXToken *Tokens, unsigned NumTokens)

    Unused:

        1. CXToken * 	        clang_getToken          (CXTranslationUnit TU, CXSourceLocation Location)
        4. CXSourceLocation 	clang_getTokenLocation  (CXTranslationUnit, CXToken)

*/

void _5_token_extraction(const CXTranslationUnit& translationUnit, const string& filePath);

CXToken*            _5_getToken              (CXTranslationUnit TU, CXSourceLocation Location);                                     // 1.
CXTokenKind         _5_getTokenKind          (CXToken Token);                                                                       // 2.
CXString            _5_getTokenSpelling      (CXTranslationUnit TU, CXToken Token);                                                 // 3.
CXSourceLocation    _5_getTokenLocation      (CXTranslationUnit TU, CXToken Token);                                                 // 4.
CXSourceRange       _5_getTokenExtent        (CXTranslationUnit TU, CXToken Token);                                                 // 5.
void                _5_tokenize              (CXTranslationUnit TU, CXSourceRange Range, CXToken **Tokens, unsigned *NumTokens);    // 6.
void                _5_annotateTokens        (CXTranslationUnit TU, CXToken *Tokens, unsigned NumTokens, CXCursor *Cursors);        // 7.
void                _5_disposeTokens         (CXTranslationUnit TU, CXToken *Tokens, unsigned NumTokens);                           // 8.
