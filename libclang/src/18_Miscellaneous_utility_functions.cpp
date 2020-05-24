#include "18_Miscellaneous_utility_functions.h"

CXString                _18_getClangVersion             (void)
                                                        { return clang_getClangVersion(); }

void                    _18_toggleCrashRecovery         (unsigned isEnabled)
                                                        { return clang_toggleCrashRecovery(isEnabled); }

void                    _18_getInclusions               (CXTranslationUnit tu, CXInclusionVisitor visitor, CXClientData client_data)
                                                        { return clang_getInclusions(tu, visitor, client_data); }

CXEvalResult            _18_evaluate                    (CXCursor C)
                                                        { return clang_Cursor_Evaluate(C); }

CXEvalResultKind        _18_getKind                     (CXEvalResult E)
                                                        { return clang_EvalResult_getKind(E); }

int                     _18_getAsInt                    (CXEvalResult E)
                                                        { return clang_EvalResult_getAsInt(E); }

long long               _18_getAsLongLong               (CXEvalResult E)
                                                        { return clang_EvalResult_getAsLongLong(E); }

unsigned                _18_isUnsignedInt               (CXEvalResult E)
                                                        { return clang_EvalResult_isUnsignedInt(E); }

unsigned long long      _18_getAsUnsigned               (CXEvalResult E)
                                                        { return clang_EvalResult_getAsUnsigned(E); }

double                  _18_getAsDouble                 (CXEvalResult E)
                                                        { return clang_EvalResult_getAsDouble(E); }

const char *            _18_getAsStr                    (CXEvalResult E)
                                                        { return clang_EvalResult_getAsStr(E); }

void                    _18_dispose                     (CXEvalResult E)
                                                        { return clang_EvalResult_dispose(E); }
