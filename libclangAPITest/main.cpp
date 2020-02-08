#include <iostream>
#include <fstream>
#include <windows.h>
#include <clang-c/Index.h>
#include <string>
#include "UtilityFunctions.h"
#include "2_Diagnostic_Reporting.h"

using namespace std;

CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData client_data)
{
    Arguments* arguments = reinterpret_cast<Arguments*>(client_data);
    string& strData = arguments->strData;
    uint32_t curLevel = arguments->treeLevel;

    strData += tabOffset(curLevel);
    dumpAST(strData, cursor);

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
                const char* argsPath = "C:\\Users\\Igor\\Desktop\\libclangAPITest\\libclangAPITest\\testLib\\include\\";
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
    const string libPath = "C:\\Users\\Igor\\Desktop\\libclangAPITest\\libclangAPITest\\testLib\\";
    bool ret = recursiveFolderSearch(libPath);

    return EXIT_SUCCESS;
}