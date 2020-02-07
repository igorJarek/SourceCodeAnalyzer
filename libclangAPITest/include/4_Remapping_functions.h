#pragma once

#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/*
    1. CXRemapping 	clang_getRemappings                 (const char *path)
    2. CXRemapping 	clang_getRemappingsFromFileList     (const char **filePaths, unsigned numFiles)
    3. unsigned 	clang_remap_getNumFiles             (CXRemapping)
    4. void 	    clang_remap_getFilenames            (CXRemapping, unsigned index, CXString *original, CXString *transformed)
    5. void 	    clang_remap_dispose                 (CXRemapping)
*/