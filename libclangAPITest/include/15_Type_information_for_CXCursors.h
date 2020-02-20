#pragma once

#include <clang-c/Index.h>
#include "UtilityFunctions.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;string _15_CXCursorType2String(const CXCursor& cursor);
string _15_CXType2String(const CXType& type);
