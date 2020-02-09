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
    string str;
    for (uint32_t index{ 0 }; index < offset; ++index)
        str += '\t';

    return str;
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
        CXTranslationUnit translationUnit = clang_parseTranslationUnit(index, absoluteFilePath.c_str(), COMPILATION_ARGS, sizeof(COMPILATION_ARGS) / sizeof(const char*), nullptr, 0, CXTranslationUnit_None);
        _2_diagnostic_reporting(translationUnit, absoluteFilePath);

        ClientData clientData;
        CXCursor cursor = clang_getTranslationUnitCursor(translationUnit);
        clang_visitChildren(cursor, visitor, &clientData);

        clang_disposeTranslationUnit(translationUnit);
        clang_disposeIndex(index);

        bool ret;
        ret = saveToFile(absoluteFilePath + ".ast", clientData.astStringData);
        ret = saveToFile(absoluteFilePath + ".astext", clientData.astExtStringData);
    }
}

CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData client_data)
{
    ClientData* clientData = reinterpret_cast<ClientData*>(client_data);
    string& astStringData = clientData->astStringData;
    string& astExtStringData = clientData->astExtStringData;
    uint32_t curLevel = clientData->treeLevel;

    astStringData += tabOffset(curLevel);
    astExtStringData += tabOffset(curLevel);

    dumpAST(astStringData, cursor);
    printCursor(astExtStringData, cursor);

    ClientData nextClientData(curLevel + 1);
    clang_visitChildren(cursor, visitor, &nextClientData);
    astStringData += nextClientData.astStringData;

    return CXChildVisit_Continue;
}

void dumpAST(string& strData, const CXCursor& cursor)
{
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
    strData += " used " + _11_CXString2String(cursorSpelling) + " '" + _11_CXString2String(cursorTypeSpelling) + "'\n";
}

void printCursor(string& strData, const CXCursor& cursor)
{
    
}