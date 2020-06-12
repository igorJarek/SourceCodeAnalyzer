#pragma once

#include <clang-c/Index.h>
#include <UtilityFunctions.h>
#include <ClangUtilityFunctions.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/*

	Used:

		1.  CXString					clang_getCursorUSR(CXCursor C)
		8.  CXString					clang_getCursorSpelling(CXCursor C)
		9.  CXSourceRange				clang_Cursor_getSpellingNameRange(CXCursor, unsigned pieceIndex, unsigned options)

		12. CXPrintingPolicy			clang_getCursorPrintingPolicy(CXCursor C)
		13. void						clang_PrintingPolicy_dispose(CXPrintingPolicy Policy)
		14. CXString					clang_getCursorPrettyPrinted(CXCursor Cursor, CXPrintingPolicy Policy)

		15. CXString					clang_getCursorDisplayName(CXCursor C)
		16. CXCursor					clang_getCursorReferenced(CXCursor C)
		17. CXCursor					clang_getCursorDefinition(CXCursor C)
		18. unsigned					clang_isCursorDefinition(CXCursor C)
		19. CXCursor					clang_getCanonicalCursor(CXCursor C)
		21. int							clang_Cursor_isDynamicCall(CXCursor C)
		22. CXType						clang_Cursor_getReceiverType(CXCursor C)																			libclang.dll throw Illegal Instruction

		28. unsigned					clang_Cursor_isVariadic(CXCursor C)
		29. unsigned					clang_Cursor_isExternalSymbol(CXCursor C, CXString* language, CXString* definedIn, unsigned* isGenerated)
		30. CXSourceRange				clang_Cursor_getCommentRange(CXCursor C)
		31. CXString					clang_Cursor_getRawCommentText(CXCursor C)
		32. CXString 					clang_Cursor_getBriefCommentText(CXCursor C)

	Unused:

		2.  CXString					clang_constructUSR_ObjCClass(const char* class_name)
		3.  CXString					clang_constructUSR_ObjCCategory(const char* class_name, const char* category_name)
		4.  CXString					clang_constructUSR_ObjCProtocol(const char* protocol_name)
		5.  CXString					clang_constructUSR_ObjCIvar(const char* name, CXString classUSR)
		6.  CXString					clang_constructUSR_ObjCMethod(const char* name, unsigned isInstanceMethod, CXString classUSR)
		7.  CXString					clang_constructUSR_ObjCProperty(const char* property, CXString classUSR)

		10. unsigned					clang_PrintingPolicy_getProperty(CXPrintingPolicy Policy, enum CXPrintingPolicyProperty Property)					-> CXPrintingPolicy2String
		11. void						clang_PrintingPolicy_setProperty(CXPrintingPolicy Policy, enum CXPrintingPolicyProperty Property, unsigned Value)	-> CXPrintingPolicy2String

		20. int							clang_Cursor_getObjCSelectorIndex(CXCursor C)
		23. unsigned					clang_Cursor_getObjCPropertyAttributes(CXCursor C, unsigned reserved)
		24. CXString					clang_Cursor_getObjCPropertyGetterName(CXCursor C)
		25. CXString					clang_Cursor_getObjCPropertySetterName(CXCursor C)
		26. unsigned					clang_Cursor_getObjCDeclQualifiers(CXCursor C)
		27. unsigned					clang_Cursor_isObjCOptional(CXCursor C)

*/

struct PrintingPolicy 
{
	void adjustForCPlusPlus() 
	{
		SuppressTagKeyword		= true;
		Bool					= true;
		UseVoidForZeroParams	= false;
	}

	unsigned Indentation							: 8;
	unsigned SuppressSpecifiers						: 1;
	unsigned SuppressTagKeyword						: 1;
	unsigned IncludeTagDefinition					: 1;
	unsigned SuppressScope							: 1;
	unsigned SuppressUnwrittenScope					: 1;
	unsigned SuppressInitializers					: 1;
	unsigned ConstantArraySizeAsWritten				: 1;
	unsigned AnonymousTagLocations					: 1;
	unsigned SuppressStrongLifetime					: 1;
	unsigned SuppressLifetimeQualifiers				: 1;
	unsigned SuppressTemplateArgsInCXXConstructors	: 1;
	unsigned Bool									: 1;
	unsigned Restrict								: 1;
	unsigned Alignof								: 1;
	unsigned UnderscoreAlignof						: 1;
	unsigned UseVoidForZeroParams					: 1;
	unsigned TerseOutput							: 1;
	unsigned PolishForDeclaration					: 1;
	unsigned Half									: 1;
	unsigned MSWChar								: 1;
	unsigned IncludeNewlines						: 1;
	unsigned MSVCFormatting							: 1;
	unsigned ConstantsAsWritten						: 1;
	unsigned SuppressImplicitBase					: 1;
	unsigned FullyQualifiedName						: 1;
	unsigned RemapFilePaths							: 1;
	unsigned PrintCanonicalTypes					: 1;

	//std::function<std::string(StringRef)> remapPath;
};

void _9_printCrossReferencingInTheAST(string & strData, const CXCursor & cursor, uint32_t curLevel);

CXString			_9_getCursorUSR							(CXCursor C);																						// 1.
CXString			_9_constructUSR_ObjCClass				(const char *class_name);																			// 2.
CXString			_9_constructUSR_ObjCCategory			(const char *class_name, const char *category_name);												// 3.
CXString			_9_constructUSR_ObjCProtocol			(const char *protocol_name);																		// 4.
CXString			_9_constructUSR_ObjCIvar				(const char *name, CXString classUSR);																// 5.
CXString			_9_constructUSR_ObjCMethod				(const char *name, unsigned isInstanceMethod, CXString classUSR);									// 6.
CXString			_9_constructUSR_ObjCProperty			(const char *property, CXString classUSR);															// 7.
CXString			_9_getCursorSpelling					(CXCursor C);																						// 8.
CXSourceRange		_9_Cursor_getSpellingNameRange			(CXCursor C, unsigned pieceIndex, unsigned options);												// 9.
unsigned			_9_PrintingPolicy_getProperty			(CXPrintingPolicy Policy, enum CXPrintingPolicyProperty Property);									// 10.
void				_9_PrintingPolicy_setProperty			(CXPrintingPolicy Policy, enum CXPrintingPolicyProperty Property, unsigned Value);					// 11.
CXPrintingPolicy	_9_getCursorPrintingPolicy				(CXCursor C);																						// 12.
void				_9_PrintingPolicy_dispose				(CXPrintingPolicy Policy);																			// 13.
CXString			_9_getCursorPrettyPrinted				(CXCursor Cursor, CXPrintingPolicy Policy);															// 14.
CXString			_9_getCursorDisplayName					(CXCursor C);																						// 15.
CXCursor			_9_getCursorReferenced					(CXCursor C);																						// 16.
CXCursor			_9_getCursorDefinition					(CXCursor C);																						// 17.
unsigned			_9_isCursorDefinition					(CXCursor C);																						// 18.
CXCursor			_9_getCanonicalCursor					(CXCursor C);																						// 19.
int					_9_getObjCSelectorIndex					(CXCursor C);																						// 20.
int					_9_isDynamicCall						(CXCursor C);																						// 21.
CXType				_9_getReceiverType						(CXCursor C);																						// 22.  libclang.dll throw Illegal Instruction
unsigned			_9_getObjCPropertyAttributes			(CXCursor C, unsigned reserved);																	// 23.
CXString			_9_getObjCPropertyGetterName			(CXCursor C);																						// 24.
CXString			_9_getObjCPropertySetterName			(CXCursor C);																						// 25.
unsigned			_9_getObjCDeclQualifiers				(CXCursor C);																						// 26.
unsigned			_9_isObjCOptional						(CXCursor C);																						// 27.
unsigned			_9_isVariadic							(CXCursor C);																						// 28.
unsigned			_9_isExternalSymbol						(CXCursor C, CXString *language, CXString *definedIn, unsigned *isGenerated);						// 29.
CXSourceRange		_9_getCommentRange						(CXCursor C);																						// 30.
CXString			_9_getRawCommentText					(CXCursor C);																						// 31.
CXString 			_9_getBriefCommentText					(CXCursor C);																						// 32.
