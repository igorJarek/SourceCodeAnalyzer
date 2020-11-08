#include "8_File_manipulation_routines.h"
#include <Html/Html.h>

void _8_file_manipulation(const CXTranslationUnit& translationUnit, const string& filePath)
{
    OutputTree outputTree;

    outputTree.addString(0, "8. File manipulation routines : ");

    CXFile file = clang_getFile(translationUnit, filePath.c_str());                                                                     // 5.
    if(!file)
        outputTree.addString(1, "clang_getFile : NULL");
    else
    {
        CXString        fileName = clang_getFileName(file);                                                                             // 1.

        time_t          fileTime = clang_getFileTime(file);                                                                             // 2.
        char            timeBuff[255] = { 0 };
        ctime_s(timeBuff, sizeof(timeBuff), &fileTime);

        CXFileUniqueID  fileUniqueIDStruct;
        int32_t         fileUniqueID = clang_getFileUniqueID(file, &fileUniqueIDStruct);                                                // 3.

        uint32_t        isFileMultipleIncludeGuarded = clang_isFileMultipleIncludeGuarded(translationUnit, file);                       // 4.

        size_t          size;
        const char*     fileContents = clang_getFileContents(translationUnit, file, &size);                                             // 6.
        CXString        realPathName = clang_File_tryGetRealPathName(file);                                                             // 8.

        outputTree.addString(1, "clang_getFileName : ",                                 fileName);
        outputTree.addString(1, "clang_getFileTime : ",                                 string(timeBuff));
        outputTree.addString(1, "clang_getFileUniqueID : ",                             to_string(fileUniqueIDStruct.data[0]) + ", " +
                                                                                        to_string(fileUniqueIDStruct.data[1]) + ", " +
                                                                                        to_string(fileUniqueIDStruct.data[2]));
        outputTree.addString(1, "clang_getFileUniqueID [return value] : ",              fileUniqueID);
        outputTree.addString(1, "clang_isFileMultipleIncludeGuarded [return value] : ", isFileMultipleIncludeGuarded);
        outputTree.addString(1, "clang_File_tryGetRealPathName [return value] : ",      realPathName);
        outputTree.addString(1, "clang_getFileContents [size] : ",                      size);
        outputTree.addString(1, "clang_getFileContents [return value] : ");
        outputTree.addValue(2, fileContents);
    }

    string saveFilePath{ filePath + FILE_FILE_EXT };
    if(!outputTree.saveToFile(saveFilePath))
        cout << "Couldn't save file : " << saveFilePath << endl;

    HTMLBuilder htmlBuilder;
    string tableID{ "TBL" };

    htmlBuilder.setIndexTitle(saveFilePath + ".html");
    htmlBuilder.setFileNameHeader(filePath);
    htmlBuilder.setFilePathHeader(saveFilePath + ".html");

    htmlBuilder.addTable("File Informations", tableID, {"Category", "Functions", "File Content"});
    htmlBuilder.addTableRows(tableID, outputTree);

    if(!htmlBuilder.saveFile(saveFilePath + ".html"))
        cout << "Couldn't save HTML file : " << saveFilePath + ".html" << endl;
}

CXString        _8_getFileName                      (CXFile SFile)
                                                    { return clang_getFileName(SFile); }

time_t          _8_getFileTime                      (CXFile SFile)
                                                    { return clang_getFileTime(SFile); }

int             _8_getFileUniqueID                  (CXFile file, CXFileUniqueID *outID)
                                                    { return clang_getFileUniqueID(file, outID); }

unsigned        _8_isFileMultipleIncludeGuarded     (CXTranslationUnit tu, CXFile file)
                                                    { return clang_isFileMultipleIncludeGuarded(tu, file); }

CXFile          _8_getFile                          (CXTranslationUnit tu, const char *file_name)
                                                    { return clang_getFile(tu, file_name); }

const char *    _8_getFileContents                  (CXTranslationUnit tu, CXFile file, size_t *size)
                                                    { return clang_getFileContents(tu, file, size); }

int             _8_File_isEqual                     (CXFile file1, CXFile file2)
                                                    { return clang_File_isEqual(file1, file2); }

CXString        _8_File_tryGetRealPathName          (CXFile file)
                                                    { return clang_File_tryGetRealPathName(file); }
