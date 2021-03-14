#include "Paths.h"

const string APP_NAME           { "libclang" };
const string APP_VERSION        { "0.9" };

const string AST_FILE_EXT       { ".ast" };
const string AST_EXT_FILE_EXT   { ".astExt" };
const string DIAGN_FILE_EXT     { ".diagn" };
const string FILE_FILE_EXT      { ".file" };
const string TOKENS_FILE_EXT    { ".tokens" };
const string TUNIT_FILE_EXT     { ".tunit" };
const string TUNIT_BIN_FILE_EXT { ".tunitBin" };

const string LIB_PATH               { "..\\lib\\" };
const string CURSORS_REF_PATH       { "..\\lib\\cursors.cur" };
const string CURSORS_INFO_REF_PATH  { "..\\lib\\cursors.curInfo" };
const string TYPES_REF_PATH         { "..\\lib\\types.type" };
const string TYPES_INFO_REF_PATH    { "..\\lib\\types.typeInfo" };

const char* argsIncludePrefix       = "-I";
const char* argsIncludePath         = "..\\lib\\include\\";
const char* COMPILATION_ARGS[2]     = { argsIncludePrefix, argsIncludePath };
