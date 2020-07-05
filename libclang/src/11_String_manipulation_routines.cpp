#include "11_String_manipulation_routines.h"

const char *    _11_getCString          (CXString string)
                                        { return clang_getCString(string); }

void            _11_disposeString       (CXString string)
                                        { return clang_disposeString(string); }

void            _11_disposeStringSet    (CXStringSet *set)
                                        { return clang_disposeStringSet(set); }
