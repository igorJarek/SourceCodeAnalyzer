#include "12_CompilationDatabase_functions.h"

CXCompilationDatabase       _12_CompilationDatabase_fromDirectory               (const char *BuildDir, CXCompilationDatabase_Error *ErrorCode)
                                                                                { return clang_CompilationDatabase_fromDirectory(BuildDir, ErrorCode); }

void                        _12_CompilationDatabase_dispose                     (CXCompilationDatabase CompilationDatabase)
                                                                                { return clang_CompilationDatabase_dispose(CompilationDatabase); }

CXCompileCommands           _12_CompilationDatabase_getCompileCommands          (CXCompilationDatabase CompilationDatabase, const char *CompleteFileName)
                                                                                { return clang_CompilationDatabase_getCompileCommands(CompilationDatabase, CompleteFileName); }

CXCompileCommands           _12_CompilationDatabase_getAllCompileCommands       (CXCompilationDatabase CompilationDatabase)
                                                                                { return clang_CompilationDatabase_getAllCompileCommands(CompilationDatabase); }

void                        _12_CompileCommands_dispose                         (CXCompileCommands CompileCommands)
                                                                                { return clang_CompileCommands_dispose(CompileCommands); }

unsigned                    _12_CompileCommands_getSize                         (CXCompileCommands CompileCommands)
                                                                                { return clang_CompileCommands_getSize(CompileCommands); }

CXCompileCommand            _12_CompileCommands_getCommand                      (CXCompileCommands CompileCommands, unsigned I)
                                                                                { return clang_CompileCommands_getCommand(CompileCommands, I); }

CXString                    _12_CompileCommand_getDirectory                     (CXCompileCommand CompileCommand)
                                                                                { return clang_CompileCommand_getDirectory(CompileCommand); }

CXString                    _12_CompileCommand_getFilename                      (CXCompileCommand CompileCommand)
                                                                                { return clang_CompileCommand_getFilename(CompileCommand); }

unsigned                    _12_CompileCommand_getNumArgs                       (CXCompileCommand CompileCommand)
                                                                                { return clang_CompileCommand_getNumArgs(CompileCommand); }

CXString                    _12_CompileCommand_getArg                           (CXCompileCommand CompileCommand, unsigned I)
                                                                                { return clang_CompileCommand_getArg(CompileCommand, I); }

unsigned                    _12_CompileCommand_getNumMappedSources              (CXCompileCommand CompileCommand)
                                                                                { return clang_CompileCommand_getNumMappedSources(CompileCommand); }

CXString                    _12_CompileCommand_getMappedSourcePath              (CXCompileCommand CompileCommand, unsigned I)
                                                                                { return clang_CompileCommand_getMappedSourcePath(CompileCommand, I); }

CXString                    _12_CompileCommand_getMappedSourceContent           (CXCompileCommand CompileCommand, unsigned I)
                                                                                { return clang_CompileCommand_getMappedSourceContent(CompileCommand, I); }
