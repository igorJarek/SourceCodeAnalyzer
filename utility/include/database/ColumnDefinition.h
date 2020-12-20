#pragma once

enum GlobalTableColName : uint32_t
{
    ClangVersion,
    AppName,
    AppVersion,

    GlobalTableLast
};

enum FileListTableColName : uint32_t
{
    FileListID,
    FileListFileName,

    FileListTableLast
};

enum TokenTableColName : uint32_t
{
    TokenID,
    TokenKind,
    TokenSpelling,
    TokenStartPos_Line,
    TokenStartPos_Col,
    TokenEndPos_Line,
    TokenEndPos_Col,

    TokenTableLast
};

enum CallingTableColName : uint32_t
{
    CalllingID,
    CallingNameTokenID,
    CallingFilePath,
    CallingFunctionID,

    CallingTableLast
};

enum FunctionsTableColName : uint32_t
{
    FunctionsID,
    FunctionsNameTokenID,

    FunctionsTableLast
};
