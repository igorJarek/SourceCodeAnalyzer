#pragma once

#include <clang-c/Index.h>
#include <clang-c/Documentation.h>
#include <string>

using std::string;

namespace std
{
    string to_string(const string&                            string);
    string to_string(const char*                              cstring);

    string to_string(const CXString&                          string);
    string to_string(const CXType&                            type);
    string to_string(const CXDiagnosticSeverity&              diagnosticSeverity);
    string to_string(const CXDiagnosticDisplayOptions&        options);
    string to_string(const CXErrorCode&                       errorCode);
    string to_string(const CXSaveError&                       saveError);
    string to_string(const CXTemplateArgumentKind&            templateArgumentKind);
    string to_string(const CXCallingConv&                     callingConv);
    string to_string(const CXTypeLayoutError&                 typeLayoutError);
    string to_string(const CXTypeNullabilityKind&             typeNullabilityKind);
    string to_string(const CXRefQualifierKind&                refQualifierKind);
    string to_string(const CX_CXXAccessSpecifier&             accessSpecifier);
    string to_string(const CX_StorageClass&                   storageClass);
    string to_string(const CXTokenKind&                       tokenKind);
    string to_string(const CXEvalResultKind&                  evalResultKind);
    string to_string(const CXLinkageKind&                     linkageKind);
    string to_string(const CXVisibilityKind&                  visibilityKind);
    string to_string(const CXAvailabilityKind&                availabilityKind);
    string to_string(const CXLanguageKind&                    languageKind);
    string to_string(const CXTLSKind&                         LSKind);
    string to_string(const CXCommentKind&                     commentKind);
    string to_string(const CXCommentInlineCommandRenderKind&  commentInlineCommandRenderKind);
    string to_string(const CXCommentParamPassDirection&       commentParamPassDirection);
}
