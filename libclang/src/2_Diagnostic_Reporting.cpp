#include "2_Diagnostic_Reporting.h"

void _2_diagnostic_reporting(CXTranslationUnit& translationUnit, const string& filePath)
{
    string strData;

    uint32_t        errorNumber      = clang_getNumDiagnostics(translationUnit);                                                                                                   // 6.
    CXDiagnosticSet diagnosticSet    = clang_getDiagnosticSetFromTU(translationUnit);                                                                                              // 8.
    uint32_t        errorNumberInSet = clang_getNumDiagnosticsInSet(diagnosticSet);                                                                                                // 1.

    ADD_STRING_OUT_NL(0, "clang_getNumDiagnostics : ", to_string(errorNumber))

    for (uint32_t errorIndex = 0; errorIndex < errorNumber; ++errorIndex)
    {
        ADD_STRING_OUT_NAME(1, "CXDiagnostic [" + to_string(errorIndex + 1) + "] : ")
        CXDiagnostic currentDiagnostic = clang_getDiagnostic(translationUnit, errorIndex);                                                                                         // 7.
        _2_printDiagnostic(strData, currentDiagnostic);
        clang_disposeDiagnostic(currentDiagnostic);                                                                                                                                // 9.
    }

    ADD_STRING_OUT_NEWLINE()
    ADD_STRING_OUT_NL(0, "clang_getNumDiagnosticsInSet : ", to_string(errorNumberInSet))

    for (uint32_t errorIndex = 0; errorIndex < errorNumber; ++errorIndex)
    {
        ADD_STRING_OUT_NAME(1, "CXDiagnostic [" + to_string(errorIndex + 1) + "] : ")
        CXDiagnostic currentDiagnostic = clang_getDiagnosticInSet(diagnosticSet, errorIndex);                                                                                      // 2.
        _2_printDiagnostic(strData, currentDiagnostic);
        clang_disposeDiagnostic(currentDiagnostic);                                                                                                                                // 9.
    }

    if(errorNumberInSet)
        clang_disposeDiagnosticSet(diagnosticSet);                                                                                                                                 // 4.

    if(!saveToFile(filePath + ".diagnostic", strData))
        cout << "Couldn't create file : " << filePath << endl;
}

void _2_printDiagnostic(string& strData, const CXDiagnostic& currentDiagnostic)
{
    uint32_t                defaultDiagnosticDisplayOption = clang_defaultDiagnosticDisplayOptions();                                                                              // 11.

    CXString                formatDiagnostic               = clang_formatDiagnostic(currentDiagnostic, CXDiagnostic_DisplaySourceLocation | CXDiagnostic_DisplayColumn |
                                                                                                       CXDiagnostic_DisplaySourceRanges | CXDiagnostic_DisplayOption |
                                                                                                       CXDiagnostic_DisplayCategoryId | CXDiagnostic_DisplayCategoryName);         // 10.

    CXDiagnosticSeverity    diagnosticSeverity             = clang_getDiagnosticSeverity(currentDiagnostic);                                                                       // 12.
    CXSourceLocation        sourceLocation                 = clang_getDiagnosticLocation(currentDiagnostic);                                                                       // 13.
    CXString                diagnosticSpelling             = clang_getDiagnosticSpelling(currentDiagnostic);                                                                       // 14.

    CXString                disableDiagnosticString;
    CXString                diagnosticOption               = clang_getDiagnosticOption(currentDiagnostic, &disableDiagnosticString);                                               // 15.
    uint32_t                diagnosticCategory             = clang_getDiagnosticCategory(currentDiagnostic);                                                                       // 16.
    CXString                diagnosticCategoryText         = clang_getDiagnosticCategoryText(currentDiagnostic);                                                                   // 18.
    uint32_t                diagnosticNumRanges            = clang_getDiagnosticNumRanges(currentDiagnostic);                                                                      // 19.
    uint32_t                diagnosticNumFixIts            = clang_getDiagnosticNumFixIts(currentDiagnostic);                                                                      // 21.

    ADD_STRING_OUT_NL(2, "clang_defaultDiagnosticDisplayOptions : ", CXDiagnosticDisplayOptions2String(defaultDiagnosticDisplayOption))
    ADD_STRING_OUT_NL(2, "clang_formatDiagnostic : ",                CXString2String(formatDiagnostic))

    ADD_STRING_OUT_NL(2, "clang_getDiagnosticSeverity : ",           CXDiagnosticSeverity2String(diagnosticSeverity))
    ADD_STRING_OUT   (2, "clang_getDiagnosticLocation :\n",          CXSourceLocation2String(sourceLocation, 3))
    ADD_STRING_OUT_NL(2, "clang_getDiagnosticSpelling : ",           CXString2String(diagnosticSpelling))

    ADD_STRING_OUT_NL(2, "clang_getDiagnosticOption Enable : ",      CXString2String(diagnosticOption))
    ADD_STRING_OUT_NL(2, "clang_getDiagnosticOption Disable : ",     CXString2String(disableDiagnosticString))
    ADD_STRING_OUT_NL(2, "clang_getDiagnosticCategory : ",           to_string(diagnosticCategory))
    ADD_STRING_OUT_NL(2, "clang_getDiagnosticCategoryText : ",       CXString2String(diagnosticCategoryText))

    ADD_STRING_OUT_NL(2, "clang_getDiagnosticNumRanges : ",          to_string(diagnosticNumRanges))
    for (uint32_t index{ 0 }; index < diagnosticNumRanges; ++index)
    {
        CXSourceRange       diagnosticRange                 = clang_getDiagnosticRange(currentDiagnostic, index);                                                                   // 20.
        ADD_STRING_OUT_NL(3, "clang_getDiagnosticRange [" + to_string(index) + "] :\n", CXSourceRange2String(diagnosticRange, 3))
    }

    ADD_STRING_OUT_NL(2, "clang_getDiagnosticNumFixIts : ",          to_string(diagnosticNumFixIts))
    for (uint32_t index{ 0 }; index < diagnosticNumFixIts; ++index)
    {
        CXSourceRange       diagnosticFixItSourceRange;
        CXString            diagnosticFixIt                = clang_getDiagnosticFixIt(currentDiagnostic, index, &diagnosticFixItSourceRange);                                      // 22.

        ADD_STRING_OUT_NL(3, "clang_getDiagnosticFixIt [" + to_string(index) + "] [return] : ",            CXString2String(diagnosticFixIt))
        ADD_STRING_OUT   (3, "clang_getDiagnosticFixIt [" + to_string(index) + "] [replacementRange] :\n", CXSourceRange2String(diagnosticFixItSourceRange, 4))
    }
}

unsigned                    _2_getNumDiagnosticsInSet               (CXDiagnosticSet Diags)
                                                                    { return clang_getNumDiagnosticsInSet(Diags); }

CXDiagnostic                _2_getDiagnosticInSet                   (CXDiagnosticSet Diags, unsigned Index)
                                                                    { return clang_getDiagnosticInSet(Diags, Index); }

CXDiagnosticSet             _2_loadDiagnostics                      (const char *file, enum CXLoadDiag_Error *error, CXString *errorString)
                                                                    { return clang_loadDiagnostics(file, error, errorString); }

void                        _2_disposeDiagnosticSet                 (CXDiagnosticSet Diags)
                                                                    { return clang_disposeDiagnosticSet(Diags); }

CXDiagnosticSet             _2_getChildDiagnostics                  (CXDiagnostic D)
                                                                    { return clang_getChildDiagnostics(D); }

unsigned                    _2_getNumDiagnostics                    (CXTranslationUnit Unit)
                                                                    { return clang_getNumDiagnostics(Unit); }

CXDiagnostic                _2_getDiagnostic                        (CXTranslationUnit Unit, unsigned Index)
                                                                    { return clang_getDiagnostic(Unit, Index); }

CXDiagnosticSet             _2_getDiagnosticSetFromTU               (CXTranslationUnit Unit)
                                                                    { return clang_getDiagnosticSetFromTU(Unit); }

void                        _2_disposeDiagnostic                    (CXDiagnostic Diagnostic)
                                                                    { return clang_disposeDiagnostic(Diagnostic); }

CXString                    _2_formatDiagnostic                     (CXDiagnostic Diagnostic, unsigned Options)
                                                                    { return clang_formatDiagnostic(Diagnostic, Options); }

unsigned                    _2_defaultDiagnosticDisplayOptions      (void)
                                                                    { return clang_defaultDiagnosticDisplayOptions(); }

enum CXDiagnosticSeverity   _2_getDiagnosticSeverity                (CXDiagnostic Diagnostic)
                                                                    { return clang_getDiagnosticSeverity(Diagnostic); }

CXSourceLocation            _2_getDiagnosticLocation                (CXDiagnostic Diagnostic)
                                                                    { return clang_getDiagnosticLocation( Diagnostic); }

CXString                    _2_getDiagnosticSpelling                (CXDiagnostic Diagnostic)
                                                                    { return clang_getDiagnosticSpelling( Diagnostic); }

CXString                    _2_getDiagnosticOption                  (CXDiagnostic Diagnostic, CXString *Disable)
                                                                    { return clang_getDiagnosticOption( Diagnostic, Disable); }

unsigned                    _2_getDiagnosticCategory                (CXDiagnostic Diagnostic)
                                                                    { return clang_getDiagnosticCategory(Diagnostic); }

CXString                    _2_getDiagnosticCategoryText            (CXDiagnostic Diagnostic)
                                                                    { return clang_getDiagnosticCategoryText(Diagnostic); }

unsigned                    _2_getDiagnosticNumRanges               (CXDiagnostic Diagnostic)
                                                                    { return clang_getDiagnosticNumRanges(Diagnostic); }

CXSourceRange               _2_getDiagnosticRange                   (CXDiagnostic Diagnostic, unsigned Range)
                                                                    { return clang_getDiagnosticRange(Diagnostic, Range); }

unsigned                    _2_getDiagnosticNumFixIts               (CXDiagnostic Diagnostic)
                                                                    { return clang_getDiagnosticNumFixIts(Diagnostic); }

CXString                    _2_getDiagnosticFixIt                   (CXDiagnostic Diagnostic, unsigned FixIt, CXSourceRange *ReplacementRange)
                                                                    { return clang_getDiagnosticFixIt(Diagnostic, FixIt, ReplacementRange); }
