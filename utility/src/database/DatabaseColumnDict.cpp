#include <Database/DatabaseColumnDict.h>
#include <Database/ColumnDefinition.h>

GlobalColumnDict  g_globalColumnDict;
TokenColumnDict   g_tokenColumnDict;
CursorColumnDict  g_cursorColumnDict;
TypeColumnDict    g_typeColumnDict;
LinkingColumnDict g_linkingColumnDict;

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

CursorColumnDict::CursorColumnDict()
{
    emplace(CursorTableColName::CursorID,                       "CursorID");
    emplace(CursorTableColName::TokenTable_TokenID,             "TokenTable_TokenID");
    emplace(CursorTableColName::CursorMangling,                 "CursorMangling");
    emplace(CursorTableColName::CursorIsBits,                   "CursorIsBits");
    emplace(CursorTableColName::CursorTemplateCursorKind,       "CursorTemplateCursorKind");
    emplace(CursorTableColName::CursorUSR,                      "CursorUSR");
    emplace(CursorTableColName::CursorDisplayName,              "CursorDisplayName");
    emplace(CursorTableColName::CursorTable_CursorReferenced,   "CursorTable_CursorReferenced");
    emplace(CursorTableColName::TypeTable_CursorType,           "TypeTable_CursorType");
    emplace(CursorTableColName::CursorEnumConstantDeclValue,    "CursorEnumConstantDeclValue");
    emplace(CursorTableColName::CursorEnumConstantDeclUValue,   "CursorEnumConstantDeclUValue");
    emplace(CursorTableColName::CursorFieldDeclBitWidth,        "CursorFieldDeclBitWidth");
    emplace(CursorTableColName::CursorExceptionSpecification,   "CursorExceptionSpecification");
    emplace(CursorTableColName::CursorOffsetOfField,            "CursorOffsetOfField");
    emplace(CursorTableColName::CursorAccessSpecifier,          "CursorAccessSpecifier");
    emplace(CursorTableColName::CursorStorageClass,             "CursorStorageClass");
    emplace(CursorTableColName::CursorEvalResultKind,           "CursorEvalResultKind");
    emplace(CursorTableColName::CursorHash,                     "CursorHash");
    emplace(CursorTableColName::CursorKind,                     "CursorKind");
    emplace(CursorTableColName::CursorKindSpelling,             "CursorKindSpelling");
    emplace(CursorTableColName::CursorAttr,                     "CursorAttr");
    emplace(CursorTableColName::CursorLinkageKind,              "CursorLinkageKind");
    emplace(CursorTableColName::CursorVisibilityKind,           "CursorVisibilityKind");
    emplace(CursorTableColName::CursorAvailabilityKind,         "CursorAvailabilityKind");
    emplace(CursorTableColName::CursorLanguageKind,             "CursorLanguageKind");
    emplace(CursorTableColName::CursorTLSKind,                  "CursorTLSKind");
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
