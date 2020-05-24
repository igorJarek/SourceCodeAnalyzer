#pragma once

#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

CXString    _17_getCursorKindSpelling               (enum CXCursorKind Kind);
void        _17_getDefinitionSpellingAndExtent      (CXCursor C, const char **startBuf, const char **endBuf, unsigned *startLine, unsigned *startColumn, unsigned *endLine, unsigned *endColumn);
void        _17_enableStackTraces                   (void);
void        _17_executeOnThread                     (void(*fn)(void *), void *user_data, unsigned stack_size);