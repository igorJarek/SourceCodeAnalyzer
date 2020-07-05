#pragma once

#include <clang-c/Index.h>
#include <clang-c/CXCompilationDatabase.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

CXCompilationDatabase   _12_CompilationDatabase_fromDirectory               (const char *BuildDir, CXCompilationDatabase_Error *ErrorCode);                 // 1.
void                    _12_CompilationDatabase_dispose                     (CXCompilationDatabase CompilationDatabase);                                    // 2.
CXCompileCommands       _12_CompilationDatabase_getCompileCommands          (CXCompilationDatabase CompilationDatabase, const char *CompleteFileName);      // 3.
CXCompileCommands       _12_CompilationDatabase_getAllCompileCommands       (CXCompilationDatabase CompilationDatabase);                                    // 4.
void                    _12_CompileCommands_dispose                         (CXCompileCommands CompileCommands);                                            // 5.
unsigned                _12_CompileCommands_getSize                         (CXCompileCommands CompileCommands);                                            // 6.
CXCompileCommand        _12_CompileCommands_getCommand                      (CXCompileCommands CompileCommands, unsigned I);                                // 7.
CXString                _12_CompileCommand_getDirectory                     (CXCompileCommand CompileCommand);                                              // 8.
CXString                _12_CompileCommand_getFilename                      (CXCompileCommand CompileCommand);                                              // 9.
unsigned                _12_CompileCommand_getNumArgs                       (CXCompileCommand CompileCommand);                                              // 10.
CXString                _12_CompileCommand_getArg                           (CXCompileCommand CompileCommand, unsigned I);                                  // 11.
unsigned                _12_CompileCommand_getNumMappedSources              (CXCompileCommand CompileCommand);                                              // 12.
CXString                _12_CompileCommand_getMappedSourcePath              (CXCompileCommand CompileCommand, unsigned I);                                  // 13.
CXString                _12_CompileCommand_getMappedSourceContent           (CXCompileCommand CompileCommand, unsigned I);                                  // 14.
