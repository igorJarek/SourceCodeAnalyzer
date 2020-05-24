#include "16_Traversing_the_AST_with_cursors.h"

unsigned    _16_visitChildren   (CXCursor parent, CXCursorVisitor visitor, CXClientData client_data)
                                { return clang_visitChildren(parent, visitor, client_data); }
