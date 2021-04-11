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

enum e_AppOptions
{
    HTML_ENABLED = (1 << 0),

    CATEGORY_1   = (1 << 1),
    CATEGORY_2   = (1 << 2),
    CATEGORY_3   = (1 << 3),
    CATEGORY_4   = (1 << 4),
    CATEGORY_5   = (1 << 5),
    CATEGORY_6   = (1 << 6),
    CATEGORY_7   = (1 << 7),
    CATEGORY_8   = (1 << 8),
    CATEGORY_9   = (1 << 9),
    CATEGORY_10  = (1 << 10),
    CATEGORY_11  = (1 << 11),
    CATEGORY_12  = (1 << 12),
    CATEGORY_13  = (1 << 13),
    CATEGORY_14  = (1 << 14),
    CATEGORY_15  = (1 << 15),
    CATEGORY_16  = (1 << 16),
    CATEGORY_17  = (1 << 17),
    CATEGORY_18  = (1 << 18),
    CATEGORY_19  = (1 << 19),
    CATEGORY_20  = (1 << 20),
    CATEGORY_21  = (1 << 21)
};

extern uint32_t g_appOptions;

bool        isOptionEnabled         (uint32_t categoryMask);
bool        isOptionNotEnabled      (uint32_t categoryMask);

int64_t     countStringLines        (const string& str);
int64_t     countFileLines          (const string& filePath);
int64_t     countFileLineColumns    (const string& filePath, int64_t line);

void        recursiveFolderSearch   (const string& folderPath);

string      extractFileName         (const string& absoluteFilePath);

void        processBeforeAll        (void);
void        processAfterAll         (void);

void        processFile             (const string& absoluteFilePath);

bool        saveToFile              (const string& path, const stringstream& data);
void        removeFile              (const string& path);
