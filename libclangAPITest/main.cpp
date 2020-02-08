#include "UtilityFunctions.h"

using namespace std;

CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData client_data)
{
    Arguments* arguments = reinterpret_cast<Arguments*>(client_data);
    string& strData = arguments->strData;
    uint32_t curLevel = arguments->treeLevel;

    strData += tabOffset(curLevel);

    dumpAST(strData, cursor);
    printCursor(cursor, curLevel);

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
            return processFolder(nextDir);
        }
        else
            processFile(folderPath, fileName);

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