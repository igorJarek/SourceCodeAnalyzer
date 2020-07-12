#include "StructsEnums2String.h"

string CXString2String(const CXString& string)
{
    std::string out{ "-NULL-" };

    if( string.data)
    {
        out = _11_getCString(string);
        _11_disposeString(string);
    }

    return out;
}

vector<string> CXStringSet2StringVec(CXStringSet* stringSet)
{
    if (stringSet)
    {  
        uint32_t stringSetCount{ stringSet->Count };
        vector<string> out(stringSetCount);

        for (uint32_t index{ 0 }; index < stringSetCount; ++index)
        {
            CXString string = stringSet->Strings[index];
            out.at(index) = move(std::string(_11_getCString(string)));
        }

        _11_disposeStringSet(stringSet);
        return out;
    }

    return {};
}

string CXType2String(const CXType& type)
{
    CXString typeSpelling = _15_getTypeSpelling(type);
    return CXString2String(typeSpelling);
}

string CXDiagnosticSeverity2String(const CXDiagnosticSeverity diagnosticSeverity)
{
    string str;
    switch (diagnosticSeverity)
    {
    case CXDiagnostic_Ignored:
        str += "CXDiagnostic_Ignored";
        break;

    case CXDiagnostic_Note:
        str += "CXDiagnostic_Note";
        break;

    case CXDiagnostic_Warning:
        str += "CXDiagnostic_Warning";
        break;

    case CXDiagnostic_Error:
        str += "CXDiagnostic_Error";
        break;

    case CXDiagnostic_Fatal:
        str += "CXDiagnostic_Fatal";
        break;
    }

    return str;
}

string CXDiagnosticDisplayOptions2String(uint32_t options)
{
    string str;

    if (options & CXDiagnostic_DisplaySourceLocation)
        str += "CXDiagnostic_DisplaySourceLocation | ";

    if (options & CXDiagnostic_DisplayColumn)
        str += "CXDiagnostic_DisplayColumn | ";

    if (options & CXDiagnostic_DisplaySourceRanges)
        str += "CXDiagnostic_DisplaySourceRanges | ";

    if (options & CXDiagnostic_DisplayOption)
        str += "CXDiagnostic_DisplayOption | ";

    if (options & CXDiagnostic_DisplayCategoryId)
        str += "CXDiagnostic_DisplayCategoryId | ";

    if (options & CXDiagnostic_DisplayCategoryName)
        str += "CXDiagnostic_DisplayCategoryName | ";

    str.erase(str.find_last_of("|"));

    return str;
}

string CXSourceLocation2String(const CXSourceLocation sourceLocation, uint32_t offset)
{
    string str;
    CXFile file1, file2;
    uint32_t line1, line2;
    uint32_t column1, column2;
    uint32_t offset1, offset2;

    clang_getExpansionLocation(sourceLocation, &file1, &line1, &column1, &offset1);
    clang_getSpellingLocation(sourceLocation, &file2, &line2, &column2, &offset2);

    str += tabOffset(offset) + "ExpansionLocation : \n";
    str += tabOffset(offset + 1);
    str += "File : " + CXString2String(clang_getFileName(file1)) + ", ";
    str += "Line : " + to_string(line1) + ", ";
    str += "Column : " + to_string(column1) + ", ";
    str += "Offset : " + to_string(offset1) + '\n';

    str += tabOffset(offset) + "SpellingLocation : \n";
    str += tabOffset(offset + 1);
    str += "File : " + CXString2String(clang_getFileName(file2)) + ", ";
    str += "Line : " + to_string(line2) + ", ";
    str += "Column : " + to_string(column2) + ", ";
    str += "Offset : " + to_string(offset2) + '\n';

    return str;
}

string CXSourceRange2String(const CXSourceRange sourceRange, uint32_t offset)
{
    string str;

    CXSourceLocation rangeStart = clang_getRangeStart(sourceRange);
    CXSourceLocation rangeEnd = clang_getRangeEnd(sourceRange);

    str += tabOffset(offset) + "RangeStart : \n";
    str += CXSourceLocation2String(rangeStart, offset + 1);
    str += tabOffset(offset) + "RangeEnd : \n";;
    str += CXSourceLocation2String(rangeEnd, offset + 1);

    return str;
}

string CXTUResourceUsage2String(const CXTUResourceUsage& TUResourceUsage, uint32_t offset)
{
	string str;

	if (TUResourceUsage.numEntries)
	{
		for (uint32_t index{ 0 }; index < TUResourceUsage.numEntries; ++index)
		{
			CXTUResourceUsageEntry resourceUsageEntry = TUResourceUsage.entries[index];
			CXTUResourceUsageKind kind = resourceUsageEntry.kind;
			uint64_t amount = resourceUsageEntry.amount;

			str += tabOffset(offset) + _6_getTUResourceUsageName(kind) + '\n';
			str += tabOffset(offset) + "Amount: " + to_string(amount) + "\n\n";
		}
	}

	return str;
}

string CXErrorCode2String(CXErrorCode errorCode)
{
	switch (errorCode)
	{
		case CXError_Success:
			return "CXError_Success";
		case CXError_Failure:
			return "CXError_Failure";
		case CXError_Crashed:
			return "CXError_Crashed";
		case CXError_InvalidArguments:
			return "CXError_InvalidArguments";
		case CXError_ASTReadError:
			return "CXError_ASTReadError";

		default:
			return "Undefined CXErrorCode";
	}
}

string CXSaveError2String(int32_t saveError)
{
	switch (saveError)
	{
		case CXSaveError_None:
			return "CXSaveError_None";
		case CXSaveError_Unknown:
			return "CXSaveError_Unknown";
		case CXSaveError_TranslationErrors:
			return "CXSaveError_TranslationErrors";
		case CXSaveError_InvalidTU:
			return "CXSaveError_InvalidTU";

		default:
			return "Undefined CXSaveError";
	}
}

string CXTemplateArgumentKind2String(CXTemplateArgumentKind templateArgumentKind)
{
	switch (templateArgumentKind)
	{
		case CXTemplateArgumentKind_Null:
			return "CXTemplateArgumentKind_Null";
		case CXTemplateArgumentKind_Type:
			return "CXTemplateArgumentKind_Type";
		case CXTemplateArgumentKind_Declaration:
			return "CXTemplateArgumentKind_Declaration";
		case CXTemplateArgumentKind_NullPtr:
			return "CXTemplateArgumentKind_NullPtr";
		case CXTemplateArgumentKind_Integral:
			return "CXTemplateArgumentKind_Integral";
		case CXTemplateArgumentKind_Template:
			return "CXTemplateArgumentKind_Template";
		case CXTemplateArgumentKind_TemplateExpansion:
			return "CXTemplateArgumentKind_TemplateExpansion";
		case CXTemplateArgumentKind_Expression:
			return "CXTemplateArgumentKind_Expression";
		case CXTemplateArgumentKind_Pack:
			return "CXTemplateArgumentKind_Pack";
		case CXTemplateArgumentKind_Invalid:
			return "CXTemplateArgumentKind_Invalid";

		default:
			return "Undefined CXTemplateArgumentKind";
	}
	
}

string CXCallingConv2String(CXCallingConv callingConv)
{
	switch (callingConv)
	{
		case CXCallingConv_Default:
			return "CXCallingConv_Default";
		case CXCallingConv_C:
			return "CXCallingConv_C";
		case CXCallingConv_X86StdCall:
			return "CXCallingConv_X86StdCall";
		case CXCallingConv_X86FastCall:
			return "CXCallingConv_X86FastCall";
		case CXCallingConv_X86ThisCall:
			return "CXCallingConv_X86ThisCall";
		case CXCallingConv_X86Pascal:
			return "CXCallingConv_X86Pascal";
		case CXCallingConv_AAPCS:
			return "CXCallingConv_AAPCS";
		case CXCallingConv_AAPCS_VFP:
			return "CXCallingConv_AAPCS_VFP";
		case CXCallingConv_X86RegCall:
			return "CXCallingConv_X86RegCall";
		case CXCallingConv_IntelOclBicc:
			return "CXCallingConv_IntelOclBicc";
		case CXCallingConv_Win64:
			return "CXCallingConv_Win64";
		
		/* OLD API
		case CXCallingConv_X86_64Win64:
			return "CXCallingConv_X86_64Win64";
		*/

		case CXCallingConv_X86_64SysV:
			return "CXCallingConv_X86_64SysV";
		case CXCallingConv_X86VectorCall:
			return "CXCallingConv_X86VectorCall";
		case CXCallingConv_Swift:
			return "CXCallingConv_Swift";
		case CXCallingConv_PreserveMost:
			return "CXCallingConv_PreserveMost";
		case CXCallingConv_PreserveAll:
			return "CXCallingConv_PreserveAll";
		case CXCallingConv_AArch64VectorCall:
			return "CXCallingConv_AArch64VectorCall";
		case CXCallingConv_Invalid:
			return "CXCallingConv_Invalid";
		case CXCallingConv_Unexposed:
			return "CXCallingConv_Unexposed";

		default:
			return "Undefined CXCallingConv";
	}

}

string CXTypeLayoutError2String(CXTypeLayoutError typeLayoutError)
{
	switch (typeLayoutError)
	{
		case CXTypeLayoutError_Invalid:
			return "CXTypeLayoutError_Invalid";
		case CXTypeLayoutError_Incomplete:
			return "CXTypeLayoutError_Incomplete";
		case CXTypeLayoutError_Dependent:
			return "CXTypeLayoutError_Dependent";
		case CXTypeLayoutError_NotConstantSize:
			return "CXTypeLayoutError_NotConstantSize";
		case CXTypeLayoutError_InvalidFieldName:
			return "CXTypeLayoutError_InvalidFieldName";
		case CXTypeLayoutError_Undeduced:
			return "CXTypeLayoutError_Undeduced";

		default:
			return "Undefined CXTypeLayoutError";
	}
}

string CXTypeNullabilityKind2String(CXTypeNullabilityKind typeNullabilityKind)
{
	switch (typeNullabilityKind)
	{
		case CXTypeNullability_NonNull:
			return "CXTypeNullability_NonNull";
		case CXTypeNullability_Nullable:
			return "CXTypeNullability_Nullable ";
		case CXTypeNullability_Unspecified:
			return "CXTypeNullability_Unspecified";
		case CXTypeNullability_Invalid:
			return "CXTypeNullability_Invalid";

		default:
			return "Undefined CXTypeNullabilityKind";
	}
}

string CXRefQualifierKind2String(const CXRefQualifierKind refQualifierKind)
{
	switch (refQualifierKind)
	{
		case CXRefQualifier_None:
			return "CXRefQualifier_None";
		case CXRefQualifier_LValue:
			return "CXRefQualifier_LValue";
		case CXRefQualifier_RValue:
			return "CXRefQualifier_RValue";

		default:
			return "Undefined CXRefQualifierKind";
	}
}

string CX_CXXAccessSpecifier2String(const CX_CXXAccessSpecifier accessSpecifier)
{
	switch (accessSpecifier)
	{
		case CX_CXXInvalidAccessSpecifier:
			return "CX_CXXInvalidAccessSpecifier";
		case CX_CXXPublic:
			return "CX_CXXPublic";
		case CX_CXXProtected:
			return "CX_CXXProtected";
		case CX_CXXPrivate:
			return "CX_CXXPrivate";

		default:
			return "Undefined CX_CXXAccessSpecifier";
	}
}

string CX_StorageClass2String(const CX_StorageClass storageClass)
{
	switch (storageClass)
	{
		case CX_SC_Invalid:
			return "CX_SC_Invalid";
		case CX_SC_None:
			return "CX_SC_None";
		case CX_SC_Extern:
			return "CX_SC_Extern";
		case CX_SC_Static:
			return "CX_SC_Static";
		case CX_SC_PrivateExtern:
			return "CX_SC_PrivateExtern";
		case CX_SC_OpenCLWorkGroupLocal:
			return "CX_SC_OpenCLWorkGroupLocal";
		case CX_SC_Auto:
			return "CX_SC_Auto";
		case CX_SC_Register:
			return "CX_SC_Register";

		default:
			return "Undefined CX_StorageClass";
	}
}

string CXTokenKind2String(const CXTokenKind tokenKind)
{
	switch (tokenKind)
	{
		case CXToken_Punctuation:
			return "CXToken_Punctuation";
		case CXToken_Keyword:
			return "CXToken_Keyword\t";
		case CXToken_Identifier:
			return "CXToken_Identifier";
		case CXToken_Literal:
			return "CXToken_Literal\t";
		case CXToken_Comment:
			return "CXToken_Comment";

		default:
			return "Undefined CXTokenKind";
	}
}

string CXPrintingPolicy2String(const CXPrintingPolicy printingPolicy, uint32_t offset)
{
	PrintingPolicy* pp = reinterpret_cast<PrintingPolicy*>(printingPolicy);
	string str;

	uint32_t indentation							= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_Indentation);
	uint32_t suppressSpecifiers						= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_SuppressSpecifiers);
	uint32_t suppressTagKeyword						= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_SuppressTagKeyword);
	uint32_t includeTagDefinition					= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_IncludeTagDefinition);
	uint32_t suppressScope							= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_SuppressScope);
	uint32_t suppressUnwrittenScope					= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_SuppressUnwrittenScope);
	uint32_t suppressInitializers					= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_SuppressInitializers);
	uint32_t constantArraySizeAsWritten				= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_ConstantArraySizeAsWritten);
	uint32_t anonymousTagLocations					= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_AnonymousTagLocations);
	uint32_t suppressStrongLifetime					= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_SuppressStrongLifetime);
	uint32_t suppressLifetimeQualifiers				= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_SuppressLifetimeQualifiers);
	uint32_t suppressTemplateArgsInCXXConstructors	= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_SuppressTemplateArgsInCXXConstructors);
	uint32_t boolean								= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_Bool);
	uint32_t restrict								= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_Restrict);
	uint32_t alignOf								= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_Alignof);
	uint32_t underscoreAlignof						= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_UnderscoreAlignof);
	uint32_t useVoidForZeroParams					= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_UseVoidForZeroParams);
	uint32_t terseOutput							= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_TerseOutput);
	uint32_t polishForDeclaration					= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_PolishForDeclaration);
	uint32_t half									= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_Half);
	uint32_t mswChar								= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_MSWChar);
	uint32_t includeNewlines						= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_IncludeNewlines);
	uint32_t mSVCFormatting							= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_MSVCFormatting);
	uint32_t constantsAsWritten						= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_ConstantsAsWritten);
	uint32_t suppressImplicitBase					= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_SuppressImplicitBase);
	uint32_t fullyQualifiedName						= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_FullyQualifiedName);
	uint32_t lastProperty							= clang_PrintingPolicy_getProperty(pp, CXPrintingPolicyProperty::CXPrintingPolicy_LastProperty);

	str += tabOffset(offset) +		"CXPrintingPolicy : \n";

	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_Indentation) : "								+ to_string(indentation)							+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_SuppressSpecifiers) : "						+ to_string(suppressSpecifiers)						+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_SuppressTagKeyword) : "						+ to_string(suppressTagKeyword)						+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_IncludeTagDefinition) : "					+ to_string(includeTagDefinition)					+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_SuppressScope) : "							+ to_string(suppressScope)							+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_SuppressUnwrittenScope) : "					+ to_string(suppressUnwrittenScope)					+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_SuppressInitializers) : "					+ to_string(suppressInitializers)					+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_ConstantArraySizeAsWritten) : "				+ to_string(constantArraySizeAsWritten)				+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_AnonymousTagLocations) : "					+ to_string(anonymousTagLocations)					+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_SuppressStrongLifetime) : "					+ to_string(suppressStrongLifetime)					+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_SuppressLifetimeQualifiers) : "				+ to_string(suppressLifetimeQualifiers)				+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_SuppressTemplateArgsInCXXConstructors) : "	+ to_string(suppressTemplateArgsInCXXConstructors)	+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_Bool) : "									+ to_string(boolean)								+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_Restrict) : "								+ to_string(restrict)								+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_Alignof) : "									+ to_string(alignOf)								+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_UnderscoreAlignof) : "						+ to_string(underscoreAlignof)						+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_UseVoidForZeroParams) : "					+ to_string(useVoidForZeroParams)					+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_TerseOutput) : "								+ to_string(terseOutput)							+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_PolishForDeclaration) : "					+ to_string(polishForDeclaration)					+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_Half) : "									+ to_string(half)									+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_MSWChar) : "									+ to_string(mswChar)								+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_IncludeNewlines) : "							+ to_string(includeNewlines)						+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_MSVCFormatting) : "							+ to_string(mSVCFormatting)							+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_ConstantsAsWritten) : "						+ to_string(constantsAsWritten)						+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_SuppressImplicitBase) : "					+ to_string(suppressImplicitBase)					+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_FullyQualifiedName) : "						+ to_string(fullyQualifiedName)						+ '\n';
	str += tabOffset(offset + 1) +	"clang_PrintingPolicy_getProperty(CXPrintingPolicy_LastProperty) : "							+ to_string(lastProperty)							+ '\n';

	return str;
}

string CXEvalResultKind2String (const CXEvalResultKind evalResultKind)
{
    switch (evalResultKind)
    {
        case CXEval_Int:
            return "CXEval_Int";
        case CXEval_Float:
            return "CXEval_Float";
        case CXEval_ObjCStrLiteral:
            return "CXEval_ObjCStrLiteral";
        case CXEval_StrLiteral:
            return "CXEval_StrLiteral";
        case CXEval_CFStr:
            return "CXEval_CFStr";
        case CXEval_Other:
            return "CXEval_Other";
        case CXEval_UnExposed:
            return "CXEval_UnExposed";

        default:
            return "Undefined CXEvalResultKind";
    }
}

string CXLinkageKind2String(const CXLinkageKind linkageKind)
{
    switch (linkageKind)
    {
        case CXLinkage_Invalid:
            return "CXLinkage_Invalid";
        case CXLinkage_NoLinkage:
            return "CXLinkage_NoLinkage";
        case CXLinkage_Internal:
            return "CXLinkage_Internal";
        case CXLinkage_UniqueExternal:
            return "CXLinkage_UniqueExternal";
        case CXLinkage_External:
            return "CXLinkage_External";

        default:
            return "Undefined CXLinkageKind";
    }
}

string CXVisibilityKind2String(const CXVisibilityKind visibilityKind)
{
    switch (visibilityKind)
    {
        case CXVisibility_Invalid:
            return "CXVisibility_Invalid";
        case CXVisibility_Hidden:
            return "CXVisibility_Hidden";
        case CXVisibility_Protected:
            return "CXVisibility_Protected";
        case CXVisibility_Default:
            return "CXVisibility_Default";

        default:
            return "Undefined CXVisibilityKind";
    }
}

string CXAvailabilityKind2String(const CXAvailabilityKind availabilityKind)
{
    switch (availabilityKind)
    {
        case CXAvailability_Available:
            return "CXAvailability_Available";
        case CXAvailability_Deprecated:
            return "CXAvailability_Deprecated";
        case CXAvailability_NotAvailable:
            return "CXAvailability_NotAvailable";
        case CXAvailability_NotAccessible:
            return "CXAvailability_NotAccessible";

        default:
            return "Undefined CXAvailabilityKind";
    }
}

string CXVersion2String(const CXVersion version, uint32_t offset)
{
    string str;

    str += tabOffset(offset) + "Major : "    + to_string(version.Major)    + ", ";
    str += tabOffset(offset) + "Minor : "    + to_string(version.Minor)    + ", ";
    str += tabOffset(offset) + "Subminor : " + to_string(version.Subminor);

    return str;
}

string CXPlatformAvailability2String(const CXPlatformAvailability platformAvailability, uint32_t offset)
{
    string str;

    CXString  platform    = platformAvailability.Platform;
    CXVersion introduced  = platformAvailability.Introduced;
    CXVersion deprecated  = platformAvailability.Deprecated;
    CXVersion obsoleted   = platformAvailability.Obsoleted;
    int32_t   unavailable = platformAvailability.Unavailable;
    CXString  message     = platformAvailability.Message;

    str += tabOffset(offset) + "Platform : "    + CXString2String(platform)   + '\n';
    str += tabOffset(offset) + "Introduced : "  + CXVersion2String(introduced, 0) + '\n';
    str += tabOffset(offset) + "Deprecated : "  + CXVersion2String(deprecated, 0) + '\n';
    str += tabOffset(offset) + "Obsoleted : "   + CXVersion2String(obsoleted,  0) + '\n';
    str += tabOffset(offset) + "Unavailable : " + to_string(unavailable)          + '\n';
    str += tabOffset(offset) + "Message : "     + CXString2String(message)    + '\n';

	return str;
}

string CXLanguageKind2String(const CXLanguageKind languageKind)
{
    switch (languageKind)
    {
        case CXLanguage_Invalid:
            return "CXLanguage_Invalid";
        case CXLanguage_C:
            return "CXLanguage_C";
        case CXLanguage_ObjC:
            return "CXLanguage_ObjC";
        case CXLanguage_CPlusPlus:
            return "CXLanguage_CPlusPlus";

        default:
            return "Undefined CXLanguageKind";
    }
}

string CXTLSKind2String(const CXTLSKind LSKind)
{
    switch (LSKind)
    {
        case CXTLS_None:
            return "CXTLS_None";
        case CXTLS_Dynamic:
            return "CXTLS_Dynamic";
        case CXTLS_Static:
            return "CXTLS_Static";

        default:
            return "Undefined CXTLSKind";
    }
}

string CXCommentKind2String(const CXCommentKind commentKind)
{
    switch (commentKind)
    {
        case CXComment_Null:
            return "CXComment_Null";
        case CXComment_Text:
            return "CXComment_Text";
        case CXComment_InlineCommand:
            return "CXComment_InlineCommand";
        case CXComment_HTMLStartTag:
            return "CXComment_HTMLStartTag";
        case CXComment_HTMLEndTag:
            return "CXComment_HTMLEndTag";
        case CXComment_Paragraph:
            return "CXComment_Paragraph";
        case CXComment_BlockCommand:
            return "CXComment_BlockCommand";
        case CXComment_ParamCommand:
            return "CXComment_ParamCommand";
        case CXComment_TParamCommand:
            return "CXComment_TParamCommand";
        case CXComment_VerbatimBlockCommand:
            return "CXComment_VerbatimBlockCommand";
        case CXComment_VerbatimBlockLine:
            return "CXComment_VerbatimBlockLine";
        case CXComment_VerbatimLine:
            return "CXComment_VerbatimLine";
        case CXComment_FullComment:
            return "CXComment_FullComment";

        default:
            return "Undefined CXCommentKind";
    }
}

string CXCommentInlineCommandRenderKind2String(const CXCommentInlineCommandRenderKind commentInlineCommandRenderKind)
{
    switch (commentInlineCommandRenderKind)
    {
        case CXCommentInlineCommandRenderKind_Normal:
            return "CXCommentInlineCommandRenderKind_Normal";
        case CXCommentInlineCommandRenderKind_Bold:
            return "CXCommentInlineCommandRenderKind_Bold";
        case CXCommentInlineCommandRenderKind_Monospaced:
            return "CXCommentInlineCommandRenderKind_Monospaced";
        case CXCommentInlineCommandRenderKind_Emphasized:
            return "CXCommentInlineCommandRenderKind_Emphasized";
        case CXCommentInlineCommandRenderKind_Anchor:
            return "CXCommentInlineCommandRenderKind_Anchor";

        default:
            return "Undefined CXCommentInlineCommandRenderKind";
    }
}

string CXCommentParamPassDirection2String(const CXCommentParamPassDirection commentParamPassDirection)
{
    switch (commentParamPassDirection)
    {
        case CXCommentParamPassDirection_In:
            return "CXCommentParamPassDirection_In";
        case CXCommentParamPassDirection_Out:
            return "CXCommentParamPassDirection_Out";
        case CXCommentParamPassDirection_InOut:
            return "CXCommentParamPassDirection_InOut";

        default:
            return "Undefined CXCommentParamPassDirection";
    }
}