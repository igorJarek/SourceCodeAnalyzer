#include "5_Token_extraction_and_manipulation.h"
#include <Html/Html.h>

void _5_token_extraction(const CXTranslationUnit& translationUnit, const string& filePath)
{
    OutputTree outputTree;

    outputTree.addString(0, "5. Token extraction and manipulation : ");

    CXFile file = _8_getFile(translationUnit, filePath.c_str());

    const int64_t lineCount = countFileLines(filePath);
    if (lineCount == -1)
        outputTree.addString(1, "File is empty.");
    else
    {
        const int64_t lastLineColumns = countFileLineColumns(filePath, lineCount);
        if(lastLineColumns == -1)
            outputTree.addString(1, "Something is wrong with last line or file.");
        else
        {
            //  For first char '#' CXSourceLocation is <1, 1>
            //  For last  char ';' CXSourceLocation is <11, 2>
            /*
                1. |#pragma once
                2. |
                3. |class Class
                4. |{
                5. |    public:
                6. |        Class(void);
                7. |        ~Class(void);
                8. |        Class(const Class& classes);
                9. |
                10.|        void classMethod(void);
                11.|};
            */

            // tokenization whole file
            CXSourceLocation beginLocation  = _21_getLocation(translationUnit, file, 1, 1);
            CXSourceLocation endLocation    = _21_getLocation(translationUnit, file, static_cast<unsigned int>(lineCount), static_cast<unsigned int>(lastLineColumns));
            CXSourceRange    tokenizerRange = _21_getRange(beginLocation, endLocation);

            CXToken*         tokensOut      = nullptr;
            uint32_t         tokensNum      = 0;

            clang_tokenize(translationUnit, tokenizerRange, &tokensOut, &tokensNum);                                                                               // 6.

            outputTree.addString(1, "clang_tokenize [NumTokens] : ", tokensNum);

            if (tokensNum > 0)
            {
                outputTree.addString(1, "Tokens : ");

                for (uint32_t index{ 0 }; index < tokensNum; ++index)
                {
                    const CXToken&   token = tokensOut[index];
                    
                    CXTokenKind      tokenKind     = clang_getTokenKind(token);                                                                                    // 2.
                    CXString         tokenSpelling = clang_getTokenSpelling(translationUnit, token);                                                               // 3.
                    CXSourceLocation tokenLocation = clang_getTokenLocation(translationUnit, token);                                                               // 4.
                    CXSourceRange    tokenRange    = clang_getTokenExtent(translationUnit, token);                                                                 // 5.

                    CXCursor         cursor        = _10_getCursor(translationUnit, tokenLocation);
                    CXCursor         cursorRef     = _9_getCursorReferenced(cursor);

                    outputTree.addString(2, to_string(index + 1) + ")\tclang_getTokenSpelling : ", tokenSpelling);
                    outputTree.addString(3, "clang_getTokenKind : ", tokenKind);
                    outputTree.addString(3, "_10_getCursor(clang_getTokenLocation) : lib/cursors.cur -> ", saveBaseCXCursorInfo(&translationUnit, &cursor, InfoAction::ADD_INFO));
                    outputTree.addString(3, "_9_getCursorReferenced : lib/cursors.cur -> ", saveBaseCXCursorInfo(&translationUnit, &cursorRef, InfoAction::ADD_INFO));
                    outputTree.addCXSourceLocation(3, "clang_getTokenLocation : ", tokenLocation);
                    outputTree.addCXSourceRange(3, "clang_getTokenExtent : ", tokenRange);
                }
            }

            if (tokensOut)
                clang_disposeTokens(translationUnit, tokensOut, tokensNum);                                                                                        // 8.
        }
    }

    string saveFilePath{ filePath + TOKENS_FILE_EXT };
    if (!outputTree.saveToFile(saveFilePath))
        cout << "Couldn't save file : " << saveFilePath << endl;

    HTMLBuilder htmlBuilder;
    string tableID{ "TBL" };

    htmlBuilder.setIndexTitle(filePath + TOKENS_FILE_EXT + ".html");
    htmlBuilder.setFileNameHeader(filePath);
    htmlBuilder.setFilePathHeader(filePath + TOKENS_FILE_EXT + ".html");

    htmlBuilder.addTable("Token Informations", tableID, {"Category", "Token Count", "Token Spelling", "Additions Info", "Ranges", "Locations"});
    htmlBuilder.addTableRows(tableID, outputTree);

    if(!htmlBuilder.saveFile(filePath + TOKENS_FILE_EXT + ".html"))
        cout << "Couldn't save HTML file : " << saveFilePath + ".html" << endl;
}

CXToken*            _5_getToken             (CXTranslationUnit TU, CXSourceLocation Location)
                                            { return clang_getToken(TU, Location); }

CXTokenKind         _5_getTokenKind         (CXToken Token)
                                            { return clang_getTokenKind(Token); }

CXString            _5_getTokenSpelling     (CXTranslationUnit TU, CXToken Token)
                                            { return clang_getTokenSpelling(TU, Token); }

CXSourceLocation    _5_getTokenLocation     (CXTranslationUnit TU, CXToken Token)
                                            { return clang_getTokenLocation(TU, Token); }

CXSourceRange       _5_getTokenExtent       (CXTranslationUnit TU, CXToken Token)
                                            { return clang_getTokenExtent(TU, Token); }

void                _5_tokenize             (CXTranslationUnit TU, CXSourceRange Range, CXToken **Tokens, unsigned *NumTokens)
                                            { return clang_tokenize(TU, Range, Tokens, NumTokens); }

void                _5_annotateTokens       (CXTranslationUnit TU, CXToken *Tokens, unsigned NumTokens, CXCursor *Cursors)
                                            { return clang_annotateTokens(TU, Tokens, NumTokens, Cursors); }

void                _5_disposeTokens        (CXTranslationUnit TU, CXToken *Tokens, unsigned NumTokens)
                                            { return clang_disposeTokens(TU, Tokens, NumTokens); }
