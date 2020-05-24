#pragma once

#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

enum CXCompletionChunkKind      _20_getCompletionChunkKind                      (CXCompletionString completion_string, unsigned chunk_number);
CXString                        _20_getCompletionChunkText                      (CXCompletionString completion_string, unsigned chunk_number);
CXCompletionString              _20_getCompletionChunkCompletionString          (CXCompletionString completion_string, unsigned chunk_number);
unsigned                        _20_getNumCompletionChunks                      (CXCompletionString completion_string);
unsigned                        _20_getCompletionPriority                       (CXCompletionString completion_string);
enum CXAvailabilityKind         _20_getCompletionAvailability                   (CXCompletionString completion_string);
unsigned                        _20_getCompletionNumAnnotations                 (CXCompletionString completion_string);
CXString                        _20_getCompletionAnnotation                     (CXCompletionString completion_string, unsigned annotation_number);
CXString                        _20_getCompletionParent                         (CXCompletionString completion_string, enum CXCursorKind *kind);
CXString                        _20_getCompletionBriefComment                   (CXCompletionString completion_string);
CXCompletionString              _20_getCursorCompletionString                   (CXCursor cursor);
unsigned                        _20_getCompletionNumFixIts                      (CXCodeCompleteResults *results, unsigned completion_index);
CXString                        _20_getCompletionFixIt                          (CXCodeCompleteResults *results, unsigned completion_index, unsigned fixit_index, CXSourceRange *replacement_range);
unsigned                        _20_defaultCodeCompleteOptions                  (void);
CXCodeCompleteResults *         _20_codeCompleteAt                              (CXTranslationUnit TU, const char *complete_filename, unsigned complete_line, unsigned complete_column, struct CXUnsavedFile *unsaved_files, unsigned num_unsaved_files, unsigned options);
void                            _20_sortCodeCompletionResults                   (CXCompletionResult *Results, unsigned NumResults);
void                            _20_disposeCodeCompleteResults                  (CXCodeCompleteResults *Results);
unsigned                        _20_codeCompleteGetNumDiagnostics               (CXCodeCompleteResults *Results);
CXDiagnostic                    _20_codeCompleteGetDiagnostic                   (CXCodeCompleteResults *Results, unsigned Index);
unsigned long long              _20_codeCompleteGetContexts                     (CXCodeCompleteResults *Results);
enum CXCursorKind               _20_codeCompleteGetContainerKind                (CXCodeCompleteResults *Results, unsigned *IsIncomplete);
CXString                        _20_codeCompleteGetContainerUSR                 (CXCodeCompleteResults *Results);
CXString                        _20_codeCompleteGetObjCSelector                 (CXCodeCompleteResults *Results);
