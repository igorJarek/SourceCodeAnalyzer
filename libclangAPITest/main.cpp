#include <iostream>
#include <fstream>
#include <windows.h>
#include <clang-c/Index.h>
#include <string>
#include "UtilityFunctions.h"
#include "2_Diagnostic_Reporting.h"

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

CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData client_data)
{
    Arguments* arguments = reinterpret_cast<Arguments*>(client_data);
    string& strData = arguments->strData;
    uint32_t curLevel = arguments->treeLevel;

    for (uint32_t index{ 0 }; index < curLevel; ++index)
        strData += "\t";

    CXCursorKind kind = clang_getCursorKind(cursor);
    CXString kindSpelling = clang_getCursorKindSpelling(kind);
    strData += _11_CXString2String(kindSpelling) + " ";

    CXSourceLocation cursorLocation = clang_getCursorLocation(cursor);
    CXSourceRange cursorRange = clang_getCursorExtent(cursor);
    CXSourceLocation locationStart = clang_getRangeStart(cursorRange);
    CXSourceLocation locationEnd = clang_getRangeEnd(cursorRange);

    CXFile cursorFile;
    uint32_t cursorLine, cursorColumn, cursorOffset;
    clang_getExpansionLocation(cursorLocation, &cursorFile, &cursorLine, &cursorColumn, &cursorOffset);

    CXFile startFile;
    uint32_t startLine, startColumn, startOffset;
    clang_getExpansionLocation(locationStart, &startFile, &startLine, &startColumn, &startOffset);

    CXFile endFile;
    uint32_t endLine, endColumn, endOffset;
    clang_getExpansionLocation(locationEnd, &endFile, &endLine, &endColumn /* endColumn -= 1; */, &endOffset);
    --endColumn;

    CXString fileName = clang_getFileName(startFile); // relative path
    CXString fileFullName = clang_File_tryGetRealPathName(startFile); // full path

    CXString cursorSpelling = clang_getCursorSpelling(cursor);
    CXType cursorType = clang_getCursorType(cursor);
    CXString cursorTypeSpelling = clang_getTypeSpelling(cursorType);

    strData += "<" + _11_CXString2String(fileName) + ":" + to_string(startLine) + ":" + to_string(startColumn) + ", col:" + to_string(endColumn) + ">" + " col:" + to_string(cursorColumn);
    strData += " used " + _11_CXString2String(cursorSpelling) + " '" + _11_CXString2String(cursorTypeSpelling) + "'";

    CXString USRString = clang_getCursorUSR(cursor);
    strData += " -> " + _11_CXString2String(USRString) + '\n';

    Arguments nextArguments(curLevel + 1);
    clang_visitChildren(cursor, visitor, &nextArguments);
    strData += nextArguments.strData;

    return CXChildVisit_Continue;
}

bool recursiveFolderSearch(const string& folderPath)
{
    WIN32_FIND_DATAA findDataStruct;
    string startDir{ folderPath + "*.*" };
    HANDLE hFind = FindFirstFileA(startDir.c_str(), &findDataStruct);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        cout << "\tError : " << "Unable to open directory (Error code : " << GetLastError() << ") : " << folderPath << endl;
        return false;
    }

    do
    {
        const string fileName{ findDataStruct.cFileName };
        if (findDataStruct.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY &&
            (fileName.compare(".") == 0 || fileName.compare("..") == 0))
            continue;

        if (findDataStruct.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            string nextDir{ folderPath + fileName + "\\" };
            bool ret = recursiveFolderSearch(nextDir);
            if (!ret)
            {
                cout << "\tError : " << "Unable to open directory (Error code : " << GetLastError() << ") : " << nextDir << endl;
                return false;
            }
        }
        else
        {
            string fileWithExtension{ fileName };
            string fileWithoutExtension{ fileWithExtension.substr(0, fileWithExtension.find_first_of(".")) };
            string absoluteFilePath{ folderPath + fileWithExtension };
            string fileExtension{ fileWithExtension.substr(fileWithExtension.find_last_of(".") + 1) };

            if (isFileHeader(fileExtension) || isFileSource(fileExtension))
            {
                CXIndex index = clang_createIndex(0, 0);
                const char* argsInclude = "-I";
                const char* argsPath = "C:\\Users\\Igor\\Desktop\\ClangTest\\libclangAPITest\\lib\\include";
                const char* args[2] = { argsInclude, argsPath };
                CXTranslationUnit translationUnit = clang_parseTranslationUnit(index, absoluteFilePath.c_str(), args, 2, nullptr, 0, CXTranslationUnit_None);
                _2_diagnostic_reporting(translationUnit, folderPath + fileWithExtension);

                Arguments arguments;
                CXCursor cursor = clang_getTranslationUnitCursor(translationUnit);
                clang_visitChildren(cursor, visitor, &arguments);

                clang_disposeTranslationUnit(translationUnit);
                clang_disposeIndex(index);

                fstream stream;
                stream.open(folderPath + fileWithExtension + ".ast", std::fstream::out | std::fstream::trunc);
                if (stream.is_open())
                {
                    stream << arguments.strData;
                    stream.close();
                }
                else
                {

                }
            }
        }
    } while (FindNextFileA(hFind, &findDataStruct) != 0);

    FindClose(hFind);
    return true;
}

int main(int argc, char* argv[])
{
    const string libPath = "C:\\Users\\Igor\\Desktop\\ClangTest\\libclangAPITest\\lib\\";

    bool ret = recursiveFolderSearch(libPath);

    return EXIT_SUCCESS;
}