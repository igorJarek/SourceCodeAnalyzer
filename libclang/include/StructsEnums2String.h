#pragma once

#include <clang-c/Index.h>
#include <clang-c/Documentation.h>
#include "11_String_manipulation_routines.h"
#include "6_Translation_unit_manipulation.h"
#include "UtilityFunctions.h"
#include <string>
#include <ostream>

using std::vector;
using std::to_string;
using std::string;

// Only one function produced std::vector
vector<string> CXStringSet2StringVec            (CXStringSet*                             stringSet);

// Simple structure functions
string CXString2String                          (const CXString&                          string);
string CXType2String                            (const CXType&                            type);
string CXDiagnosticSeverity2String              (const CXDiagnosticSeverity&              diagnosticSeverity);
string CXDiagnosticDisplayOptions2String        (const uint32_t&                          options);
string CXErrorCode2String                       (const CXErrorCode&                       errorCode);
string CXSaveError2String                       (const int32_t&                           saveError);
string CXTemplateArgumentKind2String            (const CXTemplateArgumentKind&            templateArgumentKind);
string CXCallingConv2String                     (const CXCallingConv&                     callingConv);
string CXTypeLayoutError2String                 (const CXTypeLayoutError&                 typeLayoutError);
string CXTypeNullabilityKind2String             (const CXTypeNullabilityKind&             typeNullabilityKind);
string CXRefQualifierKind2String                (const CXRefQualifierKind&                refQualifierKind);
string CX_CXXAccessSpecifier2String             (const CX_CXXAccessSpecifier&             accessSpecifier);
string CX_StorageClass2String                   (const CX_StorageClass&                   storageClass);
string CXTokenKind2String                       (const CXTokenKind&                       tokenKind);
string CXEvalResultKind2String                  (const CXEvalResultKind&                  evalResultKind);
string CXLinkageKind2String                     (const CXLinkageKind&                     linkageKind);
string CXVisibilityKind2String                  (const CXVisibilityKind&                  visibilityKind);
string CXAvailabilityKind2String                (const CXAvailabilityKind&                availabilityKind);
string CXLanguageKind2String                    (const CXLanguageKind&                    languageKind);
string CXTLSKind2String                         (const CXTLSKind&                         LSKind);
string CXCommentKind2String                     (const CXCommentKind&                     commentKind);
string CXCommentInlineCommandRenderKind2String  (const CXCommentInlineCommandRenderKind&  commentInlineCommandRenderKind);
string CXCommentParamPassDirection2String       (const CXCommentParamPassDirection&       commentParamPassDirection);

// Complex structure functions
string CXSourceLocation2String                  (const CXSourceLocation&                  sourceLocation,                        const uint32_t offset);
string CXSourceRange2String                     (const CXSourceRange&                     sourceRange,                           const uint32_t offset);
string CXTUResourceUsage2String                 (const CXTUResourceUsage&                 TUResourceUsage,                       const uint32_t offset);
string CXVersion2String                         (const CXVersion&                         version,                               const uint32_t offset);
string CXPlatformAvailability2String            (const CXPlatformAvailability&            platformAvailability,                  const uint32_t offset);
string CXPrintingPolicy2String                  (const CXPrintingPolicy&                  printingPolicy,                        const uint32_t offset);
