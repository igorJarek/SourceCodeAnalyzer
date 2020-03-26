#include "5_Token_extraction_and_manipulation.h"

void _5_token_extraction(const CXTranslationUnit& translationUnit, const string& filePath)
{
	string strData{ "Token extraction and manipulation : \n" };
	uint32_t tOffset{ 1 };



	string saveFilePath{ filePath + ".tokens" };
	if (!saveToFile(saveFilePath, strData))
		cout << "Couldn't create file : " << saveFilePath << endl;
}