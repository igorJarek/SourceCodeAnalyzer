#pragma once

#include <clang-c/Index.h>
#include <clang-c/Documentation.h>
#include "11_String_manipulation_routines.h"
#include "6_Translation_unit_manipulation.h"
#include "UtilityFunctions.h"
#include <string>
#include <ostream>

using namespace std;

string CXString2String							(const CXString& string);
vector<string> CXStringSet2StringVec			(CXStringSet* stringSet);

string CXType2String							(const CXType& type);

string CXDiagnosticSeverity2String				(const CXDiagnosticSeverity diagnosticSeverity);
string CXDiagnosticDisplayOptions2String		(uint32_t options);

string CXSourceLocation2String					(const CXSourceLocation sourceLocation,		uint32_t offset);
string CXSourceRange2String						(const CXSourceRange sourceRange,			uint32_t offset);

string CXTUResourceUsage2String					(const CXTUResourceUsage& TUResourceUsage,	uint32_t offset);
string CXErrorCode2String						(CXErrorCode errorCode);
string CXSaveError2String						(int32_t saveError);

string CXTemplateArgumentKind2String			(CXTemplateArgumentKind templateArgumentKind);
string CXCallingConv2String						(CXCallingConv callingConv);
string CXTypeLayoutError2String					(CXTypeLayoutError typeLayoutError);
string CXTypeNullabilityKind2String				(CXTypeNullabilityKind typeNullabilityKind);
string CXRefQualifierKind2String				(const CXRefQualifierKind refQualifierKind);
string CX_CXXAccessSpecifier2String				(const CX_CXXAccessSpecifier accessSpecifier);
string CX_StorageClass2String					(const CX_StorageClass storageClass);
string CXTokenKind2String						(const CXTokenKind tokenKind);
string CXPrintingPolicy2String					(const CXPrintingPolicy printingPolicy, uint32_t offset);
string CXEvalResultKind2String					(const CXEvalResultKind evalResultKind);
string CXLinkageKind2String						(const CXLinkageKind linkageKind);
string CXVisibilityKind2String					(const CXVisibilityKind visibilityKind);
string CXAvailabilityKind2String				(const CXAvailabilityKind availabilityKind);
string CXVersion2String							(const CXVersion version, uint32_t offset);
string CXPlatformAvailability2String			(const CXPlatformAvailability platformAvailability, uint32_t offset);
string CXLanguageKind2String					(const CXLanguageKind languageKind);
string CXTLSKind2String							(const CXTLSKind LSKind);
string CXCommentKind2String						(const CXCommentKind commentKind);
string CXCommentInlineCommandRenderKind2String	(const CXCommentInlineCommandRenderKind commentInlineCommandRenderKind);
string CXCommentParamPassDirection2String		(const CXCommentParamPassDirection commentParamPassDirection);
