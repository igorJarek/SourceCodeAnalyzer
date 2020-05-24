#pragma once

#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

CXCursor                        _19_getNullCursor                       (void);
CXCursor                        _19_getTranslationUnitCursor            (CXTranslationUnit TranslationUnit);
unsigned                        _19_equalCursors                        (CXCursor CursorA, CXCursor CursorB);
int                             _19_isNull                              (CXCursor Cursor);
unsigned                        _19_hashCursor                          (CXCursor Cursor);
enum CXCursorKind               _19_getCursorKind                       (CXCursor Cursor);
unsigned                        _19_isDeclaration                       (enum CXCursorKind CursorKind);
unsigned                        _19_isInvalidDeclaration                (CXCursor Cursor);
unsigned                        _19_isReference                         (enum CXCursorKind CursorKind);
unsigned                        _19_isExpression                        (enum CXCursorKind CursorKind);
unsigned                        _19_isStatement                         (enum CXCursorKind CursorKind);
unsigned                        _19_isAttribute                         (enum CXCursorKind CursorKind);
unsigned                        _19_hasAttrs                            (CXCursor Cursor);
unsigned                        _19_isInvalid                           (enum CXCursorKind CursorKind);
unsigned                        _19_isTranslationUnit                   (enum CXCursorKind CursorKind);
unsigned                        _19_isPreprocessing                     (enum CXCursorKind CursorKind);
unsigned                        _19_isUnexposed                         (enum CXCursorKind CursorKind);
enum CXLinkageKind              _19_getCursorLinkage                    (CXCursor Cursor);
enum CXVisibilityKind           _19_getCursorVisibility                 (CXCursor Cursor);
enum CXAvailabilityKind         _19_getCursorAvailability               (CXCursor Cursor);
int                             _19_getCursorPlatformAvailability       (CXCursor Cursor, int *always_deprecated, CXString *deprecated_message, int *always_unavailable, CXString *unavailable_message, CXPlatformAvailability *availability, int availability_size);
void                            _19_disposeCXPlatformAvailability       (CXPlatformAvailability *availability);
enum CXLanguageKind             _19_getCursorLanguage                   (CXCursor Cursor);
enum CXTLSKind                  _19_getCursorTLSKind                    (CXCursor Cursor);
CXTranslationUnit               _19_getTranslationUnit                  (CXCursor Cursor);
CXCursorSet                     _19_createCXCursorSet                   (void);
void                            _19_disposeCXCursorSet                  (CXCursorSet cset);
unsigned                        _19_contains                            (CXCursorSet cset, CXCursor Cursor);
unsigned                        _19_insert                              (CXCursorSet cset, CXCursor Cursor);
CXCursor                        _19_getCursorSemanticParent             (CXCursor Cursor);
CXCursor                        _19_getCursorLexicalParent              (CXCursor Cursor);
void                            _19_getOverriddenCursors                (CXCursor Cursor, CXCursor **overridden, unsigned *num_overridden);
void                            _19_disposeOverriddenCursors            (CXCursor *overridden);
CXFile                          _19_getIncludedFile                     (CXCursor Cursor);
