#pragma once

#include <clang-c/Index.h>
#include "11_String_manipulation_routines.h"
#include <string>
#include <ostream>

using namespace std;

class Arguments
{
public:

    Arguments(uint32_t level = 0)
    {
        treeLevel = level;
    }

    ~Arguments()
    {

    }

    uint32_t treeLevel{ 0 };
    string strData{};
};

string tabOffset(uint32_t offset);

bool isFileHeader(const string& extension);
bool isFileSource(const string& extension);

void dumpAST(string& strData, const CXCursor& cursor);

string CXDiagnosticSeverity2String(const CXDiagnosticSeverity diagnosticSeverity);
string CXDiagnosticDisplayOptions2String(uint32_t options);

string CXSourceLocation2String(const CXSourceLocation sourceLocation, uint32_t offset);
string CXSourceRange2String(const CXSourceRange sourceRange, uint32_t offset);
