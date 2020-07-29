#include "DatabaseColumnDict.h"
#include "ColumnDefinition.h"

GlobalColumnDict     g_globalColumnDict;
TokenColumnDict      g_tokenColumnDict;
SourceCodeColumnDict g_sourceCodeColumnDict;

GlobalColumnDict::GlobalColumnDict()
{
    emplace(GlobalTableColName::ClangVersion, "ClangVersion");
    emplace(GlobalTableColName::AppName,      "AppName");
    emplace(GlobalTableColName::AppVersion,   "AppVersion");
}

TokenColumnDict::TokenColumnDict()
{
    emplace(TokenTableColName::TokenID,       "TokenID");
    emplace(TokenTableColName::TokenKind,     "TokenKind");
    emplace(TokenTableColName::TokenSpelling, "TokenSpelling");
    emplace(TokenTableColName::TokenStartPos, "TokenStartPos");
    emplace(TokenTableColName::TokenEndPos,   "TokenEndPos");
}

SourceCodeColumnDict::SourceCodeColumnDict()
{
    emplace(SourceCodeTableColName::CursorID,              "CursorID");
    emplace(SourceCodeTableColName::TokenTable_TokenID,    "TokenTable_TokenID");
    emplace(SourceCodeTableColName::CursorMangling,        "CursorMangling");
    emplace(SourceCodeTableColName::CursorIsBits,          "CursorIsBits");
    emplace(SourceCodeTableColName::CursorUSR,             "CursorUSR");
    emplace(SourceCodeTableColName::CursorAccessSpecifier, "CursorAccessSpecifier");
    emplace(SourceCodeTableColName::CursorStorageClass,    "CursorStorageClass");
    emplace(SourceCodeTableColName::CursorDisplayName,     "CursorDisplayName");
    emplace(SourceCodeTableColName::CursorHash,            "CursorHash");
    emplace(SourceCodeTableColName::CursorKind,            "CursorKind");
    emplace(SourceCodeTableColName::CursorAttr,            "CursorAttr");
    emplace(SourceCodeTableColName::CursorLinkage,         "CursorLinkage");
    emplace(SourceCodeTableColName::CursorVisibility,      "CursorVisibility");
    emplace(SourceCodeTableColName::CursorAvailability,    "CursorAvailability");
    emplace(SourceCodeTableColName::CursorTLSKind,         "CursorTLSKind");
}
