#include "3_C++_AST_introspection.h"

void _3_printASTIntrospection(const CXTranslationUnit& translationUnit, OutputTree& astExtOutputTree, const CXCursor& cursor, uint32_t curLevel, bool print /* = true */)
{
    uint32_t isConvertingConstructor = clang_CXXConstructor_isConvertingConstructor(cursor);               // 1.
    uint32_t isCopyConstructor       = clang_CXXConstructor_isCopyConstructor(cursor);                     // 2.
    uint32_t isDefaultConstructor    = clang_CXXConstructor_isDefaultConstructor(cursor);                  // 3.
    uint32_t isMoveConstructor       = clang_CXXConstructor_isMoveConstructor(cursor);                     // 4.
    uint32_t isMutable               = clang_CXXField_isMutable(cursor);                                   // 5.
    uint32_t isDefaulted             = clang_CXXMethod_isDefaulted(cursor);                                // 6.
    uint32_t isPureVirtual           = clang_CXXMethod_isPureVirtual(cursor);                              // 7.
    uint32_t isStatic                = clang_CXXMethod_isStatic(cursor);                                   // 8.
    uint32_t isVirtual               = clang_CXXMethod_isVirtual(cursor);                                  // 9.
    uint32_t isAbstract              = clang_CXXRecord_isAbstract(cursor);                                 // 10.
    uint32_t isScoped                = clang_EnumDecl_isScoped(cursor);                                    // 11.
    uint32_t isConst                 = clang_CXXMethod_isConst(cursor);                                    // 12.

    CXCursorKind templateCursorKind        = clang_getTemplateCursorKind(cursor);                          // 13.
    CXCursor     specializedCursorTemplate = clang_getSpecializedCursorTemplate(cursor);                   // 14.

    // check last parameter
    CXSourceRange cursorReferenceNameRange_CXNameRange_WantQualifier    = clang_getCursorReferenceNameRange(cursor, CXNameRange_WantQualifier,    0);       // 15.
    CXSourceRange cursorReferenceNameRange_CXNameRange_WantTemplateArgs = clang_getCursorReferenceNameRange(cursor, CXNameRange_WantTemplateArgs, 0);       // 15.
    CXSourceRange cursorReferenceNameRange_CXNameRange_WantSinglePiece  = clang_getCursorReferenceNameRange(cursor, CXNameRange_WantSinglePiece,  0);       // 15.

    astExtOutputTree.addString(curLevel + 1, "3. ASTIntrospection : ");

    astExtOutputTree.addString(curLevel + 2, "clang_CXXConstructor_isConvertingConstructor : ",             isConvertingConstructor);
    astExtOutputTree.addString(curLevel + 2, "clang_CXXConstructor_isCopyConstructor : ",                   isCopyConstructor);
    astExtOutputTree.addString(curLevel + 2, "clang_CXXConstructor_isDefaultConstructor : ",                isDefaultConstructor);
    astExtOutputTree.addString(curLevel + 2, "clang_CXXConstructor_isMoveConstructor : ",                   isMoveConstructor);
    astExtOutputTree.addString(curLevel + 2, "clang_CXXField_isMutable : ",                                 isMutable);
    astExtOutputTree.addString(curLevel + 2, "clang_CXXMethod_isDefaulted : ",                              isDefaulted);
    astExtOutputTree.addString(curLevel + 2, "clang_CXXMethod_isPureVirtual : ",                            isPureVirtual);
    astExtOutputTree.addString(curLevel + 2, "clang_CXXMethod_isStatic : ",                                 isStatic);
    astExtOutputTree.addString(curLevel + 2, "clang_CXXMethod_isVirtual : ",                                isVirtual);
    astExtOutputTree.addString(curLevel + 2, "clang_CXXRecord_isAbstract : ",                               isAbstract);
    astExtOutputTree.addString(curLevel + 2, "clang_EnumDecl_isScoped : ",                                  isScoped);
    astExtOutputTree.addString(curLevel + 2, "clang_CXXMethod_isConst : ",                                  isConst);

    astExtOutputTree.addString(curLevel + 2, "clang_getTemplateCursorKind : ",                              _17_getCursorKindSpelling(templateCursorKind));

    if(print)
        astExtOutputTree.addString(curLevel + 2, "clang_getSpecializedCursorTemplate : lib/cursors.cur -> ",    saveBaseCXCursorInfo(&translationUnit, &specializedCursorTemplate));

    astExtOutputTree.addCXSourceRange(curLevel + 2, "clang_getCursorReferenceNameRange(cursor, CXNameRange_WantQualifier, 0) : ",    cursorReferenceNameRange_CXNameRange_WantQualifier);
    astExtOutputTree.addCXSourceRange(curLevel + 2, "clang_getCursorReferenceNameRange(cursor, CXNameRange_WantTemplateArgs, 0) : ", cursorReferenceNameRange_CXNameRange_WantTemplateArgs);
    astExtOutputTree.addCXSourceRange(curLevel + 2, "clang_getCursorReferenceNameRange(cursor, CXNameRange_WantSinglePiece, 0) : ",  cursorReferenceNameRange_CXNameRange_WantSinglePiece);
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
