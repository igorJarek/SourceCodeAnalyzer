#include <Database/DatabaseColumnDict.h>
#include <Database/ColumnDefinition.h>

GlobalColumnDict   g_globalColumnDict;
FileListColumnDict g_fileListColumnDict;
TokenColumnDict    g_tokenColumnDict;

GlobalColumnDict::GlobalColumnDict()
{
    emplace(GlobalTableColName::ClangVersion,                       "ClangVersion");
    emplace(GlobalTableColName::AppName,                            "AppName");
    emplace(GlobalTableColName::AppVersion,                         "AppVersion");
}

FileListColumnDict::FileListColumnDict()
{
    emplace(FileListTableColName::FileListID,                       "FileListID");
    emplace(FileListTableColName::FileListFileName,                 "FileListFileName");
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
