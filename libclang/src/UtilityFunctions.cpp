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

bool saveToFile(const string& path, const string& data)
{
    fstream stream;
    stream.open(path, std::fstream::out | std::fstream::trunc);
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

            ClientData clientData;
            clientData.htmlBuilder->setIndexTitle(fileWithExtension);
            clientData.htmlBuilder->setFileNameHeader(fileWithExtension);
            clientData.htmlBuilder->setFilePathHeader(absoluteFilePath);

            clientData.htmlBuilder->addTree("1. AST", "AST");

            CXCursor cursor = clang_getTranslationUnitCursor(*translationUnit);
            _8_file_manipulation(*translationUnit, absoluteFilePath);

            clang_visitChildren(cursor, visitor, &clientData);

            _6_releaseTranslationUnit(translationUnit);

            clientData.htmlBuilder->saveFile(absoluteFilePath + ".html");
        }

        clang_disposeIndex(index);
    }
}

CXChildVisitResult visitor(CXCursor cursor, CXCursor parent, CXClientData client_data)
{
    ClientData* clientDataPtr = reinterpret_cast<ClientData*>(client_data);
    if (!clientDataPtr)
        return CXChildVisit_Break;

    uint32_t curLevel               = clientDataPtr->treeLevel;
    shared_ptr<HTMLBuilder> html    = clientDataPtr->htmlBuilder;

    dumpAST(html, curLevel, cursor);
    printCursor(html, curLevel, cursor);

    ClientData nextClientData(html, curLevel + 1);
    clang_visitChildren(cursor, visitor, &nextClientData);

    return CXChildVisit_Continue;
}

void dumpAST(shared_ptr<HTMLBuilder> html, uint32_t curLevel, const CXCursor& cursor)
{
    string strData;
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
    strData += " used " + _11_CXString2String(cursorSpelling) + " '" + _11_CXString2String(cursorTypeSpelling);

    html->addTreeElement("AST", { curLevel, strData });
}

void printCursor(shared_ptr<HTMLBuilder> html, uint32_t curLevel, const CXCursor& cursor)
{
    _1_printMangling(html, curLevel, cursor);
    _3_printASTIntrospection(html, curLevel, cursor);
    _7_printInformationForAttributes(html, curLevel, cursor);
    _15_printTypeInformationForCXCursors(html, curLevel, cursor);
}