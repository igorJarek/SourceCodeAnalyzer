#include "UtilityFunctions.h"

using namespace std;

int main(int argc, char* argv[])
{
    processBeforeAll();
    bool ret = recursiveFolderSearch(LIB_PATH);
    system("pause");
    return EXIT_SUCCESS;
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
            if (!processFolder(nextDir))
                return false;
        }
        else
            processFile(folderPath, fileName);

    } while (FindNextFileA(hFind, &findDataStruct) != 0);

    FindClose(hFind);
    return true;
}