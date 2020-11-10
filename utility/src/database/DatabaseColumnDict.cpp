#include <Database/DatabaseColumnDict.h>
#include <Database/ColumnDefinition.h>

GlobalColumnDict  g_globalColumnDict;
TokenColumnDict   g_tokenColumnDict;
CursorColumnDict  g_cursorColumnDict;
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
    emplace(CursorTableColName::CursorUSR,                      "CursorUSR");
    emplace(CursorTableColName::CursorDisplayName,              "CursorDisplayName");
    emplace(CursorTableColName::CursorTable_CursorReferenced,   "CursorTable_CursorReferenced");
    emplace(CursorTableColName::CursorHash,                     "CursorHash");
    emplace(CursorTableColName::CursorKind,                     "CursorKind");
    emplace(CursorTableColName::CursorKindSpelling,             "CursorKindSpelling");
}

LinkingColumnDict::LinkingColumnDict()
{
    emplace(LinkingTableColName::LinkingID,                     "LinkingID");
    emplace(LinkingTableColName::LinkingMangling,               "LinkingMangling");
    emplace(LinkingTableColName::LinkingTableName,              "LinkingTableName");
    emplace(LinkingTableColName::LinkingCursorID,               "LinkingCursorID");

}
