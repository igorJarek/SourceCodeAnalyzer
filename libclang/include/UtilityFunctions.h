#pragma once

#include <clang-c/Index.h>

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>

#include "ClangUtilityFunctions.h"
#include "2_Diagnostic_Reporting.h"
#include "5_Token_extraction_and_manipulation.h"
#include "6_Translation_unit_manipulation.h"
#include "8_File_manipulation_routines.h"
#include "11_String_manipulation_routines.h"

using std::cout;
using std::endl;
using std::stringstream;

int64_t     countStringLines        (const string& str);
int64_t     countFileLines          (const string& filePath);
int64_t     countFileLineColumns    (const string& filePath, int64_t line);

void        recursiveFolderSearch   (const string& folderPath);

string      extractFileName         (const string& absoluteFilePath);

void        processBeforeAll        (void);
void        processAfterAll         (void);

void        processFile             (const string& absoluteFilePath);

bool        saveToFile              (const string& path, const stringstream& data);
