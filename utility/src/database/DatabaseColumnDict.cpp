#include <Database/DatabaseColumnDict.h>
#include <Database/ColumnDefinition.h>

GlobalColumnDict     g_globalColumnDict;
TokenColumnDict      g_tokenColumnDict;
SourceCodeColumnDict g_sourceCodeColumnDict;
TypeColumnDict       g_typeColumnDict;

GlobalColumnDict::GlobalColumnDict()
{
    emplace(GlobalTableColName::ClangVersion,                       "ClangVersion");
    emplace(GlobalTableColName::AppName,                            "AppName");
    emplace(GlobalTableColName::AppVersion,                         "AppVersion");
}

TokenColumnDict::TokenColumnDict()
{
    emplace(TokenTableColName::TokenID,                             "TokenID");
    emplace(TokenTableColName::TokenKind,                           "TokenKind");
    emplace(TokenTableColName::TokenSpelling,                       "TokenSpelling");
    emplace(TokenTableColName::TokenStartPos_Line,                  "TokenStartPos_Line");
    emplace(TokenTableColName::TokenStartPos_Col,                   "TokenStartPos_Col");
    emplace(TokenTableColName::TokenEndPos_Line,                    "TokenEndPos_Line");
    emplace(TokenTableColName::TokenEndPos_Col,                     "TokenEndPos_Col");
}

SourceCodeColumnDict::SourceCodeColumnDict()
{
    emplace(SourceCodeTableColName::CursorID,                       "CursorID");
    emplace(SourceCodeTableColName::TokenTable_TokenID,             "TokenTable_TokenID");
    emplace(SourceCodeTableColName::CursorMangling,                 "CursorMangling");
    emplace(SourceCodeTableColName::CursorIsBits,                   "CursorIsBits");
    emplace(SourceCodeTableColName::CursorTemplateCursorKind,       "CursorTemplateCursorKind");
    emplace(SourceCodeTableColName::CursorUSR,                      "CursorUSR");
    emplace(SourceCodeTableColName::CursorDisplayName,              "CursorDisplayName");
    emplace(SourceCodeTableColName::CursorTable_CursorReferenced,   "CursorTable_CursorReferenced");
    emplace(SourceCodeTableColName::TypeTable_CursorType,           "TypeTable_CursorType");
    emplace(SourceCodeTableColName::CursorEnumConstantDeclValue,    "CursorEnumConstantDeclValue");
    emplace(SourceCodeTableColName::CursorEnumConstantDeclUValue,   "CursorEnumConstantDeclUValue");
    emplace(SourceCodeTableColName::CursorFieldDeclBitWidth,        "CursorFieldDeclBitWidth");
    emplace(SourceCodeTableColName::CursorExceptionSpecification,   "CursorExceptionSpecification");
    emplace(SourceCodeTableColName::CursorOffsetOfField,            "CursorOffsetOfField");
    emplace(SourceCodeTableColName::CursorAccessSpecifier,          "CursorAccessSpecifier");
    emplace(SourceCodeTableColName::CursorStorageClass,             "CursorStorageClass");
    emplace(SourceCodeTableColName::CursorEvalResultKind,           "CursorEvalResultKind");
    emplace(SourceCodeTableColName::CursorHash,                     "CursorHash");
    emplace(SourceCodeTableColName::CursorKind,                     "CursorKind");
    emplace(SourceCodeTableColName::CursorKindSpelling,             "CursorKindSpelling");
    emplace(SourceCodeTableColName::CursorAttr,                     "CursorAttr");
    emplace(SourceCodeTableColName::CursorLinkageKind,              "CursorLinkageKind");
    emplace(SourceCodeTableColName::CursorVisibilityKind,           "CursorVisibilityKind");
    emplace(SourceCodeTableColName::CursorAvailabilityKind,         "CursorAvailabilityKind");
    emplace(SourceCodeTableColName::CursorLanguageKind,             "CursorLanguageKind");
    emplace(SourceCodeTableColName::CursorTLSKind,                  "CursorTLSKind");
}

TypeColumnDict::TypeColumnDict()
{
    emplace(TypeTableColName::TypeID,                               "TypeID");
    emplace(TypeTableColName::TypeSpelling,                         "TypeSpelling");
    emplace(TypeTableColName::TypeIsBits,                           "TypeIsBits");
    emplace(TypeTableColName::TypeAddressSpace,                     "TypeAddressSpace");
    emplace(TypeTableColName::TypeTypedefName,                      "TypeTypedefName");
    emplace(TypeTableColName::TypeKindSpelling,                     "TypeKindSpelling");
    emplace(TypeTableColName::TypeFuncCallingConv,                  "TypeFuncCallingConv");
    emplace(TypeTableColName::TypeExceptionSpecification,           "TypeExceptionSpecification");
    emplace(TypeTableColName::TypeArraySize,                        "TypeArraySize");
    emplace(TypeTableColName::TypeNullabilityKind,                  "TypeNullabilityKind");
    emplace(TypeTableColName::TypeAlignOf,                          "TypeAlignOf");
    emplace(TypeTableColName::TypeSizeOf,                           "TypeSizeOf");
    emplace(TypeTableColName::TypeRefQualifierKind,                 "TypeRefQualifierKind");
}

LinkingColumnDict::LinkingColumnDict()
{
    emplace(LinkingTableColName::LinkingID,                         "LinkingID");
    emplace(LinkingTableColName::LinkingMangling,                   "LinkingMangling");
    emplace(LinkingTableColName::LinkingTableName,                  "LinkingTableName");
    emplace(LinkingTableColName::LinkingCursorID,                   "LinkingCursorID");

}
