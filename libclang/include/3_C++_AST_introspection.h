#pragma once

#include <clang-c/Index.h>
#include "11_String_manipulation_routines.h"
#include "UtilityFunctions.h"
#include <fstream>
#include <string>
#include <iostream>

using std::to_string;

/*
    Used:

        1. unsigned                 clang_CXXConstructor_isConvertingConstructor    (CXCursor C)
        2. unsigned                 clang_CXXConstructor_isCopyConstructor          (CXCursor C)
        3. unsigned                 clang_CXXConstructor_isDefaultConstructor       (CXCursor C)
        4. unsigned                 clang_CXXConstructor_isMoveConstructor          (CXCursor C)
        5. unsigned                 clang_CXXField_isMutable                        (CXCursor C)
        6. unsigned                 clang_CXXMethod_isDefaulted                     (CXCursor C)
        7. unsigned                 clang_CXXMethod_isPureVirtual                   (CXCursor C)
        8. unsigned                 clang_CXXMethod_isStatic                        (CXCursor C)
        9. unsigned                 clang_CXXMethod_isVirtual                       (CXCursor C)
        10. unsigned                clang_CXXRecord_isAbstract                      (CXCursor C)
        11. unsigned                clang_EnumDecl_isScoped                         (CXCursor C)
        12. unsigned                clang_CXXMethod_isConst                         (CXCursor C)
        13. enum CXCursorKind       clang_getTemplateCursorKind                     (CXCursor C)
        14. CXCursor                clang_getSpecializedCursorTemplate              (CXCursor C)
        15. CXSourceRange           clang_getCursorReferenceNameRange               (CXCursor C, unsigned NameFlags, unsigned PieceIndex)

    Unused:

*/

// Print Function

void _3_printASTIntrospection(const CXTranslationUnit& translationUnit, OutputTree& astExtOutputTree, const CXCursor& cursor, uint32_t curLevel, bool print = true);

// Clang Functions

unsigned            _3_CXXConstructor_isConvertingConstructor   (CXCursor C);                                               // 1.
unsigned            _3_CXXConstructor_isCopyConstructor         (CXCursor C);                                               // 2.
unsigned            _3_CXXConstructor_isDefaultConstructor      (CXCursor C);                                               // 3.
unsigned            _3_CXXConstructor_isMoveConstructor         (CXCursor C);                                               // 4.
unsigned            _3_CXXField_isMutable                       (CXCursor C);                                               // 5.
unsigned            _3_CXXMethod_isDefaulted                    (CXCursor C);                                               // 6.
unsigned            _3_CXXMethod_isPureVirtual                  (CXCursor C);                                               // 7.
unsigned            _3_CXXMethod_isStatic                       (CXCursor C);                                               // 8.
unsigned            _3_CXXMethod_isVirtual                      (CXCursor C);                                               // 9.
unsigned            _3_CXXRecord_isAbstract                     (CXCursor C);                                               // 10.
unsigned            _3_EnumDecl_isScoped                        (CXCursor C);                                               // 11.
unsigned            _3_CXXMethod_isConst                        (CXCursor C);                                               // 12.
enum CXCursorKind   _3_getTemplateCursorKind                    (CXCursor C);                                               // 13.
CXCursor            _3_getSpecializedCursorTemplate             (CXCursor C);                                               // 14.
CXSourceRange       _3_getCursorReferenceNameRange              (CXCursor C, unsigned NameFlags, unsigned PieceIndex);      // 15.
