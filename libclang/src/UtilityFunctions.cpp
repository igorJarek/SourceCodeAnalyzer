#include <ExecutionTimeMeasurement/ExecutionTimeMeasurement.h>
#include <FolderBrowser/FolderBrowser.h>
#include <Html/Html.h>

#include "UtilityFunctions.h"

#include <filesystem>

bool isOptionEnabled(uint32_t categoryMask)
{
    return g_appOptions & categoryMask;
}

bool isOptionNotEnabled(uint32_t categoryMask)
{
    return !(g_appOptions & categoryMask);
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
    std::fstream stream;
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

    std::fstream stream;
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

    folderBrowser.addIgnoreFilePath("..\\lib\\src\\TestPrimitives.cpp");
    folderBrowser.addIgnoreFilePath("..\\lib\\include\\TestPrimitives.h");

    folderBrowser.startFolderBrowse(folderPath);

    const list<string>& headerFileList = folderBrowser.getHeaderFileList();
    const list<string>& sourceFileList = folderBrowser.getSourceFileList();

    for(const string& absoluteFilePath : headerFileList)
        processFile(absoluteFilePath);

    for(const string& absoluteFilePath : sourceFileList)
        processFile(absoluteFilePath);
}

string extractFileName(const string& absoluteFilePath)
{
    size_t backSlashPos = absoluteFilePath.find_last_of('\\');

    return absoluteFilePath.substr(backSlashPos + 1);
}

void processBeforeAll()
{
    string clangVersion = to_string(_18_getClangVersion());
    cout << "Clang version : " << clangVersion << endl << endl;

    _18_toggleCrashRecovery(1);
}

void processAfterAll()
{
    saveBaseCXCursorInfo(nullptr, nullptr, InfoAction::SAVE_FILE);
    saveBaseCXCursorInfo(nullptr, nullptr, InfoAction::SAVE_LINESTAMPS_FILE);

    saveBaseCXTypeInfo(nullptr, nullptr, InfoAction::SAVE_FILE);
    saveBaseCXTypeInfo(nullptr, nullptr, InfoAction::SAVE_LINESTAMPS_FILE);

    cout << endl;
}

void processFile(const string& absoluteFilePath)
{
    ExecutionTimeMeasurement timeMeasurement("File " + absoluteFilePath + " has parsed in");

    CXIndex index = clang_createIndex(0, 0);
    CXTranslationUnit* translationUnit = _6_translation_unit_manipulation(index, absoluteFilePath);
    if(translationUnit)
    {
        ClientData clientData(*translationUnit);
        CXCursor cursor = clang_getTranslationUnitCursor(*translationUnit);

        saveBaseCXCursorInfo(translationUnit, nullptr, InfoAction::ADD_INFO_LINESTAMP);
        saveBaseCXTypeInfo(translationUnit, nullptr, InfoAction::ADD_INFO_LINESTAMP);

        _5_token_extraction(*translationUnit, absoluteFilePath);
        _8_file_manipulation(*translationUnit, absoluteFilePath);

        clang_visitChildren(cursor, visitor, &clientData);

        _6_disposeTranslationUnit(*translationUnit);

        delete translationUnit;
        translationUnit = nullptr;

        bool ret;
        ret = clientData.astOutputTree.saveToFile(absoluteFilePath + AST_FILE_EXT);
        ret = clientData.astExtOutputTree.saveToFile(absoluteFilePath + AST_EXT_FILE_EXT);

        if(isOptionEnabled(HTML_ENABLED))
        {
            HTMLBuilder htmlBuilder;
            string tableID{ "TBL" };

            htmlBuilder.setIndexTitle(absoluteFilePath + AST_FILE_EXT);
            htmlBuilder.setFileNameHeader(extractFileName(absoluteFilePath));
            htmlBuilder.setFilePathHeader(absoluteFilePath);

            htmlBuilder.addTable("Abstract Syntax Tree", tableID, clientData.astOutputTree);

            ret = htmlBuilder.saveFile(absoluteFilePath + AST_FILE_EXT + ".html");

            htmlBuilder.clear();

            htmlBuilder.setIndexTitle(absoluteFilePath + AST_EXT_FILE_EXT);
            htmlBuilder.setFileNameHeader(extractFileName(absoluteFilePath));
            htmlBuilder.setFilePathHeader(absoluteFilePath);

            htmlBuilder.addTable("Extended Abstract Syntax Tree", tableID, clientData.astExtOutputTree);

            ret = htmlBuilder.saveFile(absoluteFilePath + AST_EXT_FILE_EXT + ".html");
        }
        else
        {
            removeFile(absoluteFilePath + AST_FILE_EXT + ".html");
            removeFile(absoluteFilePath + AST_EXT_FILE_EXT + ".html");
        }
    }

    clang_disposeIndex(index);
}

bool saveToFile(const string& path, const stringstream& data)
{
    std::fstream stream;
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

void removeFile(const string& path)
{
    std::filesystem::path removeFilePath(path);

    if(std::filesystem::exists(removeFilePath))
        std::filesystem::remove(removeFilePath);
}
