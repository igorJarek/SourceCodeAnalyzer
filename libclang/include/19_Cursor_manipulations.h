#pragma once

#include <clang-c/Index.h>
#include <UtilityFunctions.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/*

	Used:

		5. unsigned							clang_hashCursor										(CXCursor)
		6. enum CXCursorKind				clang_getCursorKind										(CXCursor)
		7. unsigned							clang_isDeclaration										(enum CXCursorKind)
		8. unsigned							clang_isInvalidDeclaration								(CXCursor)
		9. unsigned							clang_isReference										(enum CXCursorKind)
		10. unsigned						clang_isExpression										(enum CXCursorKind)
		11. unsigned						clang_isStatement										(enum CXCursorKind)
		12. unsigned						clang_isAttribute										(enum CXCursorKind)
		13. unsigned						clang_Cursor_hasAttrs									(CXCursor C)
		14. unsigned						clang_isInvalid											(enum CXCursorKind)
		15. unsigned						clang_isTranslationUnit									(enum CXCursorKind)
		16. unsigned						clang_isPreprocessing									(enum CXCursorKind)
		17. unsigned						clang_isUnexposed										(enum CXCursorKind)
		18. enum CXLinkageKind				clang_getCursorLinkage									(CXCursor cursor)
		19. enum CXVisibilityKind			clang_getCursorVisibility								(CXCursor cursor)
		20. enum CXAvailabilityKind			clang_getCursorAvailability								(CXCursor cursor)
		21. int								clang_getCursorPlatformAvailability						(CXCursor cursor, int *always_deprecated, CXString *deprecated_message, int *always_unavailable, 
																									CXString *unavailable_message, CXPlatformAvailability *availability, int availability_size)
		22. void							clang_disposeCXPlatformAvailability						(CXPlatformAvailability *availability)
		23. enum CXLanguageKind				clang_getCursorLanguage									(CXCursor cursor)
		24. enum CXTLSKind					clang_getCursorTLSKind									(CXCursor cursor)

		30. CXCursor						clang_getCursorSemanticParent							(CXCursor cursor)
		31. CXCursor						clang_getCursorLexicalParent							(CXCursor cursor)
		32. void							clang_getOverriddenCursors								(CXCursor cursor, CXCursor **overridden, unsigned *num_overridden)
		33. void							clang_disposeOverriddenCursors							(CXCursor *overridden)
		34. CXFile							clang_getIncludedFile									(CXCursor cursor)

	Unused:

		1. CXCursor							clang_getNullCursor										(void)
		2. CXCursor							clang_getTranslationUnitCursor							(CXTranslationUnit)
		3. unsigned							clang_equalCursors										(CXCursor, CXCursor)
		4. int								clang_Cursor_isNull										(CXCursor cursor)

		25. CXTranslationUnit				clang_Cursor_getTranslationUnit							(CXCursor)
		26. CXCursorSet						clang_createCXCursorSet									(void)
		27. void							clang_disposeCXCursorSet								(CXCursorSet cset)
		28. unsigned						clang_CXCursorSet_contains								(CXCursorSet cset, CXCursor cursor)
		29. unsigned						clang_CXCursorSet_insert								(CXCursorSet cset, CXCursor cursor)

*/

void _19_printCursorManipulations(const CXTranslationUnit& translationUnit, string& strData, const CXCursor& cursor, uint32_t curLevel);

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
