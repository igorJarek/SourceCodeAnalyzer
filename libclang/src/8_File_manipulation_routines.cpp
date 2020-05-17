#include "8_File_manipulation_routines.h"

void _8_file_manipulation(const CXTranslationUnit& translationUnit, const string& filePath)
{
    string strData{"File manipulation routines : \n"};
    uint32_t tOffset{ 1 };

    CXFile file = clang_getFile(translationUnit, filePath.c_str());													// 5.
    if(!file)
        strData += "clang_getFile : Null" + '\n';
    else
    {
        CXString fileName = clang_getFileName(file);																// 1.

        time_t fileTime = clang_getFileTime(file);																	// 2.
        char timeBuff[255] = { 0 };
        ctime_s(timeBuff, sizeof(timeBuff), &fileTime);

        CXFileUniqueID fileUniqueIDStruct;
        int32_t fileUniqueID = clang_getFileUniqueID(file, &fileUniqueIDStruct);									// 3.

        uint32_t isFileMultipleIncludeGuarded = clang_isFileMultipleIncludeGuarded(translationUnit, file);			// 4.

        size_t size;
        const char* fileContents = clang_getFileContents(translationUnit, file, &size);								// 6.
        CXString realPathName = clang_File_tryGetRealPathName(file);												// 8.

        strData += tabOffset(tOffset) + "clang_getFileName : " + _11_CXString2String(fileName) + '\n';
        strData += tabOffset(tOffset) + "clang_getFileTime : " + string(timeBuff);

        strData += tabOffset(tOffset) + "clang_getFileUniqueID : " + to_string(fileUniqueIDStruct.data[0]) + ", " +
                                                                     to_string(fileUniqueIDStruct.data[1]) + ", " +
                                                                     to_string(fileUniqueIDStruct.data[2]) + ", " + '\n';
        strData += tabOffset(tOffset) + "clang_getFileUniqueID [return value] : " + to_string(fileUniqueID) + '\n';

        strData += tabOffset(tOffset) + "clang_isFileMultipleIncludeGuarded [return value] : " + to_string(isFileMultipleIncludeGuarded) + '\n';
        strData += tabOffset(tOffset) + "clang_File_tryGetRealPathName [return value] : " + _11_CXString2String(realPathName) + "\n\n";

        strData += tabOffset(tOffset) + "clang_getFileContents [size] : " + to_string(size) + '\n';
        strData += tabOffset(tOffset) + "clang_getFileContents [return value] : " + '\n' + tabOffset(tOffset + 1) + fileContents + '\n';
    }
        
    string saveFilePath{ filePath + ".file" };
    if (!saveToFile(saveFilePath, strData))
        cout << "Couldn't create file : " << saveFilePath << endl;
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
