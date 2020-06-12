#include "13_Module_introspection.h"

void _13_printModuleIntrospection(string& strData, const CXCursor& cursor, uint32_t curLevel)
{
    strData += tabOffset(curLevel + 1) + "Module introspection : \n";

    CXModule module = clang_Cursor_getModule(cursor);       // 1.
    if(module)
    {
        
    }
}

CXModule        _13_Cursor_getModule                (CXCursor C)
                                                    { return clang_Cursor_getModule(C); }

CXModule        _13_getModuleForFile                (CXTranslationUnit TranslationUnit, CXFile File)
                                                    { return clang_getModuleForFile(TranslationUnit, File); }

CXFile          _13_Module_getASTFile               (CXModule Module)
                                                    { return clang_Module_getASTFile(Module); }

CXModule        _13_Module_getParent                (CXModule Module)
                                                    { return clang_Module_getParent(Module); }

CXString        _13_Module_getName                  (CXModule Module)
                                                    { return clang_Module_getName(Module); }

CXString        _13_Module_getFullName              (CXModule Module)
                                                    { return clang_Module_getFullName(Module); }

int             _13_Module_isSystem                 (CXModule Module)
                                                    { return clang_Module_isSystem(Module); }

unsigned        _13_Module_getNumTopLevelHeaders    (CXTranslationUnit TranslationUnit, CXModule Module)
                                                    { return clang_Module_getNumTopLevelHeaders(TranslationUnit, Module); }

CXFile          _13_Module_getTopLevelHeader        (CXTranslationUnit TranslationUnit, CXModule Module, unsigned Index)
                                                    { return clang_Module_getTopLevelHeader(TranslationUnit, Module, Index); }
