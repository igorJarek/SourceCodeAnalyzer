#pragma once

#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

CXResult									_14_findReferencesInFile			(CXCursor cursor, CXFile file, CXCursorAndRangeVisitor visitor);
CXResult									_14_findIncludesInFile				(CXTranslationUnit TU, CXFile file, CXCursorAndRangeVisitor visitor);
int											_14_isEntityObjCContainerKind		(CXIdxEntityKind IdxEntityKind);
const CXIdxObjCContainerDeclInfo *			_14_getObjCContainerDeclInfo		(const CXIdxDeclInfo* IdxDeclInfo);
const CXIdxObjCInterfaceDeclInfo *			_14_getObjCInterfaceDeclInfo		(const CXIdxDeclInfo* IdxDeclInfo);
const CXIdxObjCCategoryDeclInfo *			_14_getObjCCategoryDeclInfo			(const CXIdxDeclInfo* IdxDeclInfo);
const CXIdxObjCProtocolRefListInfo *		_14_getObjCProtocolRefListInfo		(const CXIdxDeclInfo* IdxDeclInfo);
const CXIdxObjCPropertyDeclInfo *			_14_getObjCPropertyDeclInfo			(const CXIdxDeclInfo* IdxDeclInfo);
const CXIdxIBOutletCollectionAttrInfo * 	_14_getIBOutletCollectionAttrInfo	(const CXIdxAttrInfo* IdxAttrInfo);
const CXIdxCXXClassDeclInfo *				_14_getCXXClassDeclInfo				(const CXIdxDeclInfo* IdxDeclInfo);
CXIdxClientContainer						_14_getClientContainer				(const CXIdxContainerInfo* IdxContainerInfo);
void										_14_setClientContainer				(const CXIdxContainerInfo* IdxContainerInfo, CXIdxClientContainer IdxClientContainer);
CXIdxClientEntity							_14_getClientEntity					(const CXIdxEntityInfo* IdxEntityInfo);
void										_14_setClientEntity					(const CXIdxEntityInfo* IdxEntityInfo, CXIdxClientEntity IdxClientEntity);
CXIndexAction								_14_IndexAction_create				(CXIndex CIdx);
void										_14_IndexAction_dispose				(CXIndexAction IndexAction);
int											_14_indexSourceFile					(CXIndexAction IndexAction, CXClientData client_data, IndexerCallbacks* index_callbacks, unsigned index_callbacks_size, unsigned index_options, const char *source_filename, const char *const *command_line_args, int num_command_line_args, struct CXUnsavedFile *unsaved_files, unsigned num_unsaved_files, CXTranslationUnit *out_TU, unsigned TU_options);
int											_14_indexSourceFileFullArgv			(CXIndexAction IndexAction, CXClientData client_data, IndexerCallbacks* index_callbacks, unsigned index_callbacks_size, unsigned index_options, const char *source_filename, const char *const *command_line_args, int num_command_line_args, struct CXUnsavedFile *unsaved_files, unsigned num_unsaved_files, CXTranslationUnit *out_TU, unsigned TU_options);
int											_14_indexTranslationUnit			(CXIndexAction IndexAction, CXClientData client_data, IndexerCallbacks* index_callbacks, unsigned index_callbacks_size, unsigned index_options, CXTranslationUnit TranslationUnit);
void										_14_getFileLocation					(CXIdxLoc loc, CXIdxClientFile* indexFile, CXFile* file, unsigned* line, unsigned* column, unsigned* offset);
CXSourceLocation							_14_getCXSourceLocation				(CXIdxLoc loc);
unsigned									_14_Type_visitFields				(CXType T, CXFieldVisitor visitor, CXClientData client_data);