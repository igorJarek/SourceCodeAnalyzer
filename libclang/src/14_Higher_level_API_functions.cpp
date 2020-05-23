#include "14_Higher_level_API_functions.h"

CXResult									_14_findReferencesInFile			(CXCursor cursor, CXFile file, CXCursorAndRangeVisitor visitor)
																				{ return clang_findReferencesInFile(cursor, file, visitor); }

CXResult									_14_findIncludesInFile				(CXTranslationUnit TU, CXFile file, CXCursorAndRangeVisitor visitor)
																				{ return clang_findIncludesInFile(TU, file, visitor); }

int											_14_isEntityObjCContainerKind		(CXIdxEntityKind IdxEntityKind)
																				{ return clang_index_isEntityObjCContainerKind(IdxEntityKind); }

const CXIdxObjCContainerDeclInfo *			_14_getObjCContainerDeclInfo		(const CXIdxDeclInfo* IdxDeclInfo)
																				{ return clang_index_getObjCContainerDeclInfo(IdxDeclInfo); }

const CXIdxObjCInterfaceDeclInfo *			_14_getObjCInterfaceDeclInfo		(const CXIdxDeclInfo* IdxDeclInfo)
																				{ return clang_index_getObjCInterfaceDeclInfo(IdxDeclInfo); }

const CXIdxObjCCategoryDeclInfo *			_14_getObjCCategoryDeclInfo			(const CXIdxDeclInfo* IdxDeclInfo)
																				{ return clang_index_getObjCCategoryDeclInfo(IdxDeclInfo); }

const CXIdxObjCProtocolRefListInfo*			_14_getObjCProtocolRefListInfo		(const CXIdxDeclInfo* IdxDeclInfo)
																				{ return clang_index_getObjCProtocolRefListInfo(IdxDeclInfo); }

const CXIdxObjCPropertyDeclInfo *			_14_getObjCPropertyDeclInfo			(const CXIdxDeclInfo* IdxDeclInfo)
																				{ return clang_index_getObjCPropertyDeclInfo(IdxDeclInfo); }

const CXIdxIBOutletCollectionAttrInfo *		_14_getIBOutletCollectionAttrInfo	(const CXIdxAttrInfo* IdxAttrInfo)
																				{ return clang_index_getIBOutletCollectionAttrInfo(IdxAttrInfo); }

const CXIdxCXXClassDeclInfo *				_14_getCXXClassDeclInfo				(const CXIdxDeclInfo* IdxDeclInfo)
																				{ return clang_index_getCXXClassDeclInfo(IdxDeclInfo); }

CXIdxClientContainer						_14_getClientContainer				(const CXIdxContainerInfo* IdxContainerInfo)
																				{ return clang_index_getClientContainer(IdxContainerInfo); }

void										_14_setClientContainer				(const CXIdxContainerInfo* IdxContainerInfo, CXIdxClientContainer IdxClientContainer)
																				{ return clang_index_setClientContainer(IdxContainerInfo, IdxClientContainer); }

CXIdxClientEntity							_14_getClientEntity					(const CXIdxEntityInfo* IdxEntityInfo)
																				{ return clang_index_getClientEntity(IdxEntityInfo); }

void										_14_setClientEntity					(const CXIdxEntityInfo* IdxEntityInfo, CXIdxClientEntity IdxClientEntity)
																				{ return clang_index_setClientEntity(IdxEntityInfo, IdxClientEntity); }

CXIndexAction								_14_IndexAction_create				(CXIndex CIdx)
																				{ return clang_IndexAction_create(CIdx); }

void										_14_IndexAction_dispose				(CXIndexAction IndexAction)
																				{ return clang_IndexAction_dispose(IndexAction); }

int											_14_indexSourceFile					(CXIndexAction IndexAction, CXClientData client_data, IndexerCallbacks* index_callbacks, unsigned index_callbacks_size, unsigned index_options, const char *source_filename, const char *const *command_line_args, int num_command_line_args, struct CXUnsavedFile *unsaved_files, unsigned num_unsaved_files, CXTranslationUnit *out_TU, unsigned TU_options)
																				{ return clang_indexSourceFile(IndexAction, client_data, index_callbacks, index_callbacks_size, index_options, source_filename, command_line_args, num_command_line_args, unsaved_files, num_unsaved_files, out_TU, TU_options); }

int											_14_indexSourceFileFullArgv			(CXIndexAction IndexAction, CXClientData client_data, IndexerCallbacks* index_callbacks, unsigned index_callbacks_size, unsigned index_options, const char *source_filename, const char *const *command_line_args, int num_command_line_args, struct CXUnsavedFile *unsaved_files, unsigned num_unsaved_files, CXTranslationUnit *out_TU, unsigned TU_options)
																				{ return clang_indexSourceFileFullArgv(IndexAction, client_data, index_callbacks, index_callbacks_size, index_options, source_filename, command_line_args, num_command_line_args, unsaved_files, num_unsaved_files, out_TU, TU_options); }

int											_14_indexTranslationUnit			(CXIndexAction IndexAction, CXClientData client_data, IndexerCallbacks* index_callbacks, unsigned index_callbacks_size, unsigned index_options, CXTranslationUnit TranslationUnit)
																				{ return clang_indexTranslationUnit(IndexAction, client_data, index_callbacks, index_callbacks_size, index_options, TranslationUnit); }

void										_14_getFileLocation					(CXIdxLoc loc, CXIdxClientFile* indexFile, CXFile* file, unsigned* line, unsigned* column, unsigned* offset)
																				{ return clang_indexLoc_getFileLocation(loc, indexFile, file, line, column, offset); }

CXSourceLocation							_14_getCXSourceLocation				(CXIdxLoc loc)
																				{ return clang_indexLoc_getCXSourceLocation(loc); }

unsigned									_14_Type_visitFields				(CXType T, CXFieldVisitor visitor, CXClientData client_data)
																				{ return clang_Type_visitFields(T, visitor, client_data); }
