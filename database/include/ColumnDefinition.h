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
    CursorUSR,
    CursorAccessSpecifier,
    CursorStorageClass,
    CursorDisplayName,
    CursorHash,
    CursorKind,
    CursorAttr,
    CursorLinkage,
    CursorVisibility,
    CursorAvailability,
    CursorTLSKind,

    SourceCodeTableLast
};