#include "Paths.h"

const string AST_FILE_EXT       { ".ast" };
const string AST_EXT_FILE_EXT   { ".astExt" };
const string DIAGN_FILE_EXT     { ".diagn" };
const string FILE_FILE_EXT      { ".file" };
const string TOKENS_FILE_EXT    { ".tokens" };
const string TUNIT_FILE_EXT     { ".tunit" };
const string TUNIT_BIN_FILE_EXT { ".tunitBin" };

#ifdef _DEBUG
    const string LIB_PATH           { "..\\lib\\" };
    const string CURSORS_REF_PATH   { "..\\lib\\cursors.cur" };

    const char* argsIncludePrefix   = "-I";
    const char* argsIncludePath     = "..\\lib\\include\\";
    const char* COMPILATION_ARGS[2] = { argsIncludePrefix, argsIncludePath };
#else
    const string LIB_PATH           { "..\\..\\lib\\" };
    const string CURSORS_REF_PATH   { "..\\..\\lib\\cursors.cur" };

    const char* argsIncludePrefix   = "-I";
    const char* argsIncludePath     = "..\\..\\lib\\include\\";
    const char* COMPILATION_ARGS[2] = { argsIncludePrefix, argsIncludePath };
#endif
