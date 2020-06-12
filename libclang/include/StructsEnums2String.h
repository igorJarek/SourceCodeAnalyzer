#pragma once

#include <clang-c/Index.h>
#include "11_String_manipulation_routines.h"
#include "6_Translation_unit_manipulation.h"
#include "UtilityFunctions.h"
#include <string>
#include <ostream>

using namespace std;

string CXDiagnosticSeverity2String			(const CXDiagnosticSeverity diagnosticSeverity);
string CXDiagnosticDisplayOptions2String	(uint32_t options);

string CXSourceLocation2String				(const CXSourceLocation sourceLocation,		uint32_t offset);
string CXSourceRange2String					(const CXSourceRange sourceRange,			uint32_t offset);

string CXCursorKind2String					(CXCursorKind cursorKind);

string CXTUResourceUsage2String				(const CXTUResourceUsage& TUResourceUsage,	uint32_t offset);
string CXErrorCode2String					(CXErrorCode errorCode);
string CXSaveError2String					(int32_t saveError);

string CXTemplateArgumentKind2String		(CXTemplateArgumentKind templateArgumentKind);
string CXCallingConv2String					(CXCallingConv callingConv);
string CXTypeLayoutError2String				(CXTypeLayoutError typeLayoutError);
string CXTypeNullabilityKind2String			(CXTypeNullabilityKind typeNullabilityKind);
string CXRefQualifierKind2String			(const CXRefQualifierKind refQualifierKind);
string CX_CXXAccessSpecifier2String			(const CX_CXXAccessSpecifier accessSpecifier);
string CX_StorageClass2String				(const CX_StorageClass storageClass);
string CXTokenKind2String					(const CXTokenKind tokenKind);
string CXPrintingPolicy2String				(const CXPrintingPolicy printingPolicy, uint32_t offset);
string CXEvalResultKind2String				(const CXEvalResultKind evalResultKind);
