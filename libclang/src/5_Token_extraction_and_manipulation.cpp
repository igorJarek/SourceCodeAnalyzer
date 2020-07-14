#include "5_Token_extraction_and_manipulation.h"

void _5_token_extraction(const CXTranslationUnit& translationUnit, const string& filePath)
{
    string strData;

    ADD_STRING_OUT_TEXT(0, "5. Token extraction and manipulation : ")

    CXFile file = _8_getFile(translationUnit, filePath.c_str());

    const int64_t lineCount = countFileLines(filePath);
    if (lineCount == -1)
        ADD_STRING_OUT_TEXT(1, "File is empty.")
    else
    {
        const int64_t lastLineColumns = countFileLineColumns(filePath, lineCount);
        if(lastLineColumns == -1)
            ADD_STRING_OUT_TEXT(1, "Something is wrong with last line or file.")
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

            ADD_STRING_OUT_NL(1, "clang_tokenize [NumTokens] : ", to_string(tokensNum))

            if (tokensNum > 0)
            {
                ADD_STRING_OUT_TEXT(1, "Tokens : ")

                for (uint32_t index{ 0 }; index < tokensNum; ++index)
                {
                    const CXToken&   token = tokensOut[index];
                    
                    CXTokenKind      tokenKind     = clang_getTokenKind(token);                                                                                    // 2.
                    CXString         tokenSpelling = clang_getTokenSpelling(translationUnit, token);                                                               // 3.
                    CXSourceLocation tokenLocation = clang_getTokenLocation(translationUnit, token);                                                               // 4.
                    CXSourceRange    tokenRange    = clang_getTokenExtent(translationUnit, token);                                                                 // 5.

                    CXCursor         cursor        = _10_getCursor(translationUnit, tokenLocation);

                    ADD_STRING_OUT_NL(2, to_string(index + 1) + ")\tclang_getTokenSpelling : ",         CXString2String(tokenSpelling))
                    ADD_STRING_OUT_NL(3, "clang_getTokenKind : ",                                       CXTokenKind2String(tokenKind))
                    ADD_STRING_OUT_NL(3, "_10_getCursor(clang_getTokenLocation) : lib/cursors.cur -> ", to_string(getBaseCXCursorInfo(&translationUnit, &cursor)))
                    ADD_STRING_OUT_NL(3, "clang_getTokenExtent : \n",                                   CXSourceRange2String(tokenRange, 4))
                }
            }

            if (tokensOut)
                clang_disposeTokens(translationUnit, tokensOut, tokensNum);                                                                                        // 8.
        }
    }

    string saveFilePath{ filePath + TOKENS_FILE_EXT };
    if (!saveToFile(saveFilePath, strData))
        cout << "Couldn't create file : " << saveFilePath << endl;
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
