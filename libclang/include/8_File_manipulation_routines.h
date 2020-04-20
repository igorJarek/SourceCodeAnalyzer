#pragma once

#include "UtilityFunctions.h"
#include <clang-c/Index.h>
#include "11_String_manipulation_routines.h"
#include <ctime>

using namespace std;

/*

	Used:

		1. CXString 		clang_getFileName						(CXFile SFile)
		2. time_t 			clang_getFileTime						(CXFile SFile)
		3. int 				clang_getFileUniqueID					(CXFile file, CXFileUniqueID *outID)
		4. unsigned 		clang_isFileMultipleIncludeGuarded		(CXTranslationUnit tu, CXFile file)
		5. CXFile 			clang_getFile							(CXTranslationUnit tu, const char *file_name)
		6. const char * 	clang_getFileContents					(CXTranslationUnit tu, CXFile file, size_t *size)
		8. CXString 		clang_File_tryGetRealPathName			(CXFile file)

	Unused:

		7. int 				clang_File_isEqual (CXFile file1, CXFile file2)

*/

void _8_file_manipulation(const CXTranslationUnit& translationUnit, const string& filePath);
CXFile _8_getFile(const CXTranslationUnit& translationUnit, const string& filePath);