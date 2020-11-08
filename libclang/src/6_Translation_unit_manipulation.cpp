#include "6_Translation_unit_manipulation.h"
#include <html/Html.h>

CXTranslationUnit* _6_translation_unit_manipulation(CXIndex& index, const string& filePath)
{
    const string tUnitSavePath{ filePath + TUNIT_BIN_FILE_EXT };
    OutputTree outputTree;

    CXTranslationUnit*    translationUnit                      = new CXTranslationUnit;
    CXErrorCode           errorCode                            = clang_parseTranslationUnit2(index, 
                                                                                             filePath.c_str(), 
                                                                                             COMPILATION_ARGS, 
                                                                                             sizeof(COMPILATION_ARGS) / sizeof(const char*),
                                                                                             nullptr,
                                                                                             0,
                                                                                             CXTranslationUnit_None,  /* CXTranslationUnit_Flags */
                                                                                             translationUnit);                                                      // 7.

    _2_diagnostic_reporting(*translationUnit, filePath);

    if (errorCode == CXError_Success)
    {
        CXString          translationUnitSpelling              = clang_getTranslationUnitSpelling(*translationUnit);                                                // 1.
        uint32_t          defaultEditingTranslationUnitOptions = clang_defaultEditingTranslationUnitOptions();                                                      // 5.
        uint32_t          defaultSaveOptions                   = clang_defaultSaveOptions(*translationUnit);                                                        // 9.
        int32_t           saveTranslationUnit                  = clang_saveTranslationUnit(*translationUnit, tUnitSavePath.c_str(), CXSaveTranslationUnit_None);    // 10.
        uint32_t          defaultReparseOptions                = clang_defaultReparseOptions(*translationUnit);                                                     // 13.
        CXTUResourceUsage getCXTUResourceUsage                 = clang_getCXTUResourceUsage(*translationUnit);                                                      // 16.

        CXTargetInfo      translationUnitTargetInfo            = clang_getTranslationUnitTargetInfo(*translationUnit);                                              // 18.
        CXString          targetInfo_getTriple                 = clang_TargetInfo_getTriple(translationUnitTargetInfo);                                             // 20.
        int32_t           targetInfo_getPointerWidth           = clang_TargetInfo_getPointerWidth(translationUnitTargetInfo);                                       // 21.

        outputTree.addString(0, "6. Translation Unit Manipulation : ");

        outputTree.addString(1, "clang_parseTranslationUnit2 : ",                errorCode);
        outputTree.addString(1, "clang_getTranslationUnitSpelling : ",           translationUnitSpelling);
        outputTree.addString(1, "clang_defaultEditingTranslationUnitOptions : ", defaultEditingTranslationUnitOptions);
        outputTree.addString(1, "clang_defaultSaveOptions : ",                   defaultSaveOptions);
        outputTree.addString(1, "clang_saveTranslationUnit : ",                  saveTranslationUnit);
        outputTree.addString(1, "clang_defaultReparseOptions : ",                defaultReparseOptions);
        outputTree.addCXTUResourceUsage(1, "clang_getCXTUResourceUsage : ",      getCXTUResourceUsage);
        outputTree.addString(1, "clang_TargetInfo_getTriple : ",                 targetInfo_getTriple);
        outputTree.addString(1, "clang_TargetInfo_getPointerWidth : ",           targetInfo_getPointerWidth);

        clang_disposeCXTUResourceUsage(getCXTUResourceUsage);                                                                                                       // 17.
        clang_TargetInfo_dispose(translationUnitTargetInfo);                                                                                                        // 19.
    }
    else
    {
        outputTree.addString(1, "clang_parseTranslationUnit2 : " , errorCode);

        delete translationUnit;
        translationUnit = nullptr;
    }

    string saveFilePath{ filePath + TUNIT_FILE_EXT };
    if (!outputTree.saveToFile(saveFilePath))
        cout << "Couldn't create file : " << saveFilePath << endl;

    HTMLBuilder htmlBuilder;
    string tableID{ "TBL" };

    htmlBuilder.setIndexTitle(filePath + TUNIT_FILE_EXT + ".html");
    htmlBuilder.setFileNameHeader(filePath);
    htmlBuilder.setFilePathHeader(filePath + TUNIT_FILE_EXT + ".html");

    htmlBuilder.addTable("Abc", tableID, {"Category", "Function", "Resource Usage"});
    htmlBuilder.addTableRows(tableID, outputTree);

    htmlBuilder.saveFile(filePath + TUNIT_FILE_EXT + ".html");

    return translationUnit;
}

CXString                _6_getTranslationUnitSpelling               (CXTranslationUnit CTUnit)
                                                                    { return clang_getTranslationUnitSpelling(CTUnit); }

CXTranslationUnit       _6_createTranslationUnitFromSourceFile      (CXIndex CIdx, const char *source_filename, int num_clang_command_line_args, const char *const *clang_command_line_args, unsigned num_unsaved_files, struct CXUnsavedFile *unsaved_files)
                                                                    { return clang_createTranslationUnitFromSourceFile(CIdx, source_filename, num_clang_command_line_args, clang_command_line_args, num_unsaved_files, unsaved_files); }

CXTranslationUnit       _6_createTranslationUnit                    (CXIndex CIdx, const char *ast_filename)
                                                                    { return clang_createTranslationUnit(CIdx, ast_filename); }

enum CXErrorCode        _6_createTranslationUnit2                   (CXIndex CIdx, const char *ast_filename, CXTranslationUnit *out_TU)
                                                                    { return clang_createTranslationUnit2(CIdx, ast_filename, out_TU); }

unsigned                _6_defaultEditingTranslationUnitOptions     (void)
                                                                    { return clang_defaultEditingTranslationUnitOptions(); }

CXTranslationUnit       _6_parseTranslationUnit                     (CXIndex CIdx, const char *source_filename, const char *const *command_line_args, int num_command_line_args, struct CXUnsavedFile *unsaved_files, unsigned num_unsaved_files, unsigned options)
                                                                    { return clang_parseTranslationUnit(CIdx, source_filename, command_line_args, num_command_line_args, unsaved_files, num_unsaved_files, options); }

enum CXErrorCode        _6_parseTranslationUnit2                    (CXIndex CIdx, const char *source_filename, const char *const *command_line_args, int num_command_line_args, struct CXUnsavedFile *unsaved_files, unsigned num_unsaved_files, unsigned options, CXTranslationUnit *out_TU)
                                                                    { return clang_parseTranslationUnit2(CIdx, source_filename, command_line_args, num_command_line_args, unsaved_files, num_unsaved_files, options, out_TU); }

enum CXErrorCode        _6_parseTranslationUnit2FullArgv            (CXIndex CIdx, const char *source_filename, const char *const *command_line_args, int num_command_line_args, struct CXUnsavedFile *unsaved_files, unsigned num_unsaved_files, unsigned options, CXTranslationUnit *out_TU)
                                                                    { return clang_parseTranslationUnit2FullArgv(CIdx, source_filename, command_line_args, num_command_line_args, unsaved_files, num_unsaved_files, options, out_TU); }

unsigned                _6_defaultSaveOptions                       (CXTranslationUnit TU)
                                                                    { return clang_defaultSaveOptions(TU); }

int                     _6_saveTranslationUnit                      (CXTranslationUnit TU, const char *FileName, unsigned options)
                                                                    { return clang_saveTranslationUnit(TU, FileName, options); }

unsigned                _6_suspendTranslationUnit                   (CXTranslationUnit TU)
                                                                    { return clang_suspendTranslationUnit(TU); }

void                    _6_disposeTranslationUnit                   (CXTranslationUnit TU)
                                                                    { return clang_disposeTranslationUnit(TU); }

unsigned                _6_defaultReparseOptions                    (CXTranslationUnit TU)
                                                                    { return clang_defaultReparseOptions(TU); }

int                     _6_reparseTranslationUnit                   (CXTranslationUnit TU, unsigned num_unsaved_files, struct CXUnsavedFile *unsaved_files, unsigned options)
                                                                    { return clang_reparseTranslationUnit(TU, num_unsaved_files, unsaved_files, options); }

const char *            _6_getTUResourceUsageName                   (enum CXTUResourceUsageKind kind)
                                                                    { return clang_getTUResourceUsageName(kind); }

CXTUResourceUsage       _6_getCXTUResourceUsage                     (CXTranslationUnit TU)
                                                                    { return clang_getCXTUResourceUsage(TU); }

void                    _6_disposeCXTUResourceUsage                 (CXTUResourceUsage usage)
                                                                    { return clang_disposeCXTUResourceUsage(usage); }

CXTargetInfo            _6_getTranslationUnitTargetInfo             (CXTranslationUnit CTUnit)
                                                                    { return clang_getTranslationUnitTargetInfo(CTUnit); }

void                    _6_TargetInfo_dispose                       (CXTargetInfo Info)
                                                                    { return clang_TargetInfo_dispose(Info); }

CXString                _6_TargetInfo_getTriple                     (CXTargetInfo Info)
                                                                    { return clang_TargetInfo_getTriple(Info); }

int                     _6_TargetInfo_getPointerWidth               (CXTargetInfo Info)
                                                                    { return clang_TargetInfo_getPointerWidth(Info); }
