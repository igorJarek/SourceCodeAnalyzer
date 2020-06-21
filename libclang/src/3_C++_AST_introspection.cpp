#include "3_C++_AST_introspection.h"

void _3_printASTIntrospection(const CXTranslationUnit& translationUnit, string& strData, const CXCursor& cursor, uint32_t curLevel, bool print /* = true */)
{
    uint32_t isConvertingConstructor = _3_CXXConstructor_isConvertingConstructor(cursor);               // 1.
    uint32_t isCopyConstructor       = _3_CXXConstructor_isCopyConstructor(cursor);                     // 2.
    uint32_t isDefaultConstructor    = _3_CXXConstructor_isDefaultConstructor(cursor);                  // 3.
    uint32_t isMoveConstructor       = _3_CXXConstructor_isMoveConstructor(cursor);                     // 4.
    uint32_t isMutable               = _3_CXXField_isMutable(cursor);                                   // 5.
    uint32_t isDefaulted             = _3_CXXMethod_isDefaulted(cursor);                                // 6.
    uint32_t isPureVirtual           = _3_CXXMethod_isPureVirtual(cursor);                              // 7.
    uint32_t isStatic                = _3_CXXMethod_isStatic(cursor);                                   // 8.
    uint32_t isVirtual               = _3_CXXMethod_isVirtual(cursor);                                  // 9.
    uint32_t isAbstract              = _3_CXXRecord_isAbstract(cursor);                                 // 10.
    uint32_t isScoped                = _3_EnumDecl_isScoped(cursor);                                    // 11.
    uint32_t isConst                 = _3_CXXMethod_isConst(cursor);                                    // 12.

    CXCursorKind templateCursorKind        = _3_getTemplateCursorKind(cursor);                          // 13.
    CXCursor     specializedCursorTemplate = _3_getSpecializedCursorTemplate(cursor);                   // 14.

    // check last parameter
    CXSourceRange cursorReferenceNameRange_CXNameRange_WantQualifier    = clang_getCursorReferenceNameRange(cursor, CXNameRange_WantQualifier,    0);       // 15.
    CXSourceRange cursorReferenceNameRange_CXNameRange_WantTemplateArgs = clang_getCursorReferenceNameRange(cursor, CXNameRange_WantTemplateArgs, 0);       // 15.
    CXSourceRange cursorReferenceNameRange_CXNameRange_WantSinglePiece  = clang_getCursorReferenceNameRange(cursor, CXNameRange_WantSinglePiece,  0);       // 15.

    ADD_STRING_OUT_NAME(curLevel + 1, "3. ASTIntrospection : ")

    ADD_STRING_OUT_NL(curLevel + 2, "_3_CXXConstructor_isConvertingConstructor : ",             to_string(isConvertingConstructor))
    ADD_STRING_OUT_NL(curLevel + 2, "_3_CXXConstructor_isCopyConstructor : ",                   to_string(isCopyConstructor))
    ADD_STRING_OUT_NL(curLevel + 2, "_3_CXXConstructor_isDefaultConstructor : ",                to_string(isDefaultConstructor))
    ADD_STRING_OUT_NL(curLevel + 2, "_3_CXXConstructor_isMoveConstructor : ",                   to_string(isMoveConstructor))
    ADD_STRING_OUT_NL(curLevel + 2, "_3_CXXField_isMutable : ",                                 to_string(isMutable))
    ADD_STRING_OUT_NL(curLevel + 2, "_3_CXXMethod_isDefaulted : ",                              to_string(isDefaulted))
    ADD_STRING_OUT_NL(curLevel + 2, "_3_CXXMethod_isPureVirtual : ",                            to_string(isPureVirtual))
    ADD_STRING_OUT_NL(curLevel + 2, "_3_CXXMethod_isStatic : ",                                 to_string(isStatic))
    ADD_STRING_OUT_NL(curLevel + 2, "_3_CXXMethod_isVirtual : ",                                to_string(isVirtual))
    ADD_STRING_OUT_NL(curLevel + 2, "_3_CXXRecord_isAbstract : ",                               to_string(isAbstract))
    ADD_STRING_OUT_NL(curLevel + 2, "_3_EnumDecl_isScoped : ",                                  to_string(isScoped))
    ADD_STRING_OUT_NL(curLevel + 2, "_3_CXXMethod_isConst : ",                                  to_string(isConst))

    ADD_STRING_OUT_NL(curLevel + 2, "_3_getTemplateCursorKind : ",                              CXCursorKind2String(templateCursorKind))
    ADD_STRING_OUT_IF_NL(curLevel + 2, "_3_getSpecializedCursorTemplate : lib/cursors.cur -> ", to_string(saveBaseCXCursorInfo(translationUnit, specializedCursorTemplate)))

    ADD_STRING_OUT_NL(curLevel + 2, "clang_getCursorReferenceNameRange(cursor, CXNameRange_WantQualifier, 0) :\n",    CXSourceRange2String(cursorReferenceNameRange_CXNameRange_WantQualifier,    curLevel + 3))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getCursorReferenceNameRange(cursor, CXNameRange_WantTemplateArgs, 0) :\n", CXSourceRange2String(cursorReferenceNameRange_CXNameRange_WantTemplateArgs, curLevel + 3))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getCursorReferenceNameRange(cursor, CXNameRange_WantSinglePiece, 0) :\n",  CXSourceRange2String(cursorReferenceNameRange_CXNameRange_WantSinglePiece,  curLevel + 3))
}

unsigned            _3_CXXConstructor_isConvertingConstructor   (CXCursor C)
                                                                { return clang_CXXConstructor_isConvertingConstructor(C); }

unsigned            _3_CXXConstructor_isCopyConstructor         (CXCursor C)
                                                                { return clang_CXXConstructor_isCopyConstructor(C); }

unsigned            _3_CXXConstructor_isDefaultConstructor      (CXCursor C)
                                                                { return clang_CXXConstructor_isDefaultConstructor(C); }

unsigned            _3_CXXConstructor_isMoveConstructor         (CXCursor C)
                                                                { return clang_CXXConstructor_isMoveConstructor(C); }

unsigned            _3_CXXField_isMutable                       (CXCursor C)
                                                                { return clang_CXXField_isMutable(C); }

unsigned            _3_CXXMethod_isDefaulted                    (CXCursor C)
                                                                { return clang_CXXMethod_isDefaulted(C); }

unsigned            _3_CXXMethod_isPureVirtual                  (CXCursor C)
                                                                { return clang_CXXMethod_isPureVirtual(C); }

unsigned            _3_CXXMethod_isStatic                       (CXCursor C)
                                                                { return clang_CXXMethod_isStatic(C); }

unsigned            _3_CXXMethod_isVirtual                      (CXCursor C)
                                                                { return clang_CXXMethod_isVirtual(C); }

unsigned            _3_CXXRecord_isAbstract                     (CXCursor C)
                                                                { return clang_CXXRecord_isAbstract(C); }

unsigned            _3_EnumDecl_isScoped                        (CXCursor C)
                                                                { return clang_EnumDecl_isScoped(C); }

unsigned            _3_CXXMethod_isConst                        (CXCursor C)
                                                                { return clang_CXXMethod_isConst(C); }

enum CXCursorKind   _3_getTemplateCursorKind                    (CXCursor C)
                                                                { return clang_getTemplateCursorKind(C); }

CXCursor            _3_getSpecializedCursorTemplate             (CXCursor C)
                                                                { return clang_getSpecializedCursorTemplate(C); }

CXSourceRange       _3_getCursorReferenceNameRange              (CXCursor C, unsigned NameFlags, unsigned PieceIndex)
                                                                { return clang_getCursorReferenceNameRange(C, NameFlags, PieceIndex); }
