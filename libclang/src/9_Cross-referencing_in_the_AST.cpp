#include "9_Cross-referencing_in_the_AST.h"

void _9_printCrossReferencingInTheAST(const CXTranslationUnit& translationUnit, OutputTree& astExtOutputTree, const CXCursor& cursor, uint32_t curLevel, bool cursorStopRecursion)
{
    CXString         cursorUSR               = clang_getCursorUSR(cursor);                                                                                      // 1.
    CXString         cursorSpelling          = clang_getCursorSpelling(cursor);                                                                                 // 8.
    CXSourceRange    spellingNameRange       = clang_Cursor_getSpellingNameRange(cursor, 0, 0);                                                                 // 9.    check last 2 parameters
    CXPrintingPolicy cursorPrintingPolicy    = clang_getCursorPrintingPolicy(cursor);                                                                           // 12.
    CXString         cursorPrettyPrinted     = clang_getCursorPrettyPrinted(cursor, cursorPrintingPolicy);                                                      // 14.   add more cases with cursorPrintingPolicy

    CXString         cursorDisplayName       = clang_getCursorDisplayName(cursor);                                                                              // 15.
    CXCursor         cursorReferenced        = clang_getCursorReferenced(cursor);                                                                               // 16.
    CXCursor         cursorDefinition        = clang_getCursorDefinition(cursor);                                                                               // 17.
    uint32_t         isCursorDefinition      = clang_isCursorDefinition(cursor);                                                                                // 18.
    CXCursor         canonicalCursor         = clang_getCanonicalCursor(cursor);                                                                                // 19.
    int32_t          isDynamicCall           = clang_Cursor_isDynamicCall(cursor);                                                                              // 21.

    CXType           receiverType;
    if (clang_isExpression(cursor.kind)) // without this check -> libclang.lib throws error
        receiverType = clang_Cursor_getReceiverType(cursor);                                                                                                    // 22.

    uint32_t         isVariadic              = clang_Cursor_isVariadic(cursor);                                                                                 // 28.

    CXString         language, definedIn;
    uint32_t         isGenerated;
    uint32_t         isExternalSymbol        = clang_Cursor_isExternalSymbol(cursor, &language, &definedIn, &isGenerated);                                      // 29.

    CXSourceRange    commentRange            = clang_Cursor_getCommentRange(cursor);                                                                            // 30.
    CXString         rawCommentText          = clang_Cursor_getRawCommentText(cursor);                                                                          // 31.
    CXString         briefCommentText        = clang_Cursor_getBriefCommentText(cursor);                                                                        // 32.

    astExtOutputTree.addString(curLevel + 1, "9. Cross-referencing in the AST : ");

    astExtOutputTree.addString(curLevel + 2, "clang_getCursorUSR : ",                               cursorUSR);
    astExtOutputTree.addString(curLevel + 2, "clang_getCursorSpelling : ",                          cursorSpelling);

    if (spellingNameRange.ptr_data[0] != nullptr && spellingNameRange.ptr_data[1] != nullptr)
        astExtOutputTree.addCXSourceRange(curLevel + 2, "clang_Cursor_getSpellingNameRange : ",     spellingNameRange);
    else
        astExtOutputTree.addString(curLevel + 2, "clang_Cursor_getSpellingNameRange : ",            "Null");

    astExtOutputTree.addCXPrintingPolicy(curLevel + 2, "clang_getCursorPrintingPolicy : ",          cursorPrintingPolicy);

    //astExtOutputTree.addString(curLevel + 2, "clang_getCursorPrettyPrinted : ",                   cursorPrettyPrinted); // multilines source code destroy line counting
    astExtOutputTree.addString(curLevel + 2, "clang_getCursorDisplayName : ",                       cursorDisplayName);

    if(cursorStopRecursion)
    {
        astExtOutputTree.addString(curLevel + 2, "clang_getCursorReferenced : lib/cursors.cur -> ", saveBaseCXCursorInfo(&translationUnit, &cursorReferenced, InfoAction::ADD_INFO));
        astExtOutputTree.addString(curLevel + 2, "clang_getCursorDefinition : lib/cursors.cur -> ", saveBaseCXCursorInfo(&translationUnit, &cursorDefinition, InfoAction::ADD_INFO));
    }

    astExtOutputTree.addString(curLevel + 2, "clang_isCursorDefinition : ",                         isCursorDefinition);

    if(cursorStopRecursion)
        astExtOutputTree.addString(curLevel + 2, "clang_getCanonicalCursor : lib/cursors.cur -> ",  saveBaseCXCursorInfo(&translationUnit, &canonicalCursor, InfoAction::ADD_INFO));

    astExtOutputTree.addString(curLevel + 2, "clang_Cursor_isDynamicCall : ",                       isDynamicCall);

    if(_19_isExpression(cursor.kind)) // without this check -> libclang.lib throws error
        astExtOutputTree.addString(curLevel + 2, "clang_Cursor_getReceiverType : lib/types.type -> ", saveBaseCXTypeInfo(nullptr, &receiverType, InfoAction::ADD_INFO));
    else
        astExtOutputTree.addString(curLevel + 2, "clang_Cursor_getReceiverType : ",                 "Null");

    astExtOutputTree.addString(curLevel + 2, "clang_Cursor_isVariadic : ",                          isVariadic);

    astExtOutputTree.addString(curLevel + 2, "clang_Cursor_isExternalSymbol [ret] : ",              isExternalSymbol);

    if(isExternalSymbol)
    {
        astExtOutputTree.addString(curLevel + 2, "clang_Cursor_isExternalSymbol [language] : ",     language);
        astExtOutputTree.addString(curLevel + 2, "clang_Cursor_isExternalSymbol [definedIn] : ",    definedIn);
        astExtOutputTree.addString(curLevel + 2, "clang_Cursor_isExternalSymbol [isGenerated] : ",  isGenerated);
    }

    astExtOutputTree.addCXSourceRange(curLevel + 2, "clang_Cursor_getCommentRange : ",              commentRange);
    astExtOutputTree.addString(curLevel + 2, "clang_Cursor_getRawCommentText : ",                   rawCommentText);
    astExtOutputTree.addString(curLevel + 2, "clang_Cursor_getBriefCommentText : ",                 briefCommentText);

    clang_PrintingPolicy_dispose(cursorPrintingPolicy);                                                                                                        // 13.
}

CXString            _9_getCursorUSR                         (CXCursor C)
                                                            { return clang_getCursorUSR(C); }

CXString            _9_constructUSR_ObjCClass               (const char *class_name)
                                                            { return clang_constructUSR_ObjCClass(class_name); }

CXString            _9_constructUSR_ObjCCategory            (const char *class_name, const char *category_name)
                                                            { return clang_constructUSR_ObjCCategory(class_name, category_name); }

CXString            _9_constructUSR_ObjCProtocol            (const char *protocol_name)
                                                            { return clang_constructUSR_ObjCProtocol(protocol_name); }

CXString            _9_constructUSR_ObjCIvar                (const char *name, CXString classUSR)
                                                            { return clang_constructUSR_ObjCIvar(name, classUSR); }

CXString            _9_constructUSR_ObjCMethod              (const char *name, unsigned isInstanceMethod, CXString classUSR)
                                                            { return clang_constructUSR_ObjCMethod(name, isInstanceMethod, classUSR); }

CXString            _9_constructUSR_ObjCProperty            (const char *property, CXString classUSR)
                                                            { return clang_constructUSR_ObjCProperty(property, classUSR); }

CXString            _9_getCursorSpelling                    (CXCursor C)
                                                            { return clang_getCursorSpelling(C); }

CXSourceRange       _9_Cursor_getSpellingNameRange          (CXCursor C, unsigned pieceIndex, unsigned options)
                                                            { return clang_Cursor_getSpellingNameRange(C, pieceIndex, options); }

unsigned            _9_PrintingPolicy_getProperty           (CXPrintingPolicy Policy, enum CXPrintingPolicyProperty Property)
                                                            { return clang_PrintingPolicy_getProperty(Policy, Property); }

void                _9_PrintingPolicy_setProperty           (CXPrintingPolicy Policy, enum CXPrintingPolicyProperty Property, unsigned Value)
                                                            { return clang_PrintingPolicy_setProperty(Policy, Property, Value); }

CXPrintingPolicy    _9_getCursorPrintingPolicy              (CXCursor C)
                                                            { return clang_getCursorPrintingPolicy(C); }

void                _9_PrintingPolicy_dispose               (CXPrintingPolicy Policy)
                                                            { return clang_PrintingPolicy_dispose(Policy); }

CXString            _9_getCursorPrettyPrinted               (CXCursor Cursor, CXPrintingPolicy Policy)
                                                            { return clang_getCursorPrettyPrinted(Cursor, Policy); }

CXString            _9_getCursorDisplayName                 (CXCursor C)
                                                            { return clang_getCursorDisplayName(C); }

CXCursor            _9_getCursorReferenced                  (CXCursor C)
                                                            { return clang_getCursorReferenced(C); }

CXCursor            _9_getCursorDefinition                  (CXCursor C)
                                                            { return clang_getCursorDefinition(C); }

unsigned            _9_isCursorDefinition                   (CXCursor C)
                                                            { return clang_isCursorDefinition(C); }

CXCursor            _9_getCanonicalCursor                   (CXCursor C)
                                                            { return clang_getCanonicalCursor(C); }

int                 _9_getObjCSelectorIndex                 (CXCursor C)
                                                            { return clang_Cursor_getObjCSelectorIndex(C); }

int                 _9_isDynamicCall                        (CXCursor C)
                                                            { return clang_Cursor_isDynamicCall(C); }

CXType              _9_getReceiverType                      (CXCursor C)
                                                            { return clang_Cursor_getReceiverType(C); }

unsigned            _9_getObjCPropertyAttributes            (CXCursor C, unsigned reserved)
                                                            { return clang_Cursor_getObjCPropertyAttributes(C, reserved); }

CXString            _9_getObjCPropertyGetterName            (CXCursor C)
                                                            { return clang_Cursor_getObjCPropertyGetterName(C); }

CXString            _9_getObjCPropertySetterName            (CXCursor C)
                                                            { return clang_Cursor_getObjCPropertySetterName(C); }

unsigned            _9_getObjCDeclQualifiers                (CXCursor C)
                                                            { return clang_Cursor_getObjCDeclQualifiers(C); }

unsigned            _9_isObjCOptional                       (CXCursor C)
                                                            { return clang_Cursor_isObjCOptional(C); }

unsigned            _9_isVariadic                           (CXCursor C)
                                                            { return clang_Cursor_isVariadic(C); }

unsigned            _9_isExternalSymbol                     (CXCursor C, CXString *language, CXString *definedIn, unsigned *isGenerated)
                                                            { return clang_Cursor_isExternalSymbol(C, language, definedIn, isGenerated); }

CXSourceRange       _9_getCommentRange                      (CXCursor C)
                                                            { return clang_Cursor_getCommentRange(C); }

CXString            _9_getRawCommentText                    (CXCursor C)
                                                            { return clang_Cursor_getRawCommentText(C); }

CXString            _9_getBriefCommentText                  (CXCursor C)
                                                            { return clang_Cursor_getBriefCommentText(C); }
