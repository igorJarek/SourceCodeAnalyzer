#include "8_File_manipulation_routines.h"

void _8_file_manipulation(const CXTranslationUnit& translationUnit, const string& filePath)
{
    string strData;

    ADD_STRING_OUT_NAME(0, "8. File manipulation routines : ")

    CXFile file = clang_getFile(translationUnit, filePath.c_str());                                                                     // 5.
    if(!file)
        ADD_STRING_OUT_NAME(1, "clang_getFile : null")
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

        ADD_STRING_OUT_NL(1, "clang_getFileName : ",                                CXString2String(fileName))
        ADD_STRING_OUT   (1, "clang_getFileTime : ",                                string(timeBuff))

        ADD_STRING_OUT_NL(1, "clang_getFileUniqueID : ",                             to_string(fileUniqueIDStruct.data[0]) + ", " +
                                                                                     to_string(fileUniqueIDStruct.data[1]) + ", " +
                                                                                     to_string(fileUniqueIDStruct.data[2]))

        ADD_STRING_OUT_NL(1, "clang_getFileUniqueID [return value] : ",              to_string(fileUniqueID))
        ADD_STRING_OUT_NL(1, "clang_isFileMultipleIncludeGuarded [return value] : ", to_string(isFileMultipleIncludeGuarded))
        ADD_STRING_OUT_NL(1, "clang_File_tryGetRealPathName [return value] : ",      CXString2String(realPathName))
        ADD_STRING_OUT_NL(1, "clang_getFileContents [size] : ",                      to_string(size))
        ADD_STRING_OUT_NAME(1, "clang_getFileContents [return value] : ")
        ADD_STRING_OUT_NAME(2, fileContents)
    }

    string saveFilePath{ filePath + ".file" };
    if (!saveToFile(saveFilePath, strData))
        cout << "Couldn't save file : " << saveFilePath << endl;
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
