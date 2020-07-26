#pragma once

enum class GlobalTableColName
{
    ClangVersion,
    AppVersion,

    GlobalTableLast
};

enum class TokenTableColName
{
    TokenID,
    TokenKind,
    TokenSpelling,
    TokenStartPos,
    TokenEndPos,

    TokenTableLast
};

enum class SourceCodeTableColName
{
    CursorID,
    TokenID,
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