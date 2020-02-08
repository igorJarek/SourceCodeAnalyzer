#pragma once

#include <clang-c/Index.h>
#include <string>
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

void dumpAST(string& strData, const CXCursor& cursor);
void printCursor(const CXCursor& cursor, uint32_t curLevel);
