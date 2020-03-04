#include "2_Diagnostic_Reporting.h"

void _2_diagnostic_reporting(CXTranslationUnit& translationUnit, const string& filePath)
{
    fstream stream;
    stream.open(filePath + ".diagnostic", std::fstream::out | std::fstream::trunc);
    if (stream.is_open())
    {
        uint32_t errorNumber = clang_getNumDiagnostics(translationUnit);                                                                                    // 6.
        
        stream << "clang_getNumDiagnostics : " << errorNumber << endl;
        stream << "-------------------------------------------" << endl;

        for (uint32_t index = 0; index < errorNumber; ++index)
        {
            stream << "Current Diagnostic : " << index << endl;
            CXDiagnostic currentDiagnostic = clang_getDiagnostic(translationUnit, index);                                                                   // 7.
            _2_printDiagnostic(stream, currentDiagnostic);
            clang_disposeDiagnostic(currentDiagnostic);                                                                                                     // 9.
        }


        CXDiagnosticSet	diagnosticSet = clang_getDiagnosticSetFromTU(translationUnit);                                                                      // 8.
        uint32_t errorNumberInSet = clang_getNumDiagnosticsInSet(diagnosticSet);                                                                            // 1.

        stream << "clang_getNumDiagnosticsInSet : " << errorNumberInSet << endl;
        stream << "-------------------------------------------" << endl;

        for (uint32_t index = 0; index < errorNumber; ++index)
        {
            stream << "Current Diagnostic : " << index << endl;
            CXDiagnostic currentDiagnostic = clang_getDiagnosticInSet(diagnosticSet, index);                                                                // 2.
            _2_printDiagnostic(stream, currentDiagnostic);
            clang_disposeDiagnostic(currentDiagnostic);                                                                                                     // 9.
        }

        if(errorNumberInSet)
            clang_disposeDiagnosticSet(diagnosticSet);                                                                                                      // 4.

        stream.close();
    }
    else
        cout << "Couldn't create file : " << filePath << endl;
}

void _2_printDiagnostic(fstream& stream, const CXDiagnostic& currentDiagnostic)
{
    uint32_t defaultDiagnosticDisplayOption = clang_defaultDiagnosticDisplayOptions();                                                                      // 11.

    CXString formatDiagnostic = clang_formatDiagnostic(currentDiagnostic,   CXDiagnostic_DisplaySourceLocation | CXDiagnostic_DisplayColumn |
                                                                            CXDiagnostic_DisplaySourceRanges | CXDiagnostic_DisplayOption |
                                                                            CXDiagnostic_DisplayCategoryId | CXDiagnostic_DisplayCategoryName);             // 10.

    CXDiagnosticSeverity    diagnosticSeverity      = clang_getDiagnosticSeverity(currentDiagnostic);                                                       // 12.
    CXSourceLocation        sourceLocation          = clang_getDiagnosticLocation(currentDiagnostic);                                                       // 13.
    CXString                diagnosticSpelling      = clang_getDiagnosticSpelling(currentDiagnostic);                                                       // 14.

    CXString                disableDiagnosticString;
    CXString                diagnosticOption        = clang_getDiagnosticOption(currentDiagnostic, &disableDiagnosticString);                               // 15.
    uint32_t                diagnosticCategory      = clang_getDiagnosticCategory(currentDiagnostic);                                                       // 16.
    CXString                diagnosticCategoryText  = clang_getDiagnosticCategoryText(currentDiagnostic);                                                   // 18.
    uint32_t                diagnosticNumRanges     = clang_getDiagnosticNumRanges(currentDiagnostic);                                                      // 19.
    uint32_t                diagnosticNumFixIts     = clang_getDiagnosticNumFixIts(currentDiagnostic);                                                      // 21.

    stream << tabOffset(1) + "clang_defaultDiagnosticDisplayOptions : " << CXDiagnosticDisplayOptions2String(defaultDiagnosticDisplayOption) << endl;
    stream << tabOffset(1) + "clang_formatDiagnostic : "                << formatDiagnostic << endl;

    stream << tabOffset(1) + "clang_getDiagnosticSeverity : "           << CXDiagnosticSeverity2String(diagnosticSeverity) << endl;
    stream << tabOffset(1) + "clang_getDiagnosticLocation : "           << endl << CXSourceLocation2String(sourceLocation, 2);
    stream << tabOffset(1) + "clang_getDiagnosticSpelling : "           << diagnosticSpelling << endl;

    stream << tabOffset(1) + "clang_getDiagnosticOption Enable : "      << diagnosticOption << endl;
    stream << tabOffset(1) + "clang_getDiagnosticOption Disable : "     << disableDiagnosticString << endl;

    stream << tabOffset(1) + "clang_getDiagnosticCategory : "           << diagnosticCategory << endl;
    stream << tabOffset(1) + "clang_getDiagnosticCategoryText : "       << diagnosticCategoryText << endl;

    stream << tabOffset(1) + "clang_getDiagnosticNumRanges : "          << diagnosticNumRanges << endl;
    for (uint32_t index{ 0 }; index < diagnosticNumRanges; ++index)
    {
        CXSourceRange diagnosticRange = clang_getDiagnosticRange(currentDiagnostic, index);                                                                 // 20.
        stream << tabOffset(2) + "clang_getDiagnosticRange " << index << " : " << endl << CXSourceRange2String(diagnosticRange, 3);
    }

    stream << tabOffset(1) + "clang_getDiagnosticNumFixIts : " << diagnosticNumFixIts << endl;
    for (uint32_t index{ 0 }; index < diagnosticNumFixIts; ++index)
    {
        CXSourceRange diagnosticFixItSourceRange;
        CXString diagnosticFixIt = clang_getDiagnosticFixIt(currentDiagnostic, index, &diagnosticFixItSourceRange);                                         // 22.
        stream << tabOffset(2) + "clang_getDiagnosticFixIt "    << index << " : " << endl;
        stream << tabOffset(3) + "CXString : "                  << diagnosticFixIt << endl;
        stream << tabOffset(3) + "Range : "                     << endl << CXSourceRange2String(diagnosticFixItSourceRange, 4);
    }
}