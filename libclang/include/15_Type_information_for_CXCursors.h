#pragma once

#include <clang-c/Index.h>
#include "UtilityFunctions.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/*
	Used:

		1.  CXType 							clang_getCursorType									(CXCursor C)
		2.  CXString 						clang_getTypeSpelling								(CXType CT)
		3.  CXType 							clang_getTypedefDeclUnderlyingType					(CXCursor C)
		4.  CXType							clang_getEnumDeclIntegerType						(CXCursor C)
		5.  long long 						clang_getEnumConstantDeclValue						(CXCursor C)
		6.  unsigned long long				clang_getEnumConstantDeclUnsignedValue				(CXCursor C)
		7.  int 							clang_getFieldDeclBitWidth							(CXCursor C)

		8.  int 							clang_Cursor_getNumArguments						(CXCursor C)
		9.  CXCursor						clang_Cursor_getArgument							(CXCursor C, unsigned i)

		10. int 							clang_Cursor_getNumTemplateArguments				(CXCursor C)
		11. enum CXTemplateArgumentKind		clang_Cursor_getTemplateArgumentKind				(CXCursor C, unsigned I)
		12. CXType 							clang_Cursor_getTemplateArgumentType				(CXCursor C, unsigned I)
		13. long long 						clang_Cursor_getTemplateArgumentValue				(CXCursor C, unsigned I)
		14. unsigned long long 				clang_Cursor_getTemplateArgumentUnsignedValue		(CXCursor C, unsigned I)

		16. CXType							clang_getCanonicalType								(CXType T)
		17. unsigned 						clang_isConstQualifiedType							(CXType T)
		18. unsigned 						clang_Cursor_isMacroFunctionLike					(CXCursor C)
		19. unsigned 						clang_Cursor_isMacroBuiltin							(CXCursor C)
		20. unsigned 						clang_Cursor_isFunctionInlined						(CXCursor C)
		21. unsigned 						clang_isVolatileQualifiedType						(CXType T)
		22. unsigned 						clang_isRestrictQualifiedType						(CXType T)
		23. unsigned 						clang_getAddressSpace								(CXType T)
		24. CXString 						clang_getTypedefName								(CXType CT)
		25. CXType 							clang_getPointeeType								(CXType T)
		26. CXCursor 						clang_getTypeDeclaration							(CXType T)
		29. CXString 						clang_getTypeKindSpelling							(enum CXTypeKind K)
		30. enum CXCallingConv 				clang_getFunctionTypeCallingConv					(CXType T)
		31. CXType 							clang_getResultType									(CXType T)
		32. int 							clang_getExceptionSpecificationType					(CXType T)

		33. int 							clang_getNumArgTypes								(CXType T)
		34. CXType 							clang_getArgType									(CXType T, unsigned i)

		40. unsigned 						clang_isFunctionTypeVariadic						(CXType T)
		41. CXType 							clang_getCursorResultType							(CXCursor C)
		42. int 							clang_getCursorExceptionSpecificationType			(CXCursor C)
		43. unsigned 						clang_isPODType										(CXType T)
		44. CXType 							clang_getElementType								(CXType T)
		45. long long 						clang_getNumElements								(CXType T)
		46. CXType 							clang_getArrayElementType							(CXType T)
		47. long long 						clang_getArraySize									(CXType T)
		48. CXType 							clang_Type_getNamedType								(CXType T)
		49. unsigned 						clang_Type_isTransparentTagTypedef					(CXType T)
		50. enum CXTypeNullabilityKind 		clang_Type_getNullability							(CXType T)
		51. long long 						clang_Type_getAlignOf								(CXType T)
		52. CXType 							clang_Type_getClassType								(CXType T)
		53. long long 						clang_Type_getSizeOf								(CXType T)
		54. long long 						clang_Type_getOffsetOf								(CXType T, const char *S)
		55. CXType 							clang_Type_getModifiedType							(CXType T)
		56. long long 						clang_Cursor_getOffsetOfField						(CXCursor C)
		57. unsigned 						clang_Cursor_isAnonymous							(CXCursor C)
		58. unsigned 						clang_Cursor_isAnonymousRecordDecl					(CXCursor C)
		59. unsigned 						clang_Cursor_isInlineNamespace						(CXCursor C)

		60. int 							clang_Type_getNumTemplateArguments					(CXType T)
		61. CXType 							clang_Type_getTemplateArgumentAsType				(CXType T, unsigned i)

		62. enum CXRefQualifierKind 		clang_Type_getCXXRefQualifier						(CXType T)
		63. unsigned 						clang_Cursor_isBitField								(CXCursor C)
		64. unsigned 						clang_isVirtualBase									(CXCursor)
		65. enum CX_CXXAccessSpecifier 		clang_getCXXAccessSpecifier							(CXCursor)
		66. enum CX_StorageClass 			clang_Cursor_getStorageClass						(CXCursor)

		67. unsigned 						clang_getNumOverloadedDecls							(CXCursor cursor)
		68. CXCursor 						clang_getOverloadedDecl								(CXCursor cursor, unsigned index)

	Unused:

		ObjC 27. CXString 					clang_getDeclObjCTypeEncoding						(CXCursor C)
		ObjC 28. CXString 					clang_Type_getObjCEncoding							(CXType type)

		ObjC 35. CXType 					clang_Type_getObjCObjectBaseType					(CXType T)

		ObjC 36. unsigned					clang_Type_getNumObjCProtocolRefs					(CXType T);
		ObjC 37. CXCursor					clang_Type_getObjCProtocolDecl						(CXType T, unsigned i)

		ObjC 38. unsigned 					clang_Type_getNumObjCTypeArgs						(CXType T)
		ObjC 39. CXType 					clang_Type_getObjCTypeArg							(CXType T, unsigned i)

		15. unsigned 						clang_equalTypes									(CXType A, CXType B)
		54. long long						clang_Type_getOffsetOf								(CXType T, const char * S)	
    
*/

void _15_printTypeInformationForCXCursors(string& strData, const CXCursor& cursor, uint32_t curLevel);
string _15_CXCursor2String(const CXCursor& cursor);
string _15_CXType2String(const CXType& type);