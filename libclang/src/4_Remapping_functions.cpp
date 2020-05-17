#include "4_Remapping_functions.h"

CXRemapping     _4_getRemappings                (const char *path)
                                                { return clang_getRemappings(path); }

CXRemapping     _4_getRemappingsFromFileList    (const char **filePaths, unsigned numFiles)
                                                { return clang_getRemappingsFromFileList(filePaths, numFiles); }

unsigned        _4_remap_getNumFiles            (CXRemapping remapping)
                                                { return clang_remap_getNumFiles(remapping); }

void            _4_remap_getFilenames           (CXRemapping remapping, unsigned index, CXString *original, CXString *transformed)
                                                { return clang_remap_getFilenames(remapping, index, original, transformed); }

void            _4_remap_dispose                (CXRemapping remapping)
                                                { return clang_remap_dispose(remapping); }
