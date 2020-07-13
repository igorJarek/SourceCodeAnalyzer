#include "0_1_Comment_introspection.h"

void _0_1_printCommentIntrospection(string& strData, const CXCursor& cursor, uint32_t curLevel, bool print /* = true */)
{
    CXComment                           parsedComment       = clang_Cursor_getParsedComment(cursor);                                                    // 1.

    CXCommentKind                       commentKind          = clang_Comment_getKind(parsedComment);                                                    // 2.
    unsigned                            numChildren          = clang_Comment_getNumChildren(parsedComment);                                             // 3.
    unsigned                            isWhitespace         = clang_Comment_isWhitespace(parsedComment);                                               // 5.
    unsigned                            trailingNewline      = clang_InlineContentComment_hasTrailingNewline(parsedComment);                            // 6.
    CXString                            textComment_getText  = clang_TextComment_getText(parsedComment);                                                // 7.
    CXString                            getInlineCommandName = clang_InlineCommandComment_getCommandName(parsedComment);                                // 8.
    CXCommentInlineCommandRenderKind    getRenderKind        = clang_InlineCommandComment_getRenderKind(parsedComment);                                 // 9.
    unsigned                            getNumArgs           = clang_InlineCommandComment_getNumArgs(parsedComment);                                    // 10.
    CXString                            getTagName           = clang_HTMLTagComment_getTagName(parsedComment);                                          // 12.
    unsigned                            isSelfClosing        = clang_HTMLStartTagComment_isSelfClosing(parsedComment);                                  // 13.
    unsigned                            getNumAttrs          = clang_HTMLStartTag_getNumAttrs(parsedComment);                                           // 14.
    CXString                            getBlockCommandName  = clang_BlockCommandComment_getCommandName(parsedComment);                                 // 17.
    unsigned                            getBlockNumArgs      = clang_BlockCommandComment_getNumArgs(parsedComment);                                     // 18.
    CXComment                           getParagraph         = clang_BlockCommandComment_getParagraph(parsedComment);                                   // 20.
    CXString                            getParamCParamName   = clang_ParamCommandComment_getParamName(parsedComment);                                   // 21.
    unsigned                            isParamIndexValid    = clang_ParamCommandComment_isParamIndexValid(parsedComment);                              // 22.
    unsigned                            getParamIndex        = clang_ParamCommandComment_getParamIndex(parsedComment);                                  // 23.
    unsigned                            isDirectionExplicit  = clang_ParamCommandComment_isDirectionExplicit(parsedComment);                            // 24.
    enum CXCommentParamPassDirection    getDirection         = clang_ParamCommandComment_getDirection(parsedComment);                                   // 25.
    CXString                            getTParamParamName   = clang_TParamCommandComment_getParamName(parsedComment);                                  // 26.
    unsigned                            isParamPositionValid = clang_TParamCommandComment_isParamPositionValid(parsedComment);                          // 27.
    unsigned                            getDepth             = clang_TParamCommandComment_getDepth(parsedComment);                                      // 28.  ???
    unsigned                            getTParamIndex       = clang_TParamCommandComment_getIndex(parsedComment, getDepth);                            // 29.  ???
    CXString                            verbatimBlockText    = clang_VerbatimBlockLineComment_getText(parsedComment);                                   // 30.
    CXString                            verbatomLineText     = clang_VerbatimLineComment_getText(parsedComment);                                        // 31.
    CXString                            asString             = clang_HTMLTagComment_getAsString(parsedComment);                                         // 32.
    CXString                            asHTML               = clang_FullComment_getAsHTML(parsedComment);                                              // 33.
    CXString                            asXML                = clang_FullComment_getAsXML(parsedComment);                                               // 34.

    ADD_STRING_OUT_TEXT(curLevel + 1, "0-1. Comment introspection : ")

    ADD_STRING_OUT_NL(curLevel + 2, "clang_Comment_getKind : ",                                 CXCommentKind2String(commentKind))

    if(commentKind != CXCommentKind::CXComment_Null)
    {
        ADD_STRING_OUT_NL(curLevel + 2, "clang_Comment_getNumChildren : ",                      to_string(numChildren))
        for(uint32_t index { 0 }; index < numChildren; ++index)
        {
            CXComment     comment = clang_Comment_getChild(parsedComment, index);                                                                       // 4.
            CXCommentKind kind    = clang_Comment_getKind(comment);                                                                                     // 2.
            ADD_STRING_OUT_NL(curLevel + 3, "clang_Comment_getChild [" + to_string(index) + "] : ", CXCommentKind2String(kind))
        }

        ADD_STRING_OUT_NL(curLevel + 2, "clang_Comment_isWhitespace : ",                        to_string(isWhitespace))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_InlineContentComment_hasTrailingNewline : ",     to_string(trailingNewline))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_TextComment_getText : ",                         CXString2String(textComment_getText))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_InlineCommandComment_getCommandName : ",         CXString2String(getInlineCommandName))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_InlineCommandComment_getRenderKind : ",          CXCommentInlineCommandRenderKind2String(getRenderKind))

        ADD_STRING_OUT_NL(curLevel + 2, "clang_InlineCommandComment_getNumArgs : ",             to_string(getNumArgs))
        for(uint32_t index { 0 }; index < getNumArgs; ++index)
        {
            CXString getArgText = clang_InlineCommandComment_getArgText(parsedComment, index);                                                          // 11.
            ADD_STRING_OUT_NL(curLevel + 3, "clang_InlineCommandComment_getArgText [" + to_string(index) + "] : ", CXString2String(getArgText))
        }

        ADD_STRING_OUT_NL(curLevel + 2, "clang_HTMLTagComment_getTagName : ",                   CXString2String(getTagName))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_HTMLStartTagComment_isSelfClosing : ",           to_string(isSelfClosing))

        ADD_STRING_OUT_NL(curLevel + 2, "clang_HTMLStartTag_getNumAttrs : ",                    to_string(getNumAttrs))
        for(uint32_t index { 0 }; index < getNumAttrs; ++index)
        {
            CXString getAttrName  = clang_HTMLStartTag_getAttrName(parsedComment, index);                                                               // 15.
            CXString getAttrValue = clang_HTMLStartTag_getAttrValue(parsedComment, index);                                                              // 16.

            ADD_STRING_OUT_NL(curLevel + 3, "clang_HTMLStartTag_getAttrName [" + to_string(index) + "] : ", CXString2String(getAttrName))
            ADD_STRING_OUT_NL(curLevel + 3, "clang_HTMLStartTag_getAttrValue [" + to_string(index) + "] : ", CXString2String(getAttrValue))
        }

        ADD_STRING_OUT_NL(curLevel + 2, "clang_BlockCommandComment_getCommandName : ",          CXString2String(getBlockCommandName))

        ADD_STRING_OUT_NL(curLevel + 2, "clang_BlockCommandComment_getNumArgs : ",              to_string(getBlockNumArgs))
        for(uint32_t index { 0 }; index < getBlockNumArgs; ++index)
        {
            CXString getArgText = clang_BlockCommandComment_getArgText(parsedComment, index);                                                           // 19.

            ADD_STRING_OUT_NL(curLevel + 3, "clang_BlockCommandComment_getArgText [" + to_string(index) + "] : ", CXString2String(getArgText))
        }

        ADD_STRING_OUT_NL(curLevel + 2, "clang_BlockCommandComment_getParagraph : ",            CXCommentKind2String(clang_Comment_getKind(getParagraph)))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_ParamCommandComment_getParamName : ",            CXString2String(getParamCParamName))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_ParamCommandComment_isParamIndexValid : ",       to_string(isParamIndexValid))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_ParamCommandComment_getParamIndex : ",           to_string(getParamIndex))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_ParamCommandComment_isDirectionExplicit : ",     to_string(isDirectionExplicit))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_ParamCommandComment_getDirection : ",            CXCommentParamPassDirection2String(getDirection))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_TParamCommandComment_getParamName : ",           CXString2String(getTParamParamName))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_TParamCommandComment_isParamPositionValid : ",   to_string(isParamPositionValid))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_TParamCommandComment_getDepth : ",               to_string(getDepth))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_TParamCommandComment_getIndex : ",               to_string(getTParamIndex))

        ADD_STRING_OUT_NL(curLevel + 2, "clang_VerbatimBlockLineComment_getText : ",            CXString2String(verbatimBlockText))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_VerbatimLineComment_getText : ",                 CXString2String(verbatomLineText))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_HTMLTagComment_getAsString : ",                  CXString2String(asString))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_FullComment_getAsHTML : ",                       CXString2String(asHTML))
        ADD_STRING_OUT_NL(curLevel + 2, "clang_FullComment_getAsXML : ",                        CXString2String(asXML))
    }
}

CXComment                               _0_1_getParsedComment                           (CXCursor Cursor)
                                                                                        { return clang_Cursor_getParsedComment(Cursor); }

enum CXCommentKind                      _0_1_Comment_getKind                            (CXComment Comment)
                                                                                        { return clang_Comment_getKind(Comment); }

unsigned                                _0_1_Comment_getNumChildren                     (CXComment Comment)
                                                                                        { return clang_Comment_getNumChildren(Comment); }

CXComment                               _0_1_Comment_getChild                           (CXComment Comment, unsigned ChildIdx)
                                                                                        { return clang_Comment_getChild(Comment, ChildIdx); }

unsigned                                _0_1_Comment_isWhitespace                       (CXComment Comment)
                                                                                        { return clang_Comment_isWhitespace(Comment); }

unsigned                                _0_1_InlineContentComment_hasTrailingNewline    (CXComment Comment)
                                                                                        { return clang_InlineContentComment_hasTrailingNewline(Comment); }

CXString                                _0_1_TextComment_getText                        (CXComment Comment)
                                                                                        { return clang_TextComment_getText(Comment); }

CXString                                _0_1_InlineCommandComment_getCommandName        (CXComment Comment)
                                                                                        { return clang_InlineCommandComment_getCommandName(Comment); }

enum CXCommentInlineCommandRenderKind   _0_1_InlineCommandComment_getRenderKind         (CXComment Comment)
                                                                                        { return clang_InlineCommandComment_getRenderKind(Comment); }

unsigned                                _0_1_InlineCommandComment_getNumArgs            (CXComment Comment)
                                                                                        { return clang_InlineCommandComment_getNumArgs(Comment); }

CXString                                _0_1_InlineCommandComment_getArgText            (CXComment Comment, unsigned ArgIdx)
                                                                                        { return clang_InlineCommandComment_getArgText(Comment, ArgIdx); }

CXString                                _0_1_HTMLTagComment_getTagName                  (CXComment Comment)
                                                                                        { return clang_HTMLTagComment_getTagName(Comment); }

unsigned                                _0_1_HTMLStartTagComment_isSelfClosing          (CXComment Comment)
                                                                                        { return clang_HTMLStartTagComment_isSelfClosing(Comment); }

unsigned                                _0_1_HTMLStartTag_getNumAttrs                   (CXComment Comment)
                                                                                        { return clang_HTMLStartTag_getNumAttrs(Comment); }

CXString                                _0_1_HTMLStartTag_getAttrName                   (CXComment Comment, unsigned AttrIdx)
                                                                                        { return clang_HTMLStartTag_getAttrName(Comment, AttrIdx); }

CXString                                _0_1_HTMLStartTag_getAttrValue                  (CXComment Comment, unsigned AttrIdx)
                                                                                        { return clang_HTMLStartTag_getAttrValue(Comment, AttrIdx); }

CXString                                _0_1_BlockCommandComment_getCommandName         (CXComment Comment)
                                                                                        { return clang_BlockCommandComment_getCommandName(Comment); }

unsigned                                _0_1_BlockCommandComment_getNumArgs             (CXComment Comment)
                                                                                        { return clang_BlockCommandComment_getNumArgs(Comment); }

CXString                                _0_1_BlockCommandComment_getArgText             (CXComment Comment, unsigned ArgIdx)
                                                                                        { return clang_BlockCommandComment_getArgText(Comment, ArgIdx); }

CXComment                               _0_1_BlockCommandComment_getParagraph           (CXComment Comment)
                                                                                        { return clang_BlockCommandComment_getParagraph(Comment); }

CXString                                _0_1_ParamCommandComment_getParamName           (CXComment Comment)
                                                                                        { return clang_ParamCommandComment_getParamName(Comment); }

unsigned                                _0_1_ParamCommandComment_isParamIndexValid      (CXComment Comment)
                                                                                        { return clang_ParamCommandComment_isParamIndexValid(Comment); }

unsigned                                _0_1_ParamCommandComment_getParamIndex          (CXComment Comment)
                                                                                        { return clang_ParamCommandComment_getParamIndex(Comment); }

unsigned                                _0_1_ParamCommandComment_isDirectionExplicit    (CXComment Comment)
                                                                                        { return clang_ParamCommandComment_isDirectionExplicit(Comment); }

enum CXCommentParamPassDirection        _0_1_ParamCommandComment_getDirection           (CXComment Comment)
                                                                                        { return clang_ParamCommandComment_getDirection(Comment); }

CXString                                _0_1_TParamCommandComment_getParamName          (CXComment Comment)
                                                                                        { return clang_TParamCommandComment_getParamName(Comment); }

unsigned                                _0_1_TParamCommandComment_isParamPositionValid  (CXComment Comment)
                                                                                        { return clang_TParamCommandComment_isParamPositionValid(Comment); }

unsigned                                _0_1_TParamCommandComment_getDepth              (CXComment Comment)
                                                                                        { return clang_TParamCommandComment_getDepth(Comment); }

unsigned                                _0_1_TParamCommandComment_getIndex              (CXComment Comment, unsigned Depth)
                                                                                        { return clang_TParamCommandComment_getIndex(Comment, Depth); }

CXString                                _0_1_VerbatimBlockLineComment_getText           (CXComment Comment)
                                                                                        { return clang_VerbatimBlockLineComment_getText(Comment); }

CXString                                _0_1_VerbatimLineComment_getText                (CXComment Comment)
                                                                                        { return clang_VerbatimLineComment_getText(Comment); }

CXString                                _0_1_HTMLTagComment_getAsString                 (CXComment Comment)
                                                                                        { return clang_HTMLTagComment_getAsString(Comment); }

CXString                                _0_1_FullComment_getAsHTML                      (CXComment Comment)
                                                                                        { return clang_FullComment_getAsHTML(Comment); }

CXString                                _0_1_FullComment_getAsXML                       (CXComment Comment)
                                                                                        { return clang_FullComment_getAsXML(Comment); }
