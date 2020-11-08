#include "2_Diagnostic_Reporting.h"
#include <html/Html.h>

void _2_diagnostic_reporting(CXTranslationUnit& translationUnit, const string& filePath)
{
    OutputTree outputTree;

    uint32_t        errorNumber      = clang_getNumDiagnostics(translationUnit);                                                                                                   // 6.
    CXDiagnosticSet diagnosticSet    = clang_getDiagnosticSetFromTU(translationUnit);                                                                                              // 8.
    uint32_t        errorNumberInSet = clang_getNumDiagnosticsInSet(diagnosticSet);                                                                                                // 1.

    outputTree.addString(0, "clang_getNumDiagnostics : ", errorNumber);

    for (uint32_t errorIndex = 0; errorIndex < errorNumber; ++errorIndex)
    {
        outputTree.addString(1, "CXDiagnostic [" + to_string(errorIndex + 1) + "] : ");
        CXDiagnostic currentDiagnostic = clang_getDiagnostic(translationUnit, errorIndex);                                                                                         // 7.
        _2_printDiagnostic(outputTree, currentDiagnostic);
        clang_disposeDiagnostic(currentDiagnostic);                                                                                                                                // 9.
    }

    outputTree.addNewLine(0);

    outputTree.addString(0, "clang_getNumDiagnosticsInSet : ", errorNumberInSet);

    for (uint32_t errorIndex = 0; errorIndex < errorNumber; ++errorIndex)
    {
        outputTree.addString(1, "CXDiagnostic [" + to_string(errorIndex + 1) + "] : ");
        CXDiagnostic currentDiagnostic = clang_getDiagnosticInSet(diagnosticSet, errorIndex);                                                                                      // 2.
        _2_printDiagnostic(outputTree, currentDiagnostic);
        clang_disposeDiagnostic(currentDiagnostic);                                                                                                                                // 9.
    }

    if(errorNumberInSet)
        clang_disposeDiagnosticSet(diagnosticSet);                                                                                                                                 // 4.

    string saveFilePath{ filePath + DIAGN_FILE_EXT };
    if(!outputTree.saveToFile(saveFilePath))
        cout << "Couldn't save file : " << saveFilePath << endl;

    HTMLBuilder htmlBuilder;
    string tableID{ "TBL" };

    htmlBuilder.setIndexTitle(saveFilePath + ".html");
    htmlBuilder.setFileNameHeader(saveFilePath);
    htmlBuilder.setFilePathHeader(saveFilePath + ".html");

    htmlBuilder.addTable("Diagnostic", tableID, outputTree);

    if(!htmlBuilder.saveFile(saveFilePath + ".html"))
        cout << "Couldn't save HTML file : " << saveFilePath + ".html" << endl;
}

void _2_printDiagnostic(OutputTree& outputTree, const CXDiagnostic& currentDiagnostic)
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

    outputTree.addString(2, "clang_defaultDiagnosticDisplayOptions : ", defaultDiagnosticDisplayOption);
    outputTree.addString(2, "clang_formatDiagnostic : ",                formatDiagnostic);

    outputTree.addString(2, "clang_getDiagnosticSeverity : ",           diagnosticSeverity);
    outputTree.addCXSourceLocation(2, "clang_getDiagnosticLocation : ", sourceLocation);
    outputTree.addString(2, "clang_getDiagnosticSpelling : ",           diagnosticSpelling);

    outputTree.addString(2, "clang_getDiagnosticOption Enable : ",      diagnosticOption);
    outputTree.addString(2, "clang_getDiagnosticOption Disable : ",     disableDiagnosticString);
    outputTree.addString(2, "clang_getDiagnosticCategory : ",           diagnosticCategory);
    outputTree.addString(2, "clang_getDiagnosticCategoryText : ",       diagnosticCategoryText);

    outputTree.addString(2, "clang_getDiagnosticNumRanges : ",          diagnosticNumRanges);
    for (uint32_t index{ 0 }; index < diagnosticNumRanges; ++index)
    {
        CXSourceRange       diagnosticRange                 = clang_getDiagnosticRange(currentDiagnostic, index);                                                                   // 20.
        outputTree.addCXSourceRange(3, "clang_getDiagnosticRange [" + to_string(index) + "] : ", diagnosticRange);
    }

    outputTree.addString(2, "clang_getDiagnosticNumFixIts : ", diagnosticNumFixIts);
    for (uint32_t index{ 0 }; index < diagnosticNumFixIts; ++index)
    {
        CXSourceRange       diagnosticFixItSourceRange;
        CXString            diagnosticFixIt                = clang_getDiagnosticFixIt(currentDiagnostic, index, &diagnosticFixItSourceRange);                                      // 22.

        outputTree.addString(3, "clang_getDiagnosticFixIt [" + to_string(index) + "] [return] : ",            diagnosticFixIt);
        outputTree.addCXSourceRange(3, "clang_getDiagnosticFixIt [" + to_string(index) + "] [replacementRange] :\n", diagnosticFixItSourceRange);
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
