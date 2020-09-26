#pragma once

enum GlobalTableColName : uint32_t
{
    ClangVersion,
    AppName,
    AppVersion,

    GlobalTableLast
};

enum TokenTableColName : uint32_t
{
    TokenID,
    TokenKind,
    TokenSpelling,
    TokenStartPos,
    TokenEndPos,

    TokenTableLast
};

enum SourceCodeTableColName : uint32_t
{
    CursorID,
    TokenTable_TokenID,
    CursorMangling,
    CursorIsBits,
    CursorTemplateCursorKind,
    CursorUSR,
    CursorDisplayName,
    CursorTable_CursorReferenced,
    TypeTable_CursorType,
    CursorEnumConstantDeclValue,
    CursorEnumConstantDeclUValue,
    CursorFieldDeclBitWidth,
    CursorExceptionSpecification,
    CursorOffsetOfField,
    CursorAccessSpecifier,
    CursorStorageClass,
    CursorEvalResultKind,
    CursorHash,
    CursorKind,
    CursorAttr,
    CursorLinkageKind,
    CursorVisibilityKind,
    CursorAvailabilityKind,
    CursorLanguageKind,
    CursorTLSKind,

    SourceCodeTableLast
};

enum TypeTableColName : uint32_t
{
    TypeID,
    TypeSpelling,
    TypeIsBits,
    TypeAddressSpace,
    TypeTypedefName,
    TypeKindSpelling,
    TypeFuncCallingConv,
    TypeExceptionSpecification,
    TypeArraySize,
    TypeNullabilityKind,
    TypeAlignOf,
    TypeSizeOf,
    TypeRefQualifierKind,

    TypeTableLast
};
