#include <folderbrowser/FolderBrowser.h>

#include "UtilityFunctions.h"

string tabOffset(uint32_t offset)
{
    return string(offset, '\t');
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

void recursiveFolderSearch(const string& folderPath)
{
    FolderBrowser folderBrowser;

    folderBrowser.clearFileList();
    folderBrowser.setFileTypeBrowser(FileType::SOURCE_FILE);
    folderBrowser.startFolderBrowse(folderPath);

    const list<string>& fileList = folderBrowser.getFileList();

    for(const string& absoluteFilePath : fileList)
        processFile(absoluteFilePath);
}

void processBeforeAll()
{
    string clangVersion = CXString2String(_18_getClangVersion());
    cout << "Clang version : " << clangVersion << endl << endl;

    _18_toggleCrashRecovery(1);
}

void processAfterAll()
{
    saveBaseCXCursorInfo(nullptr, nullptr, SaveCursorAction::SAVE_CURSOR_CUR_FILE);
    saveBaseCXCursorInfo(nullptr, nullptr, SaveCursorAction::SAVE_CURSOR_CURINFO_FILE);
}

void processFile(const string& absoluteFilePath)
{
    ExecutionTimeMeasurement timeMeasurement("File " + absoluteFilePath + " has parsed in");

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
