#include "21_Physical_source_locations.h"

CXSourceLocation	_21_getNullLocation				(void)
													{ return clang_getNullLocation(); }

unsigned			_21_equalLocations				(CXSourceLocation loc1, CXSourceLocation loc2)
													{ return clang_equalLocations(loc1, loc2); }

CXSourceLocation	_21_getLocation					(CXTranslationUnit tu, CXFile file, unsigned line, unsigned column)
													{ return clang_getLocation(tu, file, line, column); }

CXSourceLocation	_21_getLocationForOffset		(CXTranslationUnit tu, CXFile file, unsigned offset)
													{ return clang_getLocationForOffset(tu, file, offset); }

int					_21_isInSystemHeader			(CXSourceLocation location)
													{ return clang_Location_isInSystemHeader(location); }

int					_21_isFromMainFile				(CXSourceLocation location)
													{ return clang_Location_isFromMainFile(location); }

CXSourceRange		_21_getNullRange				(void)
													{ return clang_getNullRange(); }

CXSourceRange		_21_getRange					(CXSourceLocation begin, CXSourceLocation end)
													{ return clang_getRange(begin, end); }

unsigned			_21_equalRanges					(CXSourceRange range1, CXSourceRange range2)
													{ return clang_equalRanges(range1, range2); }

int					_21_isNull						(CXSourceRange range)
													{ return clang_Range_isNull(range); }

void				_21_getExpansionLocation		(CXSourceLocation location, CXFile* file, unsigned* line, unsigned* column, unsigned* offset) 
													{ return clang_getExpansionLocation(location, file, line, column, offset); }

void				_21_getPresumedLocation			(CXSourceLocation location, CXString* filename, unsigned* line, unsigned* column) 
													{ return clang_getPresumedLocation(location, filename, line, column); }

void				_21_getInstantiationLocation	(CXSourceLocation location, CXFile* file, unsigned* line, unsigned* column, unsigned* offset)
													{ return clang_getInstantiationLocation(location, file, line, column, offset); }

void				_21_getSpellingLocation			(CXSourceLocation location, CXFile* file, unsigned* line, unsigned* column, unsigned* offset)
													{ return clang_getSpellingLocation(location, file, line, column, offset); }

void				_21_getFileLocation				(CXSourceLocation location, CXFile* file, unsigned* line, unsigned* column, unsigned* offset)
													{ return clang_getFileLocation(location, file, line, column, offset); }

CXSourceLocation	_21_getRangeStart				(CXSourceRange range)
													{ return clang_getRangeStart(range); }

CXSourceLocation	_21_getRangeEnd					(CXSourceRange range)
													{ return clang_getRangeEnd(range); }

CXSourceRangeList*	_21_getSkippedRanges			(CXTranslationUnit tu, CXFile file)
													{ return clang_getSkippedRanges(tu, file); }

CXSourceRangeList*	_21_getAllSkippedRanges			(CXTranslationUnit tu)
													{ return clang_getAllSkippedRanges(tu); }

void				_21_disposeSourceRangeList		(CXSourceRangeList* ranges)
													{ return clang_disposeSourceRangeList(ranges); }
