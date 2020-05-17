#pragma once

#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

CXCursor            _10_getCursor               (CXTranslationUnit TU, CXSourceLocation SourceLocation);
CXSourceLocation    _10_getCursorLocation       (CXCursor C);
CXSourceRange       _10_getCursorExtent         (CXCursor C);
