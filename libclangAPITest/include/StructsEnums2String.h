#pragma once

#include <clang-c/Index.h>
#include "11_String_manipulation_routines.h"
#include "UtilityFunctions.h"
#include <string>
#include <ostream>

using namespace std;

string CXDiagnosticSeverity2String(const CXDiagnosticSeverity diagnosticSeverity);
string CXDiagnosticDisplayOptions2String(uint32_t options);

string CXSourceLocation2String(const CXSourceLocation sourceLocation, uint32_t offset);
string CXSourceRange2String(const CXSourceRange sourceRange, uint32_t offset);

string CXCursorKind2String(enum CXCursorKind cursorKind);