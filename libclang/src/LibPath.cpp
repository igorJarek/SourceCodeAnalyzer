#include "LibPath.h"

#ifdef _DEBUG
	const string LIB_PATH{ "..\\lib\\" };

	const char* argsIncludePrefix = "-I";
	const char* argsIncludePath = "..\\lib\\include\\";
	const char* COMPILATION_ARGS[2] = { argsIncludePrefix, argsIncludePath };
#else
	const string LIB_PATH{ "..\\..\\lib\\" };

	const char* argsIncludePrefix = "-I";
	const char* argsIncludePath = "..\\..\\lib\\include\\";
	const char* COMPILATION_ARGS[2] = { argsIncludePrefix, argsIncludePath };
#endif
