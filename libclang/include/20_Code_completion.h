#pragma once

#include <clang-c/Index.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

// Clang Functions

enum CXCompletionChunkKind      _20_getCompletionChunkKind                      (CXCompletionString completion_string, unsigned chunk_number);                                          // 1.
CXString                        _20_getCompletionChunkText                      (CXCompletionString completion_string, unsigned chunk_number);                                          // 2.
CXCompletionString              _20_getCompletionChunkCompletionString          (CXCompletionString completion_string, unsigned chunk_number);                                          // 3.
unsigned                        _20_getNumCompletionChunks                      (CXCompletionString completion_string);                                                                 // 4.
unsigned                        _20_getCompletionPriority                       (CXCompletionString completion_string);                                                                 // 5.
enum CXAvailabilityKind         _20_getCompletionAvailability                   (CXCompletionString completion_string);                                                                 // 6.
unsigned                        _20_getCompletionNumAnnotations                 (CXCompletionString completion_string);                                                                 // 7.
CXString                        _20_getCompletionAnnotation                     (CXCompletionString completion_string, unsigned annotation_number);                                     // 8.
CXString                        _20_getCompletionParent                         (CXCompletionString completion_string, enum CXCursorKind *kind);                                        // 9.
CXString                        _20_getCompletionBriefComment                   (CXCompletionString completion_string);                                                                 // 10.
CXCompletionString              _20_getCursorCompletionString                   (CXCursor cursor);                                                                                      // 11.
unsigned                        _20_getCompletionNumFixIts                      (CXCodeCompleteResults *results, unsigned completion_index);                                            // 12.
CXString                        _20_getCompletionFixIt                          (CXCodeCompleteResults *results, unsigned completion_index, 
                                                                                 unsigned fixit_index, CXSourceRange *replacement_range);                                               // 13.
unsigned                        _20_defaultCodeCompleteOptions                  (void);                                                                                                 // 14.
CXCodeCompleteResults *         _20_codeCompleteAt                              (CXTranslationUnit TU, const char *complete_filename, unsigned complete_line, unsigned complete_column, 
                                                                                 struct CXUnsavedFile *unsaved_files, unsigned num_unsaved_files, unsigned options);                    // 15.
void                            _20_sortCodeCompletionResults                   (CXCompletionResult *Results, unsigned NumResults);                                                     // 16.
void                            _20_disposeCodeCompleteResults                  (CXCodeCompleteResults *Results);                                                                       // 17.
unsigned                        _20_codeCompleteGetNumDiagnostics               (CXCodeCompleteResults *Results);                                                                       // 18.
CXDiagnostic                    _20_codeCompleteGetDiagnostic                   (CXCodeCompleteResults *Results, unsigned Index);                                                       // 19.
unsigned long long              _20_codeCompleteGetContexts                     (CXCodeCompleteResults *Results);                                                                       // 20.
enum CXCursorKind               _20_codeCompleteGetContainerKind                (CXCodeCompleteResults *Results, unsigned *IsIncomplete);                                               // 21.
CXString                        _20_codeCompleteGetContainerUSR                 (CXCodeCompleteResults *Results);                                                                       // 22.
CXString                        _20_codeCompleteGetObjCSelector                 (CXCodeCompleteResults *Results);                                                                       // 23.
