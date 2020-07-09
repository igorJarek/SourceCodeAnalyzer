#pragma once

#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

// Clang Functions

unsigned    _16_visitChildren   (CXCursor parent, CXCursorVisitor visitor, CXClientData client_data);         // 1.
