#pragma once

#include "UtilityFunctions.h"
#include "11_String_manipulation_routines.h"
#include "StructsEnums2String.h"
#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/*
	Used:

		1.  unsigned					clang_getNumDiagnosticsInSet			(CXDiagnosticSet Diags)
		2.  CXDiagnostic				clang_getDiagnosticInSet				(CXDiagnosticSet Diags, unsigned Index)
		4.  void						clang_disposeDiagnosticSet				(CXDiagnosticSet Diags)
		6.  unsigned					clang_getNumDiagnostics					(CXTranslationUnit Unit)
		7.  CXDiagnostic				clang_getDiagnostic						(CXTranslationUnit Unit, unsigned Index)
		8.  CXDiagnosticSet				clang_getDiagnosticSetFromTU			(CXTranslationUnit Unit)
		9.  void						clang_disposeDiagnostic					(CXDiagnostic Diagnostic)
		10. CXString					clang_formatDiagnostic					(CXDiagnostic Diagnostic, unsigned Options)
		11. unsigned 					clang_defaultDiagnosticDisplayOptions	(void)
		12. enum CXDiagnosticSeverity	clang_getDiagnosticSeverity				(CXDiagnostic)
		13. CXSourceLocation			clang_getDiagnosticLocation				(CXDiagnostic)
		14. CXString					clang_getDiagnosticSpelling				(CXDiagnostic)
		15. CXString					clang_getDiagnosticOption				(CXDiagnostic Diag, CXString * Disable)
		16. unsigned					clang_getDiagnosticCategory				(CXDiagnostic)
		18. CXString					clang_getDiagnosticCategoryText			(CXDiagnostic)
		19. unsigned					clang_getDiagnosticNumRanges			(CXDiagnostic)
		20. CXSourceRange				clang_getDiagnosticRange				(CXDiagnostic Diagnostic, unsigned Range)
		21. unsigned					clang_getDiagnosticNumFixIts			(CXDiagnostic Diagnostic)
		22. CXString					clang_getDiagnosticFixIt				(CXDiagnostic Diagnostic, unsigned FixIt, CXSourceRange * ReplacementRange)

	Unused:

		3.  CXDiagnosticSet				clang_loadDiagnostics					(const char* file, enum CXLoadDiag_Error* error, CXString* errorString)
		5.  CXDiagnosticSet				clang_getChildDiagnostics				(CXDiagnostic D)																	// ?????????
		17. CXString					clang_getDiagnosticCategoryName			(unsigned Category)																	// DEPRECATED
*/

void _2_diagnostic_reporting(CXTranslationUnit& translationUnit, const string& filePath);
void _2_printDiagnostic(string& stream, const CXDiagnostic& diagnostic);