#include "5_Token_extraction_and_manipulation.h"

void _5_token_extraction(const CXTranslationUnit& translationUnit, const string& filePath)
{
    string strData;

    ADD_STRING_OUT_NAME(0, "5. Token extraction and manipulation : ")

    CXFile file = _8_getFile(translationUnit, filePath.c_str());

    const int64_t lineCount = countFileLines(filePath);
    if (lineCount == -1)
        ADD_STRING_OUT_NAME(1, "File is empty.")
    else
    {
        const int64_t lastLineColumns = countFileLineColumns(filePath, lineCount);
        if(lastLineColumns == -1)
            ADD_STRING_OUT_NAME(1, "Something is wrong with last line or file.")
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
            CXSourceLocation endLocation    = _21_getLocation(translationUnit, file, lineCount, lastLineColumns);
            CXSourceRange    tokenizerRange = _21_getRange(beginLocation, endLocation);

            CXToken*         tokensOut      = nullptr;
            uint32_t         tokensNum      = 0;

            _5_tokenize(translationUnit, tokenizerRange, &tokensOut, &tokensNum);                                                                               // 6.

            ADD_STRING_OUT_NL(1, "_5_tokenize [NumTokens] : ", to_string(tokensNum))

            if (tokensNum > 0)
            {
                ADD_STRING_OUT_NAME(1, "Tokens : ")

                for (uint32_t index{ 0 }; index < tokensNum; ++index)
                {
                    const CXToken&   token = tokensOut[index];
                    
                    CXTokenKind      tokenKind     = _5_getTokenKind(token);                                                                                    // 2.
                    CXString         tokenSpelling = _5_getTokenSpelling(translationUnit, token);                                                               // 3.
                    CXSourceLocation tokenLocation =  clang_getTokenLocation  (translationUnit, token);                                                         // 4.
                    CXSourceRange    tokenRange    = _5_getTokenExtent(translationUnit, token);                                                                 // 5.

                    CXCursor cursor = _10_getCursor(translationUnit, tokenLocation);

                    ADD_STRING_OUT_NL(2, to_string(index + 1) + ")\t_5_getTokenSpelling : ",  _11_CXString2String(tokenSpelling))
                    ADD_STRING_OUT_NL(3, "_5_getTokenKind : ",                                CXTokenKind2String(tokenKind))
                    ADD_STRING_OUT_NL(3, "_5_annotateTokens [Cursors] : lib/cursors.cur -> ", to_string(saveBaseCXCursorInfo(translationUnit, cursor)))
                    ADD_STRING_OUT_NL(3, "_5_getTokenExtent : \n",                            CXSourceRange2String(tokenRange, 4))
                }
            }

            if (tokensOut)
                _5_disposeTokens(translationUnit, tokensOut, tokensNum);                                                                                        // 8.
        }
    }

    string saveFilePath{ filePath + ".tokens" };
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
