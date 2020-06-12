#pragma once

#include <clang-c/Index.h>
#include "11_String_manipulation_routines.h"
#include "UtilityFunctions.h"
#include "StructsEnums2String.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

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
        15. CXSourceRange 	        clang_getCursorReferenceNameRange               (CXCursor C, unsigned NameFlags, unsigned PieceIndex)

    Unused:

        14. CXCursor 	            clang_getSpecializedCursorTemplate              (CXCursor C)
*/

void _3_printASTIntrospection(string& strData, const CXCursor& cursor, uint32_t curLevel);

unsigned            _3_CXXConstructor_isConvertingConstructor   (CXCursor C);
unsigned            _3_CXXConstructor_isCopyConstructor         (CXCursor C);
unsigned            _3_CXXConstructor_isDefaultConstructor      (CXCursor C);
unsigned            _3_CXXConstructor_isMoveConstructor         (CXCursor C);
unsigned            _3_CXXField_isMutable                       (CXCursor C);
unsigned            _3_CXXMethod_isDefaulted                    (CXCursor C);
unsigned            _3_CXXMethod_isPureVirtual                  (CXCursor C);
unsigned            _3_CXXMethod_isStatic                       (CXCursor C);
unsigned            _3_CXXMethod_isVirtual                      (CXCursor C);
unsigned            _3_CXXRecord_isAbstract                     (CXCursor C);
unsigned            _3_EnumDecl_isScoped                        (CXCursor C);
unsigned            _3_CXXMethod_isConst                        (CXCursor C);
enum CXCursorKind   _3_getTemplateCursorKind                    (CXCursor C);
CXCursor            _3_getSpecializedCursorTemplate             (CXCursor C);
CXSourceRange       _3_getCursorReferenceNameRange              (CXCursor C, unsigned NameFlags, unsigned PieceIndex);
