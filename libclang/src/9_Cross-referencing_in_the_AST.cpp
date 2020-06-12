#include "9_Cross-referencing_in_the_AST.h"

void _9_printCrossReferencingInTheAST(string& strData, const CXCursor& cursor, uint32_t curLevel)
{
    strData += tabOffset(curLevel + 1) + "Cross-referencing in the AST : \n";

    CXString         cursorUSR               = clang_getCursorUSR(cursor);                                                                                     // 1.
    CXString         cursorSpelling          = clang_getCursorSpelling(cursor);                                                                                // 8.
    CXSourceRange    spellingNameRange       = clang_Cursor_getSpellingNameRange(cursor, 0, 0);                                                                // 9.    CHECK LAST 2 PARAMETERS
    CXPrintingPolicy cursorPrintingPolicy    = clang_getCursorPrintingPolicy(cursor);                                                                          // 12.
    CXString         cursorPrettyPrinted     = clang_getCursorPrettyPrinted(cursor, cursorPrintingPolicy);                                                     // 14.   dodac wiecej przypadkow cursorPrintingPolicy

    clang_PrintingPolicy_dispose(cursorPrintingPolicy);                                                                                                        // 13.

    CXString         cursorDisplayName       = clang_getCursorDisplayName(cursor);                                                                             // 15.
    CXCursor         cursorReferenced        = clang_getCursorReferenced(cursor);                                                                              // 16.
    CXCursor         cursorDefinition        = clang_getCursorDefinition(cursor);                                                                              // 17.
    uint32_t         isCursorDefinition      = clang_isCursorDefinition(cursor);                                                                               // 18.
    CXCursor         canonicalCursor         = clang_getCanonicalCursor(cursor);                                                                               // 19.
    int32_t          isDynamicCall           = clang_Cursor_isDynamicCall(cursor);                                                                             // 21.
    // CXType        receiverType            = clang_Cursor_getReceiverType(cursor);                                                                           // 22.

    uint32_t         isVariadic              = clang_Cursor_isVariadic(cursor);                                                                                // 28.

    CXString         language;
    CXString         definedIn;
    uint32_t         isGenerated;
    uint32_t         isExternalSymbol        = clang_Cursor_isExternalSymbol(cursor, &language, &definedIn, &isGenerated);                                     // 29.

    CXSourceRange    commentRange            = clang_Cursor_getCommentRange(cursor);                                                                           // 30.
    CXString         rawCommentText          = clang_Cursor_getRawCommentText(cursor);                                                                         // 31.
    CXString         briefCommentText        = clang_Cursor_getBriefCommentText(cursor);                                                                       // 32.


    strData += tabOffset(curLevel + 2) + "clang_getCursorUSR : "                                + _11_CXString2String(cursorUSR)                     + '\n';
    strData += tabOffset(curLevel + 2) + "clang_getCursorSpelling : "                           + _11_CXString2String(cursorSpelling)                + '\n';

    if (spellingNameRange.ptr_data[0] != nullptr && spellingNameRange.ptr_data[1] != nullptr)
        strData += tabOffset(curLevel + 2) + "clang_Cursor_getSpellingNameRange : \n"           + CXSourceRange2String(spellingNameRange, curLevel + 3);

    strData += tabOffset(curLevel + 2) + "clang_getCursorPrintingPolicy : \n";
    strData += CXPrintingPolicy2String(cursorPrintingPolicy, curLevel + 3)                                                                          + '\n';

    strData += tabOffset(curLevel + 2) + "clang_getCursorPrettyPrinted : \n"                    + _11_CXString2String(cursorPrettyPrinted)           + '\n';
    strData += tabOffset(curLevel + 2) + "clang_getCursorDisplayName : "                        + _11_CXString2String(cursorDisplayName)             + '\n';

    strData += tabOffset(curLevel + 2) + "clang_getCursorReferenced : lib/cursors.cur -> "      + to_string(saveBaseCXCursorInfo(cursorReferenced))  + '\n';
    strData += tabOffset(curLevel + 2) + "clang_getCursorDefinition : cursors.cur -> "          + to_string(saveBaseCXCursorInfo(cursorDefinition))  + '\n';

    strData += tabOffset(curLevel + 2) + "clang_isCursorDefinition : "                          + to_string(isCursorDefinition)                      + '\n';

    strData += tabOffset(curLevel + 2) + "clang_getCanonicalCursor : cursors.cur -> "           + to_string(saveBaseCXCursorInfo(canonicalCursor))   + '\n';

    strData += tabOffset(curLevel + 2) + "clang_Cursor_isDynamicCall : "                        + to_string(isDynamicCall)                           + '\n';
    //strData += tabOffset(curLevel + 2) + "clang_Cursor_getReceiverType : "                    + _15_CXType2String(receiverType)                    + '\n';
    strData += tabOffset(curLevel + 2) + "clang_Cursor_isVariadic : "                           + to_string(isVariadic)                              + '\n';

    strData += tabOffset(curLevel + 2) + "clang_Cursor_isExternalSymbol [ret] : "               + to_string(isExternalSymbol)                        + '\n';
    if(isExternalSymbol)
    {
        strData += tabOffset(curLevel + 2) + "clang_Cursor_isExternalSymbol [language] : "      + _11_CXString2String(language)                      + '\n';
        strData += tabOffset(curLevel + 2) + "clang_Cursor_isExternalSymbol [definedIn] : "     + _11_CXString2String(definedIn)                     + '\n';
        strData += tabOffset(curLevel + 2) + "clang_Cursor_isExternalSymbol [isGenerated] : "   + to_string(isGenerated)                             + '\n';
    }

    strData += tabOffset(curLevel + 2) + "clang_Cursor_getRawCommentText [language] : \n"       + CXSourceRange2String(commentRange, (curLevel + 3)) + '\n';
    strData += tabOffset(curLevel + 2) + "clang_Cursor_getRawCommentText [language] : "         + _11_CXString2String(rawCommentText)                + '\n';
    strData += tabOffset(curLevel + 2) + "clang_Cursor_getBriefCommentText [language] : "       + _11_CXString2String(briefCommentText)              + '\n';
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
