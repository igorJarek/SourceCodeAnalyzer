#include "10_Mapping_between_cursors_and_source_code.h"

CXCursor            _10_getCursor               (CXTranslationUnit TU, CXSourceLocation SourceLocation)
                                                { return clang_getCursor(TU, SourceLocation); }

CXSourceLocation    _10_getCursorLocation       (CXCursor C)
                                                { return clang_getCursorLocation(C); }

CXSourceRange       _10_getCursorExtent         (CXCursor C)
                                                { return clang_getCursorExtent(C); }
