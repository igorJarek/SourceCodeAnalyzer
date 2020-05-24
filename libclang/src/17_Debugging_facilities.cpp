#include "17_Debugging_facilities.h"

CXString    _17_getCursorKindSpelling               (enum CXCursorKind Kind)
                                                    { return clang_getCursorKindSpelling(Kind); }

void        _17_getDefinitionSpellingAndExtent      (CXCursor C, const char **startBuf, const char **endBuf, unsigned *startLine, unsigned *startColumn, unsigned *endLine, unsigned *endColumn)
                                                    { return clang_getDefinitionSpellingAndExtent(C, startBuf, endBuf, startLine, startColumn, endLine, endColumn); }

void        _17_enableStackTraces                   (void)
                                                    { return clang_enableStackTraces(); }

void        _17_executeOnThread                     (void(*fn)(void *), void *user_data, unsigned stack_size)
                                                    { return clang_executeOnThread(fn, user_data, stack_size); }
