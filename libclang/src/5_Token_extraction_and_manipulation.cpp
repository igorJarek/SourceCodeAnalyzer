#include "5_Token_extraction_and_manipulation.h"

void _5_token_extraction(const CXTranslationUnit& translationUnit, const string& filePath)
{
    string strData{ "Token extraction and manipulation : \n" };
    uint32_t tOffset{ 1 };

    CXFile file = _8_getFile(translationUnit, filePath.c_str());

    int64_t lineCount = countFileLines(filePath);
    if (lineCount == -1)
        strData += tabOffset(tOffset) + "File is empty." + '\n';
    else
    {
        int64_t lastLineColumns = countFileLineColumns(filePath, lineCount);
        if(lastLineColumns == -1)
            strData += tabOffset(tOffset) + "Something is wrong with last line oraz file." + '\n';
        else
        {
            //  For first char '#' CXSourceLocation is <1, 1>
            //  For last  char ';' CXSourceLocation is <11, 2>
            /*
                1. #pragma once
                2.
                3. class Class
                4. {
                5.		public:
                6.			Class(void);
                7.			~Class(void);
                8.			Class(const Class& classes);
                9.
                10.			void classMethod(void);
                11.	};
            */

            CXSourceLocation beginLocation = _21_getLocation(translationUnit, file, 1, 1);
            CXSourceLocation endLocation   = _21_getLocation(translationUnit, file, lineCount, lastLineColumns);

            CXSourceRange tokenizerRange = _21_getRange(beginLocation, endLocation);

            CXCursor* cursorsOut = nullptr;
            CXToken*  tokensOut = nullptr;
            uint32_t  tokensNum = 0;

            clang_tokenize(translationUnit, tokenizerRange, &tokensOut, &tokensNum);											// 6.

            if (tokensNum > 0)
            {
                strData += tabOffset(tOffset) + "Token count : " + to_string(tokensNum) + '\n';
                strData += tabOffset(tOffset) + "Tokens :" + '\n';

                clang_annotateTokens(translationUnit, tokensOut, tokensNum, cursorsOut);										// 7.

                for (uint32_t index{0}; index < tokensNum; ++index)
                {
                    const CXToken token = tokensOut[index];
                    
                    CXTokenKind			tokenKind		= clang_getTokenKind(token);											// 2.
                    CXString			tokenSpelling	= clang_getTokenSpelling(translationUnit, token);						// 3.
                    CXSourceLocation	tokenLoc		= clang_getTokenLocation(translationUnit, token);						// 4.   unused
                    CXSourceRange		tokenRange		= clang_getTokenExtent(translationUnit, token);							// 5.

                    strData += 
                        tabOffset(tOffset + 1) +  to_string(index + 1) + ")\t" +  _11_CXString2String(tokenSpelling) + '\n' +
                        tabOffset(tOffset + 2) + "clang_getTokenKind: " + CXTokenKind2String(tokenKind) + '\n' +
                        tabOffset(tOffset + 2) + "clang_getTokenExtent: " + '\n' +
                        CXSourceRange2String(tokenRange, tOffset + 3);
                }
            }

            if (tokensOut)
                clang_disposeTokens(translationUnit, tokensOut, tokensNum);														// 8.
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
