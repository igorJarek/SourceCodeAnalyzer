#include "19_Cursor_manipulations.h"

void _19_printCursorManipulations(const CXTranslationUnit& translationUnit, string& strData, const CXCursor& cursor, uint32_t curLevel)
{
    strData += tabOffset(curLevel + 1) + "Cursor manipulations : \n";
     
	uint32_t               hashCursor           = clang_hashCursor(cursor);                                                                                                     // 5.
	CXCursorKind           cursorKind           = clang_getCursorKind(cursor);                                                                                                  // 6.
	uint32_t               isDeclaration        = clang_isDeclaration(cursorKind);                                                                                              // 7.
	uint32_t               isInvalidDeclaration = clang_isInvalidDeclaration(cursor);                                                                                           // 8.
	uint32_t               isReference          = clang_isReference(cursorKind);                                                                                                // 9.
	uint32_t               isExpression         = clang_isExpression(cursorKind);                                                                                               // 10.
	uint32_t               isStatement          = clang_isStatement(cursorKind);                                                                                                // 11.
	uint32_t               isAttribute          = clang_isAttribute(cursorKind);                                                                                                // 12.
	uint32_t               hasAttrs             = clang_Cursor_hasAttrs(cursor);                                                                                                // 13.
	uint32_t               isInvalid            = clang_isInvalid(cursorKind);                                                                                                  // 14.
	uint32_t               isTranslationUnit    = clang_isTranslationUnit(cursorKind);                                                                                          // 15.
	uint32_t               isPreprocessing      = clang_isPreprocessing(cursorKind);                                                                                            // 16.
	uint32_t               isUnexposed          = clang_isUnexposed(cursorKind);                                                                                                // 17.
	CXLinkageKind          cursorLinkage        = clang_getCursorLinkage(cursor);                                                                                               // 18.
	CXVisibilityKind       cursorVisibility     = clang_getCursorVisibility(cursor);                                                                                            // 19.
	CXAvailabilityKind     cursorAvailability   = clang_getCursorAvailability(cursor);                                                                                          // 20.

    int32_t                alwaysDeprecated;
    CXString               deprecatedMessage;
    int32_t                alwaysUnavailable;
    CXString               unavailableMessage;
    CXPlatformAvailability platformAvailability;

    int32_t cursorPlatformAvailability          = clang_getCursorPlatformAvailability(cursor,                                                                                   /* 21. */
                                                                                      &alwaysDeprecated, 
                                                                                      &deprecatedMessage, 
                                                                                      &alwaysUnavailable, 
                                                                                      &unavailableMessage, 
                                                                                      &platformAvailability, 
                                                                                      0);                                                                                       // check last parameter

    CXLanguageKind     cursorLanguage           = clang_getCursorLanguage(cursor);                                                                                              // 23.
    CXTLSKind          TLSKind                  = clang_getCursorTLSKind(cursor);                                                                                               // 24.

    CXCursor           cursorSemanticParent     = clang_getCursorSemanticParent(cursor);                                                                                        // 30.
    CXCursor           CursorLexicalParent      = clang_getCursorLexicalParent(cursor);                                                                                         // 31.

    CXCursor*          overriddens = nullptr;
    uint32_t           num_overridden;
    clang_getOverriddenCursors(cursor, &overriddens, &num_overridden);                                                                                                          // 32.

    CXFile             includedFile             = clang_getIncludedFile(cursor);                                                                                                // 34.

    strData += tabOffset(curLevel + 2)     + "clang_hashCursor : "                                          + to_string(hashCursor)                                             + '\n';
    strData += tabOffset(curLevel + 2)     + "clang_getCursorKind : "                                       + CXCursorKind2String(cursorKind)                                   + '\n';
    strData += tabOffset(curLevel + 2)     + "clang_isDeclaration : "                                       + to_string(isDeclaration)                                          + '\n';
    strData += tabOffset(curLevel + 2)     + "clang_isInvalidDeclaration : "                                + to_string(isInvalidDeclaration)                                   + '\n';
    strData += tabOffset(curLevel + 2)     + "clang_isReference : "                                         + to_string(isReference)                                            + '\n';
    strData += tabOffset(curLevel + 2)     + "clang_isExpression : "                                        + to_string(isExpression)                                           + '\n';
    strData += tabOffset(curLevel + 2)     + "clang_isStatement : "                                         + to_string(isStatement)                                            + '\n';
    strData += tabOffset(curLevel + 2)     + "clang_isAttribute : "                                         + to_string(isAttribute)                                            + '\n';
    strData += tabOffset(curLevel + 2)     + "clang_Cursor_hasAttrs : "                                     + to_string(hasAttrs)                                               + '\n';
    strData += tabOffset(curLevel + 2)     + "clang_isInvalid : "                                           + to_string(isInvalid)                                              + '\n';
    strData += tabOffset(curLevel + 2)     + "clang_isTranslationUnit : "                                   + to_string(isTranslationUnit)                                      + '\n';
    strData += tabOffset(curLevel + 2)     + "clang_isPreprocessing : "                                     + to_string(isPreprocessing)                                        + '\n';
    strData += tabOffset(curLevel + 2)     + "clang_isUnexposed : "                                         + to_string(isUnexposed)                                            + '\n';

    strData += tabOffset(curLevel + 2)     + "clang_getCursorLinkage : "                                    + CXLinkageKind2String(cursorLinkage)                               + '\n';
    strData += tabOffset(curLevel + 2)     + "clang_getCursorVisibility : "                                 + CXVisibilityKind2String(cursorVisibility)                         + '\n';
    strData += tabOffset(curLevel + 2)     + "clang_getCursorAvailability : "                               + CXAvailabilityKind2String(cursorAvailability)                     + '\n';

    strData += tabOffset(curLevel + 2)     + "clang_getCursorPlatformAvailability [return] : "              + to_string(cursorPlatformAvailability)                             + '\n';
    if(cursorPlatformAvailability > 0)
    {
        strData += tabOffset(curLevel + 2) + "clang_getCursorPlatformAvailability [always_deprecated] : "   + to_string(alwaysDeprecated)                                       + '\n';
        strData += tabOffset(curLevel + 2) + "clang_getCursorPlatformAvailability [deprecated_message] : "  + _11_CXString2String(deprecatedMessage)                            + '\n';
        strData += tabOffset(curLevel + 2) + "clang_getCursorPlatformAvailability [always_unavailable] : "  + to_string(alwaysUnavailable)                                      + '\n';
        strData += tabOffset(curLevel + 2) + "clang_getCursorPlatformAvailability [unavailable_message] : " + _11_CXString2String(unavailableMessage)                           + '\n';
        strData += tabOffset(curLevel + 2) + "clang_getCursorPlatformAvailability [availability] : \n"      + CXPlatformAvailability2String(platformAvailability, curLevel + 3) + '\n';

        clang_disposeCXPlatformAvailability(&platformAvailability);                                                                                                             // 22.
    }

    strData += tabOffset(curLevel + 2)     + "clang_getCursorLanguage : "                                   + CXLanguageKind2String(cursorLanguage)                             + '\n';
    strData += tabOffset(curLevel + 2)     + "clang_getCursorTLSKind : "                                    + CXTLSKind2String(TLSKind)                                         + '\n';

    if(!clang_Cursor_isNull(cursorSemanticParent))
        strData += tabOffset(curLevel + 2) + "clang_getCursorSemanticParent : lib/cursors.cur -> "          + to_string(saveBaseCXCursorInfo(cursorSemanticParent))             + '\n';
    else 
        strData += tabOffset(curLevel + 2) + "clang_getCursorSemanticParent : -NULL-\n";

    if(!clang_Cursor_isNull(CursorLexicalParent))
        strData += tabOffset(curLevel + 2) + "clang_getCursorLexicalParent : lib/cursors.cur -> "           + to_string(saveBaseCXCursorInfo(CursorLexicalParent))              + '\n';
    else 
        strData += tabOffset(curLevel + 2) + "clang_getCursorLexicalParent : -NULL-\n";

    strData += tabOffset(curLevel + 2)     + "clang_getOverriddenCursors [num_overridden] : "               + to_string(num_overridden)                                         + '\n';
    if(num_overridden > 0)
    {
        for(uint32_t index { 0 }; index < num_overridden; ++index)
        {
            const CXCursor& overridden = overriddens[index];
            if(!clang_Cursor_isNull(overridden))
                strData += tabOffset(curLevel + 2) + "clang_getOverriddenCursors [" + to_string(index + 1) + "] : lib/cursors.cur -> " + to_string(saveBaseCXCursorInfo(overridden)) + '\n';
        }

        clang_disposeOverriddenCursors(overriddens);                                                                                                                            // 33.
    }

    if(includedFile)
        strData += tabOffset(curLevel + 2) + "clang_getIncludedFile : \n"                                   + getBaseCXFileInfo(translationUnit, includedFile, curLevel + 3)    + '\n';
    else
        strData += tabOffset(curLevel + 2) + "clang_getIncludedFile : -NULL-\n";
    
}

CXCursor                        _19_getNullCursor                       (void)
                                                                        { return clang_getNullCursor(); }

CXCursor                        _19_getTranslationUnitCursor            (CXTranslationUnit TranslationUnit)
                                                                        { return clang_getTranslationUnitCursor(TranslationUnit); }

unsigned                        _19_equalCursors                        (CXCursor CursorA, CXCursor CursorB)
                                                                        { return clang_equalCursors(CursorA, CursorB); }

int                             _19_isNull                              (CXCursor Cursor)
                                                                        { return clang_Cursor_isNull(Cursor); }

unsigned                        _19_hashCursor                          (CXCursor Cursor)
                                                                        { return clang_hashCursor(Cursor); }

enum CXCursorKind               _19_getCursorKind                       (CXCursor Cursor)
                                                                        { return clang_getCursorKind(Cursor); }

unsigned                        _19_isDeclaration                       (enum CXCursorKind CursorKind)
                                                                        { return clang_isDeclaration(CursorKind); }

unsigned                        _19_isInvalidDeclaration                (CXCursor Cursor)
                                                                        { return clang_isInvalidDeclaration(Cursor); }

unsigned                        _19_isReference                         (enum CXCursorKind CursorKind)
                                                                        { return clang_isReference(CursorKind); }

unsigned                        _19_isExpression                        (enum CXCursorKind CursorKind)
                                                                        { return clang_isExpression(CursorKind); }

unsigned                        _19_isStatement                         (enum CXCursorKind CursorKind)
                                                                        { return clang_isStatement(CursorKind); }

unsigned                        _19_isAttribute                         (enum CXCursorKind CursorKind)
                                                                        { return clang_isAttribute(CursorKind); }

unsigned                        _19_hasAttrs                            (CXCursor Cursor)
                                                                        { return clang_Cursor_hasAttrs(Cursor); }

unsigned                        _19_isInvalid                           (enum CXCursorKind CursorKind)
                                                                        { return clang_isInvalid(CursorKind); }

unsigned                        _19_isTranslationUnit                   (enum CXCursorKind CursorKind)
                                                                        { return clang_isTranslationUnit(CursorKind); }

unsigned                        _19_isPreprocessing                     (enum CXCursorKind CursorKind)
                                                                        { return clang_isPreprocessing(CursorKind); }

unsigned                        _19_isUnexposed                         (enum CXCursorKind CursorKind)
                                                                        { return clang_isUnexposed(CursorKind); }

enum CXLinkageKind              _19_getCursorLinkage                    (CXCursor Cursor)
                                                                        { return clang_getCursorLinkage(Cursor); }

enum CXVisibilityKind           _19_getCursorVisibility                 (CXCursor Cursor)
                                                                        { return clang_getCursorVisibility(Cursor); }

enum CXAvailabilityKind         _19_getCursorAvailability               (CXCursor Cursor)
                                                                        { return clang_getCursorAvailability(Cursor); }

int                             _19_getCursorPlatformAvailability       (CXCursor Cursor, int *always_deprecated, CXString *deprecated_message, int *always_unavailable, CXString *unavailable_message, CXPlatformAvailability *availability, int availability_size)
                                                                        { return clang_getCursorPlatformAvailability(Cursor, always_deprecated, deprecated_message, always_unavailable, unavailable_message, availability, availability_size); }

void                            _19_disposeCXPlatformAvailability       (CXPlatformAvailability *availability)
                                                                        { return clang_disposeCXPlatformAvailability(availability); }

enum CXLanguageKind             _19_getCursorLanguage                   (CXCursor Cursor)
                                                                        { return clang_getCursorLanguage(Cursor); }

enum CXTLSKind                  _19_getCursorTLSKind                    (CXCursor Cursor)
                                                                        { return clang_getCursorTLSKind(Cursor); }

CXTranslationUnit               _19_getTranslationUnit                  (CXCursor Cursor)
                                                                        { return clang_Cursor_getTranslationUnit(Cursor); }

CXCursorSet                     _19_createCXCursorSet                   (void)
                                                                        { return clang_createCXCursorSet(); }

void                            _19_disposeCXCursorSet                  (CXCursorSet cset)
                                                                        { return clang_disposeCXCursorSet(cset); }

unsigned                        _19_contains                            (CXCursorSet cset, CXCursor Cursor)
                                                                        { return clang_CXCursorSet_contains(cset, Cursor); }

unsigned                        _19_insert                              (CXCursorSet cset, CXCursor Cursor)
                                                                        { return clang_CXCursorSet_insert(cset, Cursor); }

CXCursor                        _19_getCursorSemanticParent             (CXCursor Cursor)
                                                                        { return clang_getCursorSemanticParent(Cursor); }

CXCursor                        _19_getCursorLexicalParent              (CXCursor Cursor)
                                                                        { return clang_getCursorLexicalParent(Cursor); }

void                            _19_getOverriddenCursors                (CXCursor Cursor, CXCursor **overridden, unsigned *num_overridden)
                                                                        { return clang_getOverriddenCursors(Cursor, overridden, num_overridden); }

void                            _19_disposeOverriddenCursors            (CXCursor *overridden)
                                                                        { return clang_disposeOverriddenCursors(overridden); }

CXFile                          _19_getIncludedFile                     (CXCursor Cursor)
                                                                        { return clang_getIncludedFile(Cursor); }
