#pragma once

#include "LibPath.h"

#include <clang-c/Index.h>
#include "UtilityFunctions.h"
#include "11_String_manipulation_routines.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/*
    Used:

        1.  CXString            clang_getTranslationUnitSpelling            (CXTranslationUnit CTUnit)
        5.  unsigned            clang_defaultEditingTranslationUnitOptions  (void)
        7.  enum CXErrorCode    clang_parseTranslationUnit2                 (CXIndex CIdx, const char *source_filename, const char *const *command_line_args, int num_command_line_args, 
        9.  unsigned            clang_defaultSaveOptions                    (CXTranslationUnit TU)
        10. int                 clang_saveTranslationUnit                   (CXTranslationUnit TU, const char *FileName, unsigned options)  
        12. void                clang_disposeTranslationUnit                (CXTranslationUnit)
        13. unsigned            clang_defaultReparseOptions                 (CXTranslationUnit TU)
        15. const char *        clang_getTUResourceUsageName                (enum CXTUResourceUsageKind kind)
        16. CXTUResourceUsage   clang_getCXTUResourceUsage                  (CXTranslationUnit TU)
        17. void                clang_disposeCXTUResourceUsage              (CXTUResourceUsage usage)
        18. CXTargetInfo        clang_getTranslationUnitTargetInfo          (CXTranslationUnit CTUnit)
        19. void                clang_TargetInfo_dispose                    (CXTargetInfo Info)
        20. CXString            clang_TargetInfo_getTriple                  (CXTargetInfo Info)
        21. int                 clang_TargetInfo_getPointerWidth            (CXTargetInfo Info)

    Unused:
        2.  CXTranslationUnit   clang_createTranslationUnitFromSourceFile   (CXIndex CIdx, const char *source_filename, int num_clang_command_line_args, const char *const *clang_command_line_args,
                                                                            unsigned num_unsaved_files, struct CXUnsavedFile *unsaved_files)
        3.  CXTranslationUnit   clang_createTranslationUnit                 (CXIndex CIdx, const char *ast_filename)
        4.  enum CXErrorCode    clang_createTranslationUnit2                (CXIndex CIdx, const char *ast_filename, CXTranslationUnit *out_TU)
        6.  CXTranslationUnit   clang_parseTranslationUnit                  (CXIndex CIdx, const char *source_filename, const char *const *command_line_args, int num_command_line_args, 
                                                                            struct CXUnsavedFile *unsaved_files, unsigned num_unsaved_files, unsigned options)
        8.  enum CXErrorCode    clang_parseTranslationUnit2FullArgv         (CXIndex CIdx, const char *source_filename, const char *const *command_line_args, int num_command_line_args, 
                                                                            struct CXUnsavedFile *unsaved_files, unsigned num_unsaved_files, unsigned options, CXTranslationUnit *out_TU)
        11. unsigned            clang_suspendTranslationUnit                (CXTranslationUnit)
        14. int                 clang_reparseTranslationUnit                (CXTranslationUnit TU, unsigned num_unsaved_files, struct CXUnsavedFile *unsaved_files, unsigned options)
*/

CXTranslationUnit*      _6_translation_unit_manipulation            (CXIndex& index, const string& filePath);

CXString				_6_getTranslationUnitSpelling				(CXTranslationUnit CTUnit);                                                                                         // 1.
CXTranslationUnit		_6_createTranslationUnitFromSourceFile		(CXIndex CIdx, const char *source_filename, int num_clang_command_line_args, 
                                                                     const char *const *clang_command_line_args, unsigned num_unsaved_files, 
                                                                     struct CXUnsavedFile *unsaved_files);                                                                              // 2.
CXTranslationUnit		_6_createTranslationUnit					(CXIndex CIdx, const char *ast_filename);                                                                           // 3.
enum CXErrorCode		_6_createTranslationUnit2					(CXIndex CIdx, const char *ast_filename, CXTranslationUnit *out_TU);                                                // 4.
unsigned				_6_defaultEditingTranslationUnitOptions		(void);                                                                                                             // 5.
CXTranslationUnit		_6_parseTranslationUnit						(CXIndex CIdx, const char *source_filename, const char *const *command_line_args, int num_command_line_args, 
                                                                     struct CXUnsavedFile *unsaved_files, unsigned num_unsaved_files, unsigned options);                                // 6.
enum CXErrorCode		_6_parseTranslationUnit2					(CXIndex CIdx, const char *source_filename, const char *const *command_line_args, int num_command_line_args, 
                                                                     struct CXUnsavedFile *unsaved_files, unsigned num_unsaved_files, unsigned options, CXTranslationUnit *out_TU);     // 7.
enum CXErrorCode		_6_parseTranslationUnit2FullArgv			(CXIndex CIdx, const char *source_filename, const char *const *command_line_args, int num_command_line_args, 
                                                                     struct CXUnsavedFile *unsaved_files, unsigned num_unsaved_files, unsigned options, CXTranslationUnit *out_TU);     // 8.
unsigned				_6_defaultSaveOptions						(CXTranslationUnit TU);                                                                                             // 9.
int						_6_saveTranslationUnit						(CXTranslationUnit TU, const char *FileName, unsigned options);                                                     // 10.
unsigned				_6_suspendTranslationUnit					(CXTranslationUnit TU);                                                                                             // 11.
void					_6_disposeTranslationUnit					(CXTranslationUnit TU);                                                                                             // 12.
unsigned				_6_defaultReparseOptions					(CXTranslationUnit TU);                                                                                             // 13.
int						_6_reparseTranslationUnit					(CXTranslationUnit TU, unsigned num_unsaved_files, struct CXUnsavedFile *unsaved_files, unsigned options);          // 14.
const char *			_6_getTUResourceUsageName					(enum CXTUResourceUsageKind kind);                                                                                  // 15.
CXTUResourceUsage		_6_getCXTUResourceUsage						(CXTranslationUnit TU);                                                                                             // 16.
void					_6_disposeCXTUResourceUsage					(CXTUResourceUsage usage);                                                                                          // 17.
CXTargetInfo			_6_getTranslationUnitTargetInfo				(CXTranslationUnit CTUnit);                                                                                         // 18.
void					_6_TargetInfo_dispose						(CXTargetInfo Info);                                                                                                // 19.
CXString				_6_TargetInfo_getTriple						(CXTargetInfo Info);                                                                                                // 20.
int						_6_TargetInfo_getPointerWidth				(CXTargetInfo Info);                                                                                                // 21.
