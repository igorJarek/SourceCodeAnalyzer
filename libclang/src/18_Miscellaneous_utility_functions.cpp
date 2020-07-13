#include "18_Miscellaneous_utility_functions.h"

void _18_printMiscellaneousUtilityFunctions(string& strData, const CXCursor& cursor, uint32_t curLevel)
{
    ADD_STRING_OUT_TEXT(curLevel + 1, "18. Miscellaneous utility functions : ")

    CXEvalResult         evalResult     = clang_Cursor_Evaluate(cursor);                    // 4.
    if(evalResult)
    {
        CXEvalResultKind evalResultKind = clang_EvalResult_getKind(evalResult);             // 5.
        int32_t          getAsInt       = clang_EvalResult_getAsInt(evalResult);            // 6.
        int64_t          getAsLongLong  = clang_EvalResult_getAsLongLong(evalResult);       // 7.
        uint32_t         isUnsignedInt  = clang_EvalResult_isUnsignedInt(evalResult);       // 8.
        uint64_t         getAsUnsigned  = clang_EvalResult_getAsUnsigned(evalResult);       // 9.
        double           getAsDouble    = clang_EvalResult_getAsDouble(evalResult);         // 10.
        const char*      getAsStr       = clang_EvalResult_getAsStr(evalResult);            // 11.

        clang_EvalResult_dispose(evalResult);                                               // 12.

        ADD_STRING_OUT_NL(curLevel + 2, "clang_EvalResult_getKind : ",       CXEvalResultKind2String(evalResultKind))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_EvalResult_getAsInt : ",      to_string(getAsInt))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_EvalResult_getAsLongLong : ", to_string(getAsLongLong))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_EvalResult_isUnsignedInt : ", to_string(isUnsignedInt))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_EvalResult_getAsUnsigned : ", to_string(getAsUnsigned))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_EvalResult_getAsDouble : ",   to_string(getAsDouble))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_EvalResult_getAsStr : ",      getAsStr)
    }
    else
        ADD_STRING_OUT_TEXT(curLevel + 2, "-NULL-")
}

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
