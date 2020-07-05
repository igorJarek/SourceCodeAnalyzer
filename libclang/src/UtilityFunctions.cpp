#include "UtilityFunctions.h"

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

bool saveToFile(const string& path, const string& data)
{
    return saveFile(path, data, std::fstream::trunc);
}

bool appendToFile(const string& path, const string& data)
{
    return saveFile(path, data, std::fstream::app);
}

bool saveFile(const string& path, const string& data, ios_base::openmode mode)
{
    fstream stream;
    stream.open(path, std::fstream::out | mode);
    if (stream.is_open())
    {
        stream << data;
        stream.flush();
        stream.close();
        return true;
    }
    else
        return false;
}

void processBeforeAll()
{
    cout << "Clang version : " << CXString2String(_18_getClangVersion()) << endl;
    _18_toggleCrashRecovery(1);
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
        CXIndex index = clang_createIndex(0, 0);
        CXTranslationUnit* translationUnit = _6_translation_unit_manipulation(index, absoluteFilePath);
        if (translationUnit)
        {
            cout << "Parse file : " << absoluteFilePath << endl;

            ClientData clientData(*translationUnit);
            CXCursor cursor = clang_getTranslationUnitCursor(*translationUnit);

            _5_token_extraction(*translationUnit, absoluteFilePath);
            _8_file_manipulation(*translationUnit, absoluteFilePath);

            clang_visitChildren(cursor, visitor, &clientData);

            _6_disposeTranslationUnit(*translationUnit);
            delete translationUnit;
            translationUnit = nullptr;

            bool ret;
            ret = saveToFile(absoluteFilePath + ".ast", clientData.astStringData);
            ret = saveToFile(absoluteFilePath + ".astExt", clientData.astExtStringData);
        }

        clang_disposeIndex(index);
    }
}

CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData client_data)
{
    ClientData* clientDataPtr = reinterpret_cast<ClientData*>(client_data);
    CXTranslationUnit translationUnit = clientDataPtr->translationUnit;
    string& astStringData = clientDataPtr->astStringData;
    string& astExtStringData = clientDataPtr->astExtStringData;
    uint32_t curLevel = clientDataPtr->treeLevel;

    astStringData += tabOffset(curLevel);
    astExtStringData += tabOffset(curLevel);

    dumpAST(astStringData, cursor);
    printCursor(translationUnit, astExtStringData, cursor, curLevel);

    ClientData nextClientData(translationUnit, curLevel + 1);
    clang_visitChildren(cursor, visitor, &nextClientData);

    astStringData += nextClientData.astStringData;
    astExtStringData += nextClientData.astExtStringData;

    return CXChildVisit_Continue;
}