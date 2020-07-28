#include "UtilityFunctions.h"
#include "Database.h"

Database database("..\\lib\\lib.sqlite3");

string tabOffset(uint32_t offset)
{
    return string(offset, '\t');
}

bool isFileHeader(const string& extension)
{
    if (extension.compare("h") == 0 || extension.compare("hpp") == 0)
        return true;
    else
        return false;
}

bool isFileSource(const string& extension)
{
    if (extension.compare("c") == 0 || extension.compare("cpp") == 0)
        return true;
    else
        return false;
}

int64_t countStringLines(const string& str)
{
    int64_t lines{ 0 };
    const char* data = str.c_str();

    while(*data != '\0')
    {
        if(*data == '\n')
            ++lines;

        ++data;
    }

    return lines;
}

int64_t countFileLines(const string& filePath)
{
    fstream stream;
    int64_t lines{ -1 };

    stream.open(filePath, std::fstream::in);
    if (stream.is_open())
    {
        lines = 0;

        string s;
        while (getline(stream, s))
            ++lines;

        stream.close();
    }

    return lines;
}

int64_t countFileLineColumns(const string& filePath, int64_t line)
{
    if (line < 0)
        return -1;

    fstream stream;
    int64_t columns{ -1 };
    int64_t lines{ -1 };

    stream.open(filePath, std::fstream::in);
    if (stream.is_open())
    {
        string str;
        lines = 0;

        while (getline(stream, str))
        {
            ++lines;
            if (lines == line)
                break;
        }

        if(lines == line) // file lines < line
            columns = str.size();

        stream.close();
    }

    return columns;
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
        if (findDataStruct.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && (fileName.compare(".") == 0 || fileName.compare("..") == 0))
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

void processBeforeAll()
{
    string clangVersion = CXString2String(_18_getClangVersion());
    cout << "Clang version : " << clangVersion << endl << endl;

    _18_toggleCrashRecovery(1);

    string dbErrMsg = database.createGlobalTable(clangVersion, APP_NAME, APP_VERSION);
    if(database.isNotOK())
        cout << "Database error : " << dbErrMsg << endl;
}

void processAfterAll()
{
    saveBaseCXCursorInfo(nullptr, nullptr, SaveCursorAction::SAVE_CURSOR_CUR_FILE);
    saveBaseCXCursorInfo(nullptr, nullptr, SaveCursorAction::SAVE_CURSOR_CURINFO_FILE);
}

bool processFolder(const string& path)
{
    bool ret = recursiveFolderSearch(path);
    if (!ret)
    {
        cout << "\tError : " << "Unable to open directory (Error code : " << GetLastError() << ") : " << path << endl;
        return false;
    }

    return true;
}

void processFile(const string& folderPath, const string& fileName)
{
    string fileWithExtension{ fileName };
    string absoluteFilePath{ folderPath + fileWithExtension };
    string fileExtension{ fileWithExtension.substr(fileWithExtension.find_last_of(".") + 1) };

    if (isFileHeader(fileExtension) || isFileSource(fileExtension))
    {
        ExecutionTimeMeasurement timeMeasurement("File " + absoluteFilePath + " has parsed in");

        string dbErrMsg = database.createSourceCodeTable(absoluteFilePath);
        if(database.isNotOK())
            cout << "Database error : " << dbErrMsg << endl;

        CXIndex index = clang_createIndex(0, 0);
        CXTranslationUnit* translationUnit = _6_translation_unit_manipulation(index, absoluteFilePath);
        if (translationUnit)
        {
            ClientData clientData(*translationUnit);
            CXCursor cursor = clang_getTranslationUnitCursor(*translationUnit);

            saveBaseCXCursorInfo(translationUnit, nullptr, SaveCursorAction::ADD_FILE_BASE_INFO);

            _5_token_extraction(*translationUnit, absoluteFilePath);
            _8_file_manipulation(*translationUnit, absoluteFilePath);

            clang_visitChildren(cursor, visitor, &clientData);

            _6_disposeTranslationUnit(*translationUnit);
            delete translationUnit;
            translationUnit = nullptr;

            bool ret;
            ret = saveToFile(absoluteFilePath + AST_FILE_EXT,     clientData.astStringData);
            ret = saveToFile(absoluteFilePath + AST_EXT_FILE_EXT, clientData.astExtStringData);
        }

        clang_disposeIndex(index);
    }
}

bool saveToFile(const string& path, const string& data)
{
    fstream stream;
    stream.open(path, std::fstream::out | std::fstream::trunc);
    if (stream.is_open())
    {
        stream << data;
        stream.close();

        return true;
    }
    else
        return false;
}

bool saveToFile(const string& path, const stringstream& data)
{
    fstream stream;
    stream.open(path, std::fstream::out | std::fstream::trunc);
    if (stream.is_open())
    {
        stream << data.rdbuf();
        stream.close();

        return true;
    }
    else
        return false;
}
