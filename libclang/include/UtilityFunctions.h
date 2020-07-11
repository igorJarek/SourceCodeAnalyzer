#pragma once

#include <clang-c/Index.h>

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <chrono>

#include "ClangUtilityFunctions.h"
#include "2_Diagnostic_Reporting.h"
#include "5_Token_extraction_and_manipulation.h"
#include "6_Translation_unit_manipulation.h"
#include "8_File_manipulation_routines.h"
#include "11_String_manipulation_routines.h"

#define ADD_STRING_OUT_NAME(     tabCount, functionName)                          strData += tabOffset(tabCount) + functionName                 + '\n';
#define ADD_STRING_OUT_NEWLINE()                                                  strData +=                                                      '\n';

#define ADD_STRING_OUT(          tabCount, functionName, functionValue)           strData += tabOffset(tabCount) + functionName + functionValue;
#define ADD_STRING_OUT_NL(       tabCount, functionName, functionValue)           strData += tabOffset(tabCount) + functionName + functionValue + '\n';

#define ADD_STRING_OUT_IF(       tabCount, functionName, functionValue) if(print) strData += tabOffset(tabCount) + functionName + functionValue;
#define ADD_STRING_OUT_IF_NL(    tabCount, functionName, functionValue) if(print) strData += tabOffset(tabCount) + functionName + functionValue + '\n';

using namespace std;

class ExecutionTimeMeasurement
{
public:
    ExecutionTimeMeasurement(string&& text) : m_text(text)
    {
        m_startTime = std::chrono::system_clock::now();
    }

    ~ExecutionTimeMeasurement()
    {
        m_endTime = std::chrono::system_clock::now();
        std::chrono::duration<double, std::ratio<1, 1000>> elapsedSeconds = m_endTime - m_startTime;

        cout << m_text << " " <<  elapsedSeconds.count() << " milliseconds." << endl;
    }

private:
    const string m_text;

    std::chrono::time_point<std::chrono::system_clock> m_startTime; 
    std::chrono::time_point<std::chrono::system_clock> m_endTime; 
};

class ClientData
{
public:

    ClientData(CXTranslationUnit tu, uint32_t level = 0)
    {
        translationUnit = tu;
        treeLevel = level;
    }

    CXTranslationUnit translationUnit;
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

void processBeforeAll();
bool processFolder(const string& path);
void processFile(const string& folderPath, const string& fileName);

bool saveToFile(const string& path, const string& data);
bool appendToFile(const string& path, const string& data);

bool saveFile(const string& path, const string& data, ios_base::openmode mode);
