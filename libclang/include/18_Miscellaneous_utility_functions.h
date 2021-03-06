#pragma once

#include <clang-c/Index.h>
#include <UtilityFunctions.h>
#include <fstream>
#include <string>
#include <iostream>

using std::to_string;

/*

    Used:

        1. CXString                     clang_getClangVersion                                   (void)
        2. void                         clang_toggleCrashRecovery                               (unsigned isEnabled)

        4. CXEvalResult                 clang_Cursor_Evaluate                                   (CXCursor C)
        5. CXEvalResultKind             clang_EvalResult_getKind                                (CXEvalResult E)
        6. int                          clang_EvalResult_getAsInt                               (CXEvalResult E)
        7. long long                    clang_EvalResult_getAsLongLong                          (CXEvalResult E)
        8. unsigned                     clang_EvalResult_isUnsignedInt                          (CXEvalResult E)
        9. unsigned long long           clang_EvalResult_getAsUnsigned                          (CXEvalResult E)
        10. double                      clang_EvalResult_getAsDouble                            (CXEvalResult E)
        11. const char *                clang_EvalResult_getAsStr                               (CXEvalResult E)
        12. void                        clang_EvalResult_dispose                                (CXEvalResult E)

    Unused:

        3. void                         clang_getInclusions                                     (CXTranslationUnit tu, CXInclusionVisitor visitor, CXClientData client_data)

*/

// Print Function

void _18_printMiscellaneousUtilityFunctions(OutputTree& astExtOutputTree, const CXCursor& cursor, uint32_t curLevel);

// Clang Functions

CXString                _18_getClangVersion             (void);                                                                             // 1.
void                    _18_toggleCrashRecovery         (unsigned isEnabled);                                                               // 2.
void                    _18_getInclusions               (CXTranslationUnit tu, CXInclusionVisitor visitor, CXClientData client_data);       // 3.
CXEvalResult            _18_evaluate                    (CXCursor C);                                                                       // 4.
CXEvalResultKind        _18_getKind                     (CXEvalResult E);                                                                   // 5.
int                     _18_getAsInt                    (CXEvalResult E);                                                                   // 6.
long long               _18_getAsLongLong               (CXEvalResult E);                                                                   // 7.
unsigned                _18_isUnsignedInt               (CXEvalResult E);                                                                   // 8.
unsigned long long      _18_getAsUnsigned               (CXEvalResult E);                                                                   // 9.
double                  _18_getAsDouble                 (CXEvalResult E);                                                                   // 10.
const char *            _18_getAsStr                    (CXEvalResult E);                                                                   // 11.
void                    _18_dispose                     (CXEvalResult E);                                                                   // 12.
