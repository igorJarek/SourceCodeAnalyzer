#include <libclangstruct2str/LibClangStruct2Str.h>

namespace std
{
    string to_string(const string& string)
    {
        return string;
    }

    string to_string(const CXString& string)
    {
        std::string str{ "-NULL-" };

        if( string.data)
        {
            str = clang_getCString(string);
            clang_disposeString(string);
        }

        return str;
    }

    string to_string(const CXType& type)
    {
        CXString typeSpelling = clang_getTypeSpelling(type);
        return to_string(typeSpelling);
    }

    string to_string(const CXDiagnosticSeverity& diagnosticSeverity)
    {
        switch (diagnosticSeverity)
        {
            case CXDiagnostic_Ignored:
                return "CXDiagnostic_Ignored";

            case CXDiagnostic_Note:
                return "CXDiagnostic_Note";

            case CXDiagnostic_Warning:
                return "CXDiagnostic_Warning";

            case CXDiagnostic_Error:
                return "CXDiagnostic_Error";

            case CXDiagnostic_Fatal:
                return "CXDiagnostic_Fatal";


            default:
                return "Undefined CXDiagnosticSeverity";
        }
    }

    string to_string(const CXDiagnosticDisplayOptions& options)
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

    string to_string(const CXErrorCode& errorCode)
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

    string to_string(const CXSaveError& saveError)
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

    string to_string(const CXTemplateArgumentKind& templateArgumentKind)
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

    string to_string(const CXCallingConv& callingConv)
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

    string to_string(const CXTypeLayoutError& typeLayoutError)
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

    string to_string(const CXTypeNullabilityKind& typeNullabilityKind)
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

    string to_string(const CXRefQualifierKind& refQualifierKind)
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

    string to_string(const CX_CXXAccessSpecifier& accessSpecifier)
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

    string to_string(const CX_StorageClass& storageClass)
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

    string to_string(const CXTokenKind& tokenKind)
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

    string to_string(const CXEvalResultKind& evalResultKind)
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

    string to_string(const CXLinkageKind& linkageKind)
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

    string to_string(const CXVisibilityKind& visibilityKind)
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

    string to_string(const CXAvailabilityKind& availabilityKind)
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

    string to_string(const CXLanguageKind& languageKind)
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

    string to_string(const CXTLSKind& LSKind)
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

    string to_string(const CXCommentKind& commentKind)
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

    string to_string(const CXCommentInlineCommandRenderKind& commentInlineCommandRenderKind)
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

    string to_string(const CXCommentParamPassDirection& commentParamPassDirection)
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
}
