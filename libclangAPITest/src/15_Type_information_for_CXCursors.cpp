#include "15_Type_information_for_CXCursors.h"

void _15_printTypeInformationForCXCursors(string& strData, const CXCursor& cursor, uint32_t curLevel)
{
	CXType						cursorType								= clang_getCursorType							(cursor);							// 1
	CXString					typeSpelling							= clang_getTypeSpelling							(cursorType);						// 2.

	if (cursorType.kind == CXType_Invalid || cursorType.kind == CXType_Unexposed)
	{
		strData += tabOffset(curLevel + 1) + "Type information for CXCursors : \n";
		strData += tabOffset(curLevel + 2) + "clang_getTypeSpelling : " + _11_CXString2String(typeSpelling) + '\n';

		return;
	}
	
	CXType						typedefDeclUnderlyingType				= clang_getTypedefDeclUnderlyingType			(cursor);							// 3.
	CXType						enumDeclIntegerType						= clang_getEnumDeclIntegerType					(cursor);							// 4.
	int64_t						enumConstantDeclValue					= clang_getEnumConstantDeclValue				(cursor);							// 5.
	uint64_t					enumConstantDeclUnsignedValue			= clang_getEnumConstantDeclUnsignedValue		(cursor);							// 6.
	int32_t						fieldDeclBitWidth						= clang_getFieldDeclBitWidth					(cursor);							// 7.

	int32_t						numArguments							= clang_Cursor_getNumArguments					(cursor);							// 8.
	vector<string>				getArgumentStrings;
	for (int32_t index{ 0 };	index < numArguments;					++index)
	{
		CXCursor				cursor_getArgument						= clang_Cursor_getArgument						(cursor, index);					// 9.
		getArgumentStrings.push_back(_15_CXCursor2String(cursor_getArgument));
	}
	
	int32_t						cursorNumTemplateArguments				= clang_Cursor_getNumTemplateArguments			(cursor);							// 10.
	vector<string>				templateArgumentKindStrings;
	vector<string>				templateArgumentTypeStrings;
	vector<string>				templateArgumentValueStrings;
	vector<string>				templateArgumentUnsignedValueStrings;
	for (int32_t index{ 0 };	index < cursorNumTemplateArguments;		++index)
	{
		CXTemplateArgumentKind	templateArgumentKind					= clang_Cursor_getTemplateArgumentKind			(cursor, index);					// 11.
								templateArgumentKindStrings.push_back(CXTemplateArgumentKind2String(templateArgumentKind));

		CXType					templateArgumentType					= clang_Cursor_getTemplateArgumentType			(cursor, index);					// 12.
								templateArgumentTypeStrings.push_back(_15_CXType2String(templateArgumentType));

		int64_t					templateArgumentValue					= clang_Cursor_getTemplateArgumentValue			(cursor, index);					// 13.
								templateArgumentValueStrings.push_back(to_string(templateArgumentValue));

		uint64_t				templateArgumentUnsignedValue			= clang_Cursor_getTemplateArgumentUnsignedValue	(cursor, index);					// 14.
								templateArgumentUnsignedValueStrings.push_back(to_string(templateArgumentUnsignedValue));
	}

	CXType						canonicalType							= clang_getCanonicalType						(cursorType);						// 16.
	uint32_t					isConstQualifiedType					= clang_isConstQualifiedType					(cursorType);						// 17.
	uint32_t 					isMacroFunctionLike						= clang_Cursor_isMacroFunctionLike				(cursor);							// 18.
	uint32_t 					isMacroBuiltin							= clang_Cursor_isMacroBuiltin					(cursor);							// 19.
	uint32_t 					isFunctionInlined						= clang_Cursor_isFunctionInlined				(cursor);							// 20.
	uint32_t 					isVolatileQualifiedType					= clang_isVolatileQualifiedType					(cursorType);						// 21.
	uint32_t 					isRestrictQualifiedType					= clang_isRestrictQualifiedType					(cursorType);						// 22.
	uint32_t 					getAddressSpace							= clang_getAddressSpace							(cursorType);						// 23.

	CXString 					getTypedefName							= clang_getTypedefName							(cursorType);						// 24.
	CXType 						getPointeeType							= clang_getPointeeType							(cursorType);						// 25.
	CXCursor 					getTypeDeclaration						= clang_getTypeDeclaration						(cursorType);						// 26.
	CXString 					typeKindSpelling						= clang_getTypeKindSpelling						(cursorType.kind);					// 29.

	CXCallingConv				functionTypeCallingConv					= clang_getFunctionTypeCallingConv				(cursorType);						// 30.
	CXType						resultType								= clang_getResultType							(cursorType);						// 31.
	int32_t						exceptionSpecificationType				= clang_getExceptionSpecificationType			(cursorType);						// 32.

	int32_t						numArgTypes								= clang_getNumArgTypes							(cursorType);						// 33.
	vector<string>				argTypeStrings;
	for (int32_t index{ 0 };	index < numArgTypes;					++index)
	{
		CXType					argType									= clang_getArgType								(cursorType, index);				// 34.
								argTypeStrings.push_back(_15_CXType2String(argType));
	}

	uint32_t					isFunctionTypeVariadic					= clang_isFunctionTypeVariadic					(cursorType);						// 40.
	CXType 						cursorResultType						= clang_getCursorResultType						(cursor);							// 41.
	int32_t 					cursorExceptionSpecificationType		= clang_getCursorExceptionSpecificationType		(cursor);							// 42.
	uint32_t 					isPODType								= clang_isPODType								(cursorType);						// 43.
	CXType 						elementType								= clang_getElementType							(cursorType);						// 44.
	int64_t 					numElements 							= clang_getNumElements							(cursorType); 						// 45.
	CXType 						arrayElementType						= clang_getArrayElementType						(cursorType); 						// 46.
	int64_t 					arraySize								= clang_getArraySize							(cursorType); 						// 47.
	CXType 						namedType								= clang_Type_getNamedType						(cursorType); 						// 48.
	uint32_t 					isTransparentTagTypedef					= clang_Type_isTransparentTagTypedef			(cursorType); 						// 49.

	CXTypeNullabilityKind		getNullability							= clang_Type_getNullability						(cursorType);						// 50.

	int64_t						alignOf									= clang_Type_getAlignOf							(cursorType);						// 51.
	CXType						classType								= clang_Type_getClassType						(cursorType);						// 52.
	int64_t						sizeOf									= clang_Type_getSizeOf							(cursorType);						// 53.

	CXType						modifiedType							= clang_Type_getModifiedType					(cursorType);						// 55.
	int64_t						offsetOfField							= clang_Cursor_getOffsetOfField					(cursor);							// 56.
	uint32_t					isAnonymous								= clang_Cursor_isAnonymous						(cursor);							// 57.
	uint32_t 					isAnonymousRecordDecl					= clang_Cursor_isAnonymousRecordDecl			(cursor);							// 58.
	uint32_t 					isInlineNamespace						= clang_Cursor_isInlineNamespace				(cursor);							// 59.
	
	int32_t						typeNumTemplateArguments				= clang_Type_getNumTemplateArguments			(cursorType);						// 60.
	vector<string>				templateArgumentAsTypeStrings;
	for (int32_t index{ 0 };	index < typeNumTemplateArguments;		++index)
	{
		CXType					templateArgumentAsType					= clang_Type_getTemplateArgumentAsType			(cursorType, index);				// 61.
								templateArgumentAsTypeStrings.push_back(_15_CXType2String(templateArgumentAsType));
	}
	
	CXRefQualifierKind			refQualifier							= clang_Type_getCXXRefQualifier					(cursorType);						// 62.
	int32_t						isBitField								= clang_Cursor_isBitField						(cursor);							// 63.
	int32_t						isVirtualBase							= clang_isVirtualBase							(cursor);							// 64.
	CX_CXXAccessSpecifier		accessSpecifier							= clang_getCXXAccessSpecifier					(cursor);							// 65.
	CX_StorageClass				storageClass							= clang_Cursor_getStorageClass					(cursor);							// 66.

	uint32_t					numOverloadedDecls						= clang_getNumOverloadedDecls					(cursor);							// 67.
	vector<string>				overloadedDeclStrings(numOverloadedDecls);
	for (uint32_t index{ 0 };	index < numOverloadedDecls;				++index)
	{
		CXCursor				overloadedDecl							= clang_getOverloadedDecl						(cursor, index);					// 68.
								overloadedDeclStrings.at(index)			= move(_15_CXCursor2String(overloadedDecl));
	}
	
	// Print data //

	strData += tabOffset(curLevel + 1) + "Type information for CXCursors : \n";

	strData += tabOffset(curLevel + 2) + "clang_getTypeSpelling : "						+ _11_CXString2String(typeSpelling)				+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_getTypedefDeclUnderlyingType : "		+ _15_CXType2String(typedefDeclUnderlyingType)	+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_getEnumDeclIntegerType : "				+ _15_CXType2String(enumDeclIntegerType)		+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_getEnumConstantDeclValue : "			+ to_string(enumConstantDeclValue)				+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_getEnumConstantDeclUnsignedValue : "	+ to_string(enumConstantDeclUnsignedValue)		+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_getFieldDeclBitWidth : "				+ to_string(fieldDeclBitWidth)					+ '\n';

	strData += tabOffset(curLevel + 2) + "clang_Cursor_getNumArguments : "				+ to_string(numArguments)						+ '\n';
	for(string str : getArgumentStrings)
		strData += tabOffset(curLevel + 3) + "clang_Cursor_getArgument : " + str + "\n\n";

	strData += tabOffset(curLevel + 2) + "clang_Cursor_getNumTemplateArguments : "		+ to_string(cursorNumTemplateArguments)			+ '\n';
	for (int32_t index{ 0 }; index < cursorNumTemplateArguments; ++index)
	{
		strData += tabOffset(curLevel + 3) + "clang_Cursor_getTemplateArgumentKind : "	+ templateArgumentKindStrings[index]			+'\n';
		strData += tabOffset(curLevel + 3) + "clang_Cursor_getTemplateArgumentType : "	+ templateArgumentTypeStrings[index]			+'\n';
		strData += tabOffset(curLevel + 3) + "clang_Cursor_getTemplateArgumentValue : " + templateArgumentValueStrings[index]			+'\n';
		strData += tabOffset(curLevel + 3) + "clang_Cursor_getTemplateArgumentUnsignedValue : " + templateArgumentUnsignedValueStrings[index] + "\n\n";
	}

	strData += tabOffset(curLevel + 2) + "clang_getCanonicalType : "					+ _15_CXType2String(canonicalType)				+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_isConstQualifiedType : "				+ to_string(isConstQualifiedType)				+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_Cursor_isMacroFunctionLike : "			+ to_string(isMacroFunctionLike)				+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_Cursor_isMacroBuiltin : "				+ to_string(isMacroBuiltin)						+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_Cursor_isFunctionInlined : "			+ to_string(isFunctionInlined)					+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_isVolatileQualifiedType : "				+ to_string(isVolatileQualifiedType)			+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_isRestrictQualifiedType : "				+ to_string(isRestrictQualifiedType)			+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_getAddressSpace : "						+ to_string(getAddressSpace)					+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_getTypedefName : "						+ _11_CXString2String(getTypedefName)			+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_getPointeeType : "						+ _15_CXType2String(getPointeeType)				+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_getTypeDeclaration : "					+ _15_CXCursor2String(getTypeDeclaration)		+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_getTypeKindSpelling : "					+ _11_CXString2String(typeKindSpelling)			+ '\n';

	strData += tabOffset(curLevel + 2) + "clang_getFunctionTypeCallingConv : "			+ CXCallingConv2String(functionTypeCallingConv) + '\n';
	strData += tabOffset(curLevel + 2) + "clang_getResultType : "						+ _15_CXType2String(resultType)					+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_getExceptionSpecificationType : "		+ to_string(exceptionSpecificationType)			+ '\n';

	strData += tabOffset(curLevel + 2) + "clang_getNumArgTypes : "						+ to_string(numArgTypes)						+ '\n';
	for(string str : argTypeStrings)
		strData += tabOffset(curLevel + 3) + "clang_getArgType : " + str + '\n';

	strData += tabOffset(curLevel + 2) + "clang_isFunctionTypeVariadic : "				+ to_string(isFunctionTypeVariadic)				+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_getCursorResultType : "					+ _15_CXType2String(cursorResultType)			+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_getCursorExceptionSpecificationType : " + to_string(cursorExceptionSpecificationType)	+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_isPODType : "							+ to_string(isPODType)							+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_getElementType : "						+ _15_CXType2String(elementType)				+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_getNumElements : "						+ to_string(numElements)						+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_getArrayElementType : "					+ _15_CXType2String(arrayElementType)			+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_getArraySize : "						+ to_string(arraySize)							+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_Type_getNamedType : "					+ _15_CXType2String(namedType)					+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_Type_isTransparentTagTypedef : "		+ to_string(isTransparentTagTypedef)			+ '\n';

	strData += tabOffset(curLevel + 2) + "clang_Type_getNullability : "					+ CXTypeNullabilityKind2String(getNullability)	+ '\n';

	strData += tabOffset(curLevel + 2) + "clang_Type_getAlignOf : "						+ to_string(alignOf)							+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_Type_getClassType : "					+ _15_CXType2String(classType)					+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_Type_getSizeOf : "						+ to_string(sizeOf)								+ '\n';

	strData += tabOffset(curLevel + 2) + "clang_Type_getModifiedType : "				+ _15_CXType2String(modifiedType)				+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_Cursor_getOffsetOfField : "				+ to_string(offsetOfField)						+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_Cursor_isAnonymous : "					+ to_string(isAnonymous)						+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_Cursor_isAnonymousRecordDecl : "		+ to_string(isAnonymousRecordDecl)				+ '\n';
	strData += tabOffset(curLevel + 2) + "clang_Cursor_isInlineNamespace : "			+ to_string(isInlineNamespace)					+ '\n';

	strData += tabOffset(curLevel + 2) + "clang_Type_getNumTemplateArguments : "		+ to_string(typeNumTemplateArguments)			+ '\n';
	for (string str : templateArgumentAsTypeStrings)
		strData += tabOffset(curLevel + 3) + "clang_Type_getTemplateArgumentAsType : " + str + '\n';
	
	strData += tabOffset(curLevel + 2) + "clang_Type_getCXXRefQualifier : "				+ CXRefQualifierKind2String(refQualifier) + '\n';
	strData += tabOffset(curLevel + 2) + "clang_Cursor_isBitField : "					+ to_string(isBitField) + '\n';
	strData += tabOffset(curLevel + 2) + "clang_isVirtualBase : "						+ to_string(isVirtualBase) + '\n';
	strData += tabOffset(curLevel + 2) + "clang_getCXXAccessSpecifier : "				+ CX_CXXAccessSpecifier2String(accessSpecifier) + '\n';
	strData += tabOffset(curLevel + 2) + "clang_Cursor_getStorageClass : "				+ CX_StorageClass2String(storageClass) + '\n';
	
	strData += tabOffset(curLevel + 2) + "clang_getNumOverloadedDecls : " + to_string(numOverloadedDecls) + '\n';
	for (string str : overloadedDeclStrings)
		strData += tabOffset(curLevel + 3) + "clang_getOverloadedDecl : " + str + '\n';
}

string _15_CXCursor2String(const CXCursor& cursor)
{
	CXType cursorType = clang_getCursorType (cursor); // 1.
	return _15_CXType2String(cursorType);
}

string _15_CXType2String(const CXType& type)
{
	CXString typeSpelling = clang_getTypeSpelling (type); // 2.
	return _11_CXString2String(typeSpelling);
}