#pragma once

#include <clang-c/Index.h>
#include <clang-c/CXCompilationDatabase.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

CXCompilationDatabase	_12_CompilationDatabase_fromDirectory				(const char *BuildDir, CXCompilationDatabase_Error *ErrorCode);
void					_12_CompilationDatabase_dispose						(CXCompilationDatabase CompilationDatabase);
CXCompileCommands		_12_CompilationDatabase_getCompileCommands			(CXCompilationDatabase CompilationDatabase, const char *CompleteFileName);
CXCompileCommands		_12_CompilationDatabase_getAllCompileCommands		(CXCompilationDatabase CompilationDatabase);
void					_12_CompileCommands_dispose							(CXCompileCommands CompileCommands);
unsigned				_12_CompileCommands_getSize							(CXCompileCommands CompileCommands);
CXCompileCommand		_12_CompileCommands_getCommand						(CXCompileCommands CompileCommands, unsigned I);
CXString				_12_CompileCommand_getDirectory						(CXCompileCommand CompileCommand);
CXString 				_12_CompileCommand_getFilename						(CXCompileCommand CompileCommand);
unsigned 				_12_CompileCommand_getNumArgs						(CXCompileCommand CompileCommand);
CXString 				_12_CompileCommand_getArg							(CXCompileCommand CompileCommand, unsigned I);
unsigned 				_12_CompileCommand_getNumMappedSources				(CXCompileCommand CompileCommand);
CXString 				_12_CompileCommand_getMappedSourcePath				(CXCompileCommand CompileCommand, unsigned I);
CXString				_12_CompileCommand_getMappedSourceContent			(CXCompileCommand CompileCommand, unsigned I);
