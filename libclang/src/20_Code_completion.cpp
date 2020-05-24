#include "20_Code_completion.h"

enum CXCompletionChunkKind      _20_getCompletionChunkKind                      (CXCompletionString completion_string, unsigned chunk_number)
                                                                                { return clang_getCompletionChunkKind(completion_string, chunk_number); }

CXString                        _20_getCompletionChunkText                      (CXCompletionString completion_string, unsigned chunk_number)
                                                                                { return clang_getCompletionChunkText(completion_string, chunk_number); }

CXCompletionString              _20_getCompletionChunkCompletionString          (CXCompletionString completion_string, unsigned chunk_number)
                                                                                { return clang_getCompletionChunkCompletionString(completion_string, chunk_number); }

unsigned                        _20_getNumCompletionChunks                      (CXCompletionString completion_string)
                                                                                { return clang_getNumCompletionChunks(completion_string); }

unsigned                        _20_getCompletionPriority                       (CXCompletionString completion_string)
                                                                                { return clang_getCompletionPriority(completion_string); }

enum CXAvailabilityKind         _20_getCompletionAvailability                   (CXCompletionString completion_string)
                                                                                { return clang_getCompletionAvailability(completion_string); }

unsigned                        _20_getCompletionNumAnnotations                 (CXCompletionString completion_string)
                                                                                { return clang_getCompletionNumAnnotations(completion_string); }

CXString                        _20_getCompletionAnnotation                     (CXCompletionString completion_string, unsigned annotation_number)
                                                                                { return clang_getCompletionAnnotation(completion_string, annotation_number); }

CXString                        _20_getCompletionParent                         (CXCompletionString completion_string, enum CXCursorKind *kind)
                                                                                { return clang_getCompletionParent(completion_string, kind); }

CXString                        _20_getCompletionBriefComment                   (CXCompletionString completion_string)
                                                                                { return clang_getCompletionBriefComment(completion_string); }

CXCompletionString              _20_getCursorCompletionString                   (CXCursor cursor)
                                                                                { return clang_getCursorCompletionString(cursor); }

unsigned                        _20_getCompletionNumFixIts                      (CXCodeCompleteResults *results, unsigned completion_index)
                                                                                { return clang_getCompletionNumFixIts(results, completion_index); }

CXString                        _20_getCompletionFixIt                          (CXCodeCompleteResults *results, unsigned completion_index, unsigned fixit_index, CXSourceRange *replacement_range)
                                                                                { return clang_getCompletionFixIt(results, completion_index, fixit_index, replacement_range); }

unsigned                        _20_defaultCodeCompleteOptions                  (void)
                                                                                { return clang_defaultCodeCompleteOptions(); }

CXCodeCompleteResults*          _20_codeCompleteAt                              (CXTranslationUnit TU, const char *complete_filename, unsigned complete_line, unsigned complete_column, struct CXUnsavedFile *unsaved_files, unsigned num_unsaved_files, unsigned options)
                                                                                { return clang_codeCompleteAt(TU, complete_filename, complete_line, complete_column, unsaved_files, num_unsaved_files, options); }

void                            _20_sortCodeCompletionResults                   (CXCompletionResult *Results, unsigned NumResults)
                                                                                { return clang_sortCodeCompletionResults(Results, NumResults); }

void                            _20_disposeCodeCompleteResults                  (CXCodeCompleteResults *Results)
                                                                                { return clang_disposeCodeCompleteResults(Results); }

unsigned                        _20_codeCompleteGetNumDiagnostics               (CXCodeCompleteResults *Results)
                                                                                { return clang_codeCompleteGetNumDiagnostics(Results); }

CXDiagnostic                    _20_codeCompleteGetDiagnostic                   (CXCodeCompleteResults *Results, unsigned Index)
                                                                                { return clang_codeCompleteGetDiagnostic(Results, Index); }

unsigned long long              _20_codeCompleteGetContexts                     (CXCodeCompleteResults *Results)
                                                                                { return clang_codeCompleteGetContexts(Results); }

enum CXCursorKind               _20_codeCompleteGetContainerKind                (CXCodeCompleteResults *Results, unsigned *IsIncomplete)
                                                                                { return clang_codeCompleteGetContainerKind(Results, IsIncomplete); }

CXString                        _20_codeCompleteGetContainerUSR                 (CXCodeCompleteResults *Results)
                                                                                { return clang_codeCompleteGetContainerUSR(Results); }

CXString                        _20_codeCompleteGetObjCSelector                 (CXCodeCompleteResults *Results)
                                                                                { return clang_codeCompleteGetObjCSelector(Results); }
