#include "19_Cursor_manipulations.h"

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
