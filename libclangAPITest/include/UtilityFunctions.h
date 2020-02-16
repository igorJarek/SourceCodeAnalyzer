#pragma once

#include <clang-c/Index.h>

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

#include "1_Name_Mangling_API_Functions.h"
#include "2_Diagnostic_Reporting.h"
#include "3_C++_AST_introspection.h"
#include "6_Translation_unit_manipulation.h"
#include "11_String_manipulation_routines.h"

using namespace std;

class ClientData
{
public:

    ClientData(uint32_t level = 0)
    {
        treeLevel = level;
    }

    uint32_t treeLevel{ 0 };
    string astStringData{};
    string astExtStringData{};
};

string tabOffset(uint32_t offset);

bool isFileHeader(const string& extension);
bool isFileSource(const string& extension);

CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData client_data);
bool recursiveFolderSearch(const string& folderPath);

bool processFolder(const string& path);
void processFile(const string& folderPath, const string& fileName);

bool saveToFile(const string& path, const string& data);

void dumpAST(string& strData, const CXCursor& cursor);
void printCursor(string& strData, const CXCursor& cursor, uint32_t curLevel);
