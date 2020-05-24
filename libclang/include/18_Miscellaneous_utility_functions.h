#pragma once

#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

CXString                _18_getClangVersion             (void);
void                    _18_toggleCrashRecovery         (unsigned isEnabled);
void                    _18_getInclusions               (CXTranslationUnit tu, CXInclusionVisitor visitor, CXClientData client_data);
CXEvalResult            _18_evaluate                    (CXCursor C);
CXEvalResultKind        _18_getKind                     (CXEvalResult E);
int                     _18_getAsInt                    (CXEvalResult E);
long long               _18_getAsLongLong               (CXEvalResult E);
unsigned                _18_isUnsignedInt               (CXEvalResult E);
unsigned long long      _18_getAsUnsigned               (CXEvalResult E);
double                  _18_getAsDouble                 (CXEvalResult E);
const char *            _18_getAsStr                    (CXEvalResult E);
void                    _18_dispose                     (CXEvalResult E);