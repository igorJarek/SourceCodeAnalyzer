#pragma once

#include <clang-c/Index.h>

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

#include "ClangUtilityFunctions.h"
#include "2_Diagnostic_Reporting.h"
#include "5_Token_extraction_and_manipulation.h"
#include "6_Translation_unit_manipulation.h"
#include "8_File_manipulation_routines.h"
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

int64_t countStringLines(const string& str);
int64_t countFileLines(const string& filePath);
int64_t countFileLineColumns(const string& filePath, int64_t line);

bool isFileHeader(const string& extension);
bool isFileSource(const string& extension);

CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData client_data);
bool recursiveFolderSearch(const string& folderPath);

bool processFolder(const string& path);
void processFile(const string& folderPath, const string& fileName);

bool saveToFile(const string& path, const string& data);
bool appendToFile(const string& path, const string& data);

bool saveFile(const string& path, const string& data, ios_base::openmode mode);
