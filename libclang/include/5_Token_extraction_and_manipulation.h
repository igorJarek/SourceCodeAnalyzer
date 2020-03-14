#pragma once

#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/*
    1. CXToken * 	        clang_getToken          (CXTranslationUnit TU, CXSourceLocation Location)
    2. CXTokenKind 	        clang_getTokenKind      (CXToken)
    3. CXString 	        clang_getTokenSpelling  (CXTranslationUnit, CXToken)
    4. CXSourceLocation 	clang_getTokenLocation  (CXTranslationUnit, CXToken)
    5. CXSourceRange 	    clang_getTokenExtent    (CXTranslationUnit, CXToken)
    6. void 	            clang_tokenize          (CXTranslationUnit TU, CXSourceRange Range, CXToken **Tokens, unsigned *NumTokens)
    7. void 	            clang_annotateTokens    (CXTranslationUnit TU, CXToken *Tokens, unsigned NumTokens, CXCursor *Cursors)
    8. void 	            clang_disposeTokens     (CXTranslationUnit TU, CXToken *Tokens, unsigned NumTokens)
*/