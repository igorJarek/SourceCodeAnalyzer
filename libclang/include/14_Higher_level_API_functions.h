#pragma once

#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

CXResult                                    _14_findReferencesInFile            (CXCursor cursor, CXFile file, CXCursorAndRangeVisitor visitor);                                                // 1.
CXResult                                    _14_findIncludesInFile              (CXTranslationUnit TU, CXFile file, CXCursorAndRangeVisitor visitor);                                           // 2.
int                                         _14_isEntityObjCContainerKind       (CXIdxEntityKind IdxEntityKind);                                                                                // 3.
const CXIdxObjCContainerDeclInfo *          _14_getObjCContainerDeclInfo        (const CXIdxDeclInfo* IdxDeclInfo);                                                                             // 4.
const CXIdxObjCInterfaceDeclInfo *          _14_getObjCInterfaceDeclInfo        (const CXIdxDeclInfo* IdxDeclInfo);                                                                             // 5.
const CXIdxObjCCategoryDeclInfo *           _14_getObjCCategoryDeclInfo         (const CXIdxDeclInfo* IdxDeclInfo);                                                                             // 6.
const CXIdxObjCProtocolRefListInfo *        _14_getObjCProtocolRefListInfo      (const CXIdxDeclInfo* IdxDeclInfo);                                                                             // 7.
const CXIdxObjCPropertyDeclInfo *           _14_getObjCPropertyDeclInfo         (const CXIdxDeclInfo* IdxDeclInfo);                                                                             // 8.
const CXIdxIBOutletCollectionAttrInfo *     _14_getIBOutletCollectionAttrInfo   (const CXIdxAttrInfo* IdxAttrInfo);                                                                             // 9.
const CXIdxCXXClassDeclInfo *               _14_getCXXClassDeclInfo             (const CXIdxDeclInfo* IdxDeclInfo);                                                                             // 10.
CXIdxClientContainer                        _14_getClientContainer              (const CXIdxContainerInfo* IdxContainerInfo);                                                                   // 11.
void                                        _14_setClientContainer              (const CXIdxContainerInfo* IdxContainerInfo, CXIdxClientContainer IdxClientContainer);                          // 12.
CXIdxClientEntity                           _14_getClientEntity                 (const CXIdxEntityInfo* IdxEntityInfo);                                                                         // 13.
void                                        _14_setClientEntity                 (const CXIdxEntityInfo* IdxEntityInfo, CXIdxClientEntity IdxClientEntity);                                      // 14.
CXIndexAction                               _14_IndexAction_create              (CXIndex CIdx);                                                                                                 // 15.
void                                        _14_IndexAction_dispose             (CXIndexAction IndexAction);                                                                                    // 16.
int                                         _14_indexSourceFile                 (CXIndexAction IndexAction, CXClientData client_data, IndexerCallbacks* index_callbacks, 
                                                                                 unsigned index_callbacks_size, unsigned index_options, const char *source_filename, 
                                                                                 const char *const *command_line_args, int num_command_line_args, struct CXUnsavedFile *unsaved_files, 
                                                                                 unsigned num_unsaved_files, CXTranslationUnit *out_TU, unsigned TU_options);                                   // 17.
int                                         _14_indexSourceFileFullArgv         (CXIndexAction IndexAction, CXClientData client_data, IndexerCallbacks* index_callbacks, 
                                                                                 unsigned index_callbacks_size, unsigned index_options, const char *source_filename, 
                                                                                 const char *const *command_line_args, int num_command_line_args, struct CXUnsavedFile *unsaved_files, 
                                                                                 unsigned num_unsaved_files, CXTranslationUnit *out_TU, unsigned TU_options);                                   // 18.
int                                         _14_indexTranslationUnit            (CXIndexAction IndexAction, CXClientData client_data, IndexerCallbacks* index_callbacks, 
                                                                                 unsigned index_callbacks_size, unsigned index_options, CXTranslationUnit TranslationUnit);                     // 19.
void                                        _14_getFileLocation                 (CXIdxLoc loc, CXIdxClientFile* indexFile, CXFile* file, unsigned* line, unsigned* column, unsigned* offset);   // 20.
CXSourceLocation                            _14_getCXSourceLocation             (CXIdxLoc loc);                                                                                                 // 21.
unsigned                                    _14_Type_visitFields                (CXType T, CXFieldVisitor visitor, CXClientData client_data);                                                   // 22.
