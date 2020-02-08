#pragma once

#include <clang-c/Index.h>

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

#include "LibPath.h"
#include "2_Diagnostic_Reporting.h"
#include "11_String_manipulation_routines.h"

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

CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData client_data);
bool recursiveFolderSearch(const string& folderPath);

bool processFolder(const string& path);
void processFile(const string& folderPath, const string& fileName);

void dumpAST(string& strData, const CXCursor& cursor);
void printCursor(const CXCursor& cursor, uint32_t curLevel);
