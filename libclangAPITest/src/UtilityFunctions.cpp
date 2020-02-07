#include "UtilityFunctions.h"

bool isFileHeader(const string& extension)
{
    if (extension.compare("h") == 0 || extension.compare("hpp") == 0)
        return true;
    else
        return false;
}

bool isFileSource(const string& extension)
{
    if (extension.compare("c") == 0 || extension.compare("cpp") == 0)
        return true;
    else
        return false;
}

string tabOffset(uint32_t offset)
{
    string str;
    for (uint32_t index{ 0 }; index < offset; ++index)
        str += '\t';

    return str;
}

string CXDiagnosticSeverity2String(const CXDiagnosticSeverity diagnosticSeverity)
{
    string str;
    switch (diagnosticSeverity)
    {
    case CXDiagnostic_Ignored:
        str += "CXDiagnostic_Ignored";
        break;

    case CXDiagnostic_Note:
        str += "CXDiagnostic_Note";
        break;

    case CXDiagnostic_Warning:
        str += "CXDiagnostic_Warning";
        break;

    case CXDiagnostic_Error:
        str += "CXDiagnostic_Error";
        break;

    case CXDiagnostic_Fatal:
        str += "CXDiagnostic_Fatal";
        break;
    }

    return str;
}

string CXDiagnosticDisplayOptions2String(uint32_t options)
{
    string str;

    if (options & CXDiagnostic_DisplaySourceLocation)
        str += "CXDiagnostic_DisplaySourceLocation | ";
    
    if (options & CXDiagnostic_DisplayColumn)
        str += "CXDiagnostic_DisplayColumn | ";

    if (options & CXDiagnostic_DisplaySourceRanges)
        str += "CXDiagnostic_DisplaySourceRanges | ";

    if (options & CXDiagnostic_DisplayOption)
        str += "CXDiagnostic_DisplayOption | ";

    if (options & CXDiagnostic_DisplayCategoryId)
        str += "CXDiagnostic_DisplayCategoryId | ";

    if (options & CXDiagnostic_DisplayCategoryName)
        str += "CXDiagnostic_DisplayCategoryName | ";

    str.erase(str.find_last_of("|"));

    return str;
}

string CXSourceLocation2String(const CXSourceLocation sourceLocation, uint32_t offset)
{
    string str;
    CXFile file1, file2; 
    uint32_t line1, line2;
    uint32_t column1, column2;
    uint32_t offset1, offset2;

    clang_getExpansionLocation(sourceLocation, &file1, &line1, &column1, &offset1);
    clang_getSpellingLocation(sourceLocation, &file2, &line2, &column2, &offset2);

    str += tabOffset(offset) +  "ExpansionLocation : \n";
    str += tabOffset(offset + 1) + "File : " + _11_CXString2String(clang_getFileName(file1)) + '\n';
    str += tabOffset(offset + 1) + "Line : " + to_string(line1) + '\n';
    str += tabOffset(offset + 1) + "Column : " + to_string(column1) + '\n';
    str += tabOffset(offset + 1) + "Offset : " + to_string(offset1) + "\n\n";

    str += tabOffset(offset) + "SpellingLocation : \n";
    str += tabOffset(offset + 1) + "File : " + _11_CXString2String(clang_getFileName(file2)) + '\n';
    str += tabOffset(offset + 1) + "Line : " + to_string(line2) + '\n';
    str += tabOffset(offset + 1) + "Column : " + to_string(column2) + '\n';
    str += tabOffset(offset + 1) + "Offset : " + to_string(offset2) + "\n\n";

    return str;
}

string CXSourceRange2String(const CXSourceRange sourceRange, uint32_t offset)
{
    string str;

    CXSourceLocation rangeStart = clang_getRangeStart(sourceRange);
    CXSourceLocation rangeEnd = clang_getRangeEnd(sourceRange);

    str += tabOffset(offset) + "RangeStart : \n";
    str += CXSourceLocation2String(rangeStart, offset + 1);
    str += tabOffset(offset) + "RangeEnd : \n";;
    str += CXSourceLocation2String(rangeEnd, offset + 1);

    return str;
}