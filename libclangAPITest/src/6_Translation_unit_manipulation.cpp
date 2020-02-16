#include "6_Translation_unit_manipulation.h"

CXTranslationUnit* _6_translation_unit_manipulation(CXIndex& index, const string& filePath)
{
	string tUnitSavePath{ filePath + ".tunit" };
	string strData = "Translation Unit Manipulation :\n";

	CXTranslationUnit* translationUnit = new CXTranslationUnit;
	CXErrorCode errorCode = clang_parseTranslationUnit2(index, 
														filePath.c_str(), 
														COMPILATION_ARGS, 
														sizeof(COMPILATION_ARGS) / sizeof(const char*), 
														nullptr, 
														0, 
														CXTranslationUnit_None,  /* CXTranslationUnit_Flags */
														translationUnit); // 7.

	_2_diagnostic_reporting(*translationUnit, filePath);

	if (errorCode == CXError_Success)
	{
		CXString TranslationUnitSpelling = clang_getTranslationUnitSpelling(*translationUnit); // 1.
		uint32_t defaultEditingTranslationUnitOptions = clang_defaultEditingTranslationUnitOptions(); // 5.
		uint32_t defaultSaveOptions = clang_defaultSaveOptions(*translationUnit); // 9.

		int32_t saveTranslationUnit = clang_saveTranslationUnit(*translationUnit, tUnitSavePath.c_str(), CXSaveTranslationUnit_None); // 10.

		uint32_t defaultReparseOptions = clang_defaultReparseOptions(*translationUnit); // 13.

		CXTUResourceUsage getCXTUResourceUsage = clang_getCXTUResourceUsage(*translationUnit); // 16.
		string getCXTUResourceUsageString = CXTUResourceUsage2String(getCXTUResourceUsage, 2);
		clang_disposeCXTUResourceUsage(getCXTUResourceUsage); // 17.

		CXTargetInfo translationUnitTargetInfo = clang_getTranslationUnitTargetInfo(*translationUnit); // 18.
		CXString targetInfo_getTriple = clang_TargetInfo_getTriple(translationUnitTargetInfo); // 20.
		int32_t targetInfo_getPointerWidth = clang_TargetInfo_getPointerWidth(translationUnitTargetInfo); // 21.
		clang_TargetInfo_dispose(translationUnitTargetInfo); // 19.

		strData += tabOffset(1) + "clang_parseTranslationUnit2 : " + CXErrorCode2String(errorCode) + '\n';
		strData += tabOffset(1) + "clang_getTranslationUnitSpelling : " + _11_CXString2String(TranslationUnitSpelling) + '\n';
		strData += tabOffset(1) + "clang_defaultEditingTranslationUnitOptions : " + to_string(defaultEditingTranslationUnitOptions) + '\n';
		strData += tabOffset(1) + "clang_defaultSaveOptions : " + to_string(defaultSaveOptions) + '\n';
		strData += tabOffset(1) + "clang_saveTranslationUnit : " + CXSaveError2String(saveTranslationUnit) + '\n';
		strData += tabOffset(1) + "clang_defaultReparseOptions : " + to_string(defaultReparseOptions) + '\n';
		strData += tabOffset(1) + "clang_getCXTUResourceUsage : " + '\n' + getCXTUResourceUsageString;
		strData += tabOffset(1) + "clang_TargetInfo_getTriple : " + _11_CXString2String(targetInfo_getTriple) + '\n';
		strData += tabOffset(1) + "clang_TargetInfo_getPointerWidth : " + to_string(targetInfo_getPointerWidth) + '\n';
	}
	else
	{
		strData += tabOffset(1) + "clang_parseTranslationUnit2 : " + CXErrorCode2String(errorCode) + '\n';
		delete translationUnit;
		translationUnit = nullptr;
	}

	bool ret = saveToFile(filePath + ".tunitLog", strData);

	return translationUnit;
}

void _6_releaseTranslationUnit(CXTranslationUnit* translationUnit)
{
	if (translationUnit)
	{
		clang_disposeTranslationUnit(*translationUnit); // 12.
		delete translationUnit;
	}	
}

const char* _6_CXTUResourceUsageKind2constChar(enum CXTUResourceUsageKind kind)
{
	return clang_getTUResourceUsageName(kind); // 15.
}