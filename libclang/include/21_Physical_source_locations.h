#pragma once

#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/*

	Used:

	Unused:

		1. CXSourceLocation 	clang_getNullLocation               (void)
		2. unsigned 	        clang_equalLocations                (CXSourceLocation loc1, CXSourceLocation loc2)
		3. CXSourceLocation 	clang_getLocation                   (CXTranslationUnit tu, CXFile file, unsigned line, unsigned column)
		4. CXSourceLocation 	clang_getLocationForOffset          (CXTranslationUnit tu, CXFile file, unsigned offset)
		5. int 	                clang_Location_isInSystemHeader     (CXSourceLocation location)
		6. int 	                clang_Location_isFromMainFile       (CXSourceLocation location)
		7. CXSourceRange 	    clang_getNullRange                  (void)
		8. CXSourceRange 	    clang_getRange                      (CXSourceLocation begin, CXSourceLocation end)
		9. unsigned 	        clang_equalRanges                   (CXSourceRange range1, CXSourceRange range2)
		10. int 	            clang_Range_isNull                  (CXSourceRange range)
		11. void 	            clang_getExpansionLocation          (CXSourceLocation location, CXFile *file, unsigned *line, unsigned *column, unsigned *offset)
		12. void 	            clang_getPresumedLocation           (CXSourceLocation location, CXString *filename, unsigned *line, unsigned *column)
		13. void 	            clang_getInstantiationLocation      (CXSourceLocation location, CXFile *file, unsigned *line, unsigned *column, unsigned *offset)
		14. void 	            clang_getSpellingLocation           (CXSourceLocation location, CXFile *file, unsigned *line, unsigned *column, unsigned *offset)
		15. void 	            clang_getFileLocation               (CXSourceLocation location, CXFile *file, unsigned *line, unsigned *column, unsigned *offset)
		16. CXSourceLocation 	clang_getRangeStart                 (CXSourceRange range)
		17. CXSourceLocation 	clang_getRangeEnd                   (CXSourceRange range)
		18. CXSourceRangeList* 	clang_getSkippedRanges              (CXTranslationUnit tu, CXFile file)
		19. CXSourceRangeList* 	clang_getAllSkippedRanges           (CXTranslationUnit tu)
		20. void                clang_disposeSourceRangeList        (CXSourceRangeList *ranges)
*/

CXSourceLocation        _21_getNullLocation             (void);
unsigned                _21_equalLocations              (CXSourceLocation loc1, CXSourceLocation loc2);
CXSourceLocation        _21_getLocation                 (CXTranslationUnit tu, CXFile file, unsigned line, unsigned column);
CXSourceLocation        _21_getLocationForOffset        (CXTranslationUnit tu, CXFile file, unsigned offset);
int                     _21_isInSystemHeader            (CXSourceLocation location);
int                     _21_isFromMainFile              (CXSourceLocation location);
CXSourceRange           _21_getNullRange                (void);
CXSourceRange           _21_getRange                    (CXSourceLocation begin, CXSourceLocation end);
unsigned                _21_equalRanges                 (CXSourceRange range1, CXSourceRange range2);
int                     _21_isNull                      (CXSourceRange range);
void                    _21_getExpansionLocation        (CXSourceLocation location, CXFile* file, unsigned* line, unsigned* column, unsigned* offset);
void                    _21_getPresumedLocation         (CXSourceLocation location, CXString* filename, unsigned* line, unsigned* column);
void                    _21_getInstantiationLocation    (CXSourceLocation location, CXFile* file, unsigned* line, unsigned* column, unsigned* offset);
void                    _21_getSpellingLocation         (CXSourceLocation location, CXFile* file, unsigned* line, unsigned* column, unsigned* offset);
void                    _21_getFileLocation             (CXSourceLocation location, CXFile* file, unsigned* line, unsigned* column, unsigned* offset);
CXSourceLocation        _21_getRangeStart               (CXSourceRange range);
CXSourceLocation        _21_getRangeEnd                 (CXSourceRange range);
CXSourceRangeList*      _21_getSkippedRanges            (CXTranslationUnit tu, CXFile file);
CXSourceRangeList*      _21_getAllSkippedRanges         (CXTranslationUnit tu);
void                    _21_disposeSourceRangeList      (CXSourceRangeList* ranges);
