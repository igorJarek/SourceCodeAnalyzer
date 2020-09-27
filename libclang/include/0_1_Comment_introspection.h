#pragma once

#include <clang-c/Documentation.h>
#include <UtilityFunctions.h>
#include <string>
#include <iostream>

using std::to_string;

/*
    For Doxygen documentation engine
    https://clang.llvm.org/doxygen/group__CINDEX__COMMENT.html
*/

/*

    Used:

        1. CXComment                               clang_Cursor_getParsedComment                   (CXCursor Cursor) 
        2. enum CXCommentKind                      clang_Comment_getKind                           (CXComment Comment)
        3. unsigned                                clang_Comment_getNumChildren                    (CXComment Comment)
        4. CXComment                               clang_Comment_getChild                          (CXComment Comment, unsigned ChildIdx)
        5. unsigned                                clang_Comment_isWhitespace                      (CXComment Comment)
        6. unsigned                                clang_InlineContentComment_hasTrailingNewline   (CXComment Comment)
        7. CXString                                clang_TextComment_getText                       (CXComment Comment)
        8. CXString                                clang_InlineCommandComment_getCommandName       (CXComment Comment)
        9. enum CXCommentInlineCommandRenderKind   clang_InlineCommandComment_getRenderKind        (CXComment Comment)
        10. unsigned                               clang_InlineCommandComment_getNumArgs           (CXComment Comment)
        11. CXString                               clang_InlineCommandComment_getArgText           (CXComment Comment, unsigned ArgIdx)
        12. CXString                               clang_HTMLTagComment_getTagName                 (CXComment Comment)
        13. unsigned                               clang_HTMLStartTagComment_isSelfClosing         (CXComment Comment)
        14. unsigned                               clang_HTMLStartTag_getNumAttrs                  (CXComment Comment)
        15. CXString                               clang_HTMLStartTag_getAttrName                  (CXComment Comment, unsigned AttrIdx)
        16. CXString                               clang_HTMLStartTag_getAttrValue                 (CXComment Comment, unsigned AttrIdx)
        17. CXString                               clang_BlockCommandComment_getCommandName        (CXComment Comment)
        18. unsigned                               clang_BlockCommandComment_getNumArgs            (CXComment Comment)
        19. CXString                               clang_BlockCommandComment_getArgText            (CXComment Comment, unsigned ArgIdx)
        20. CXComment                              clang_BlockCommandComment_getParagraph          (CXComment Comment)
        21. CXString                               clang_ParamCommandComment_getParamName          (CXComment Comment)
        22. unsigned                               clang_ParamCommandComment_isParamIndexValid     (CXComment Comment)
        23. unsigned                               clang_ParamCommandComment_getParamIndex         (CXComment Comment)
        24. unsigned                               clang_ParamCommandComment_isDirectionExplicit   (CXComment Comment)
        25. enum CXCommentParamPassDirection       clang_ParamCommandComment_getDirection          (CXComment Comment)
        26. CXString                               clang_TParamCommandComment_getParamName         (CXComment Comment)
        27. unsigned                               clang_TParamCommandComment_isParamPositionValid (CXComment Comment)
        28. unsigned                               clang_TParamCommandComment_getDepth             (CXComment Comment)
        29. unsigned                               clang_TParamCommandComment_getIndex             (CXComment Comment, unsigned Depth)
        30. CXString                               clang_VerbatimBlockLineComment_getText          (CXComment Comment)
        31. CXString                               clang_VerbatimLineComment_getText               (CXComment Comment)
        32. CXString                               clang_HTMLTagComment_getAsString                (CXComment Comment) 
        33. CXString                               clang_FullComment_getAsHTML                     (CXComment Comment) 
        34. CXString                               clang_FullComment_getAsXML                      (CXComment Comment)

    Unused:

*/

// Print Function

void _0_1_printCommentIntrospection(string& strData, const CXCursor& cursor, uint32_t curLevel, bool print = true);

// Clang Functions

CXComment                               _0_1_getParsedComment                           (CXCursor Cursor);                          // 1.
enum CXCommentKind                      _0_1_Comment_getKind                            (CXComment Comment);                        // 2.
unsigned                                _0_1_Comment_getNumChildren                     (CXComment Comment);                        // 3.
CXComment                               _0_1_Comment_getChild                           (CXComment Comment, unsigned ChildIdx);     // 4.
unsigned                                _0_1_Comment_isWhitespace                       (CXComment Comment);                        // 5.
unsigned                                _0_1_InlineContentComment_hasTrailingNewline    (CXComment Comment);                        // 6.
CXString                                _0_1_TextComment_getText                        (CXComment Comment);                        // 7.
CXString                                _0_1_InlineCommandComment_getCommandName        (CXComment Comment);                        // 8.
enum CXCommentInlineCommandRenderKind   _0_1_InlineCommandComment_getRenderKind         (CXComment Comment);                        // 9.
unsigned                                _0_1_InlineCommandComment_getNumArgs            (CXComment Comment);                        // 10.
CXString                                _0_1_InlineCommandComment_getArgText            (CXComment Comment, unsigned ArgIdx);       // 11.
CXString                                _0_1_HTMLTagComment_getTagName                  (CXComment Comment);                        // 12.
unsigned                                _0_1_HTMLStartTagComment_isSelfClosing          (CXComment Comment);                        // 13.
unsigned                                _0_1_HTMLStartTag_getNumAttrs                   (CXComment Comment);                        // 14.
CXString                                _0_1_HTMLStartTag_getAttrName                   (CXComment Comment, unsigned AttrIdx);      // 15.
CXString                                _0_1_HTMLStartTag_getAttrValue                  (CXComment Comment, unsigned AttrIdx);      // 16.
CXString                                _0_1_BlockCommandComment_getCommandName         (CXComment Comment);                        // 17.
unsigned                                _0_1_BlockCommandComment_getNumArgs             (CXComment Comment);                        // 18.
CXString                                _0_1_BlockCommandComment_getArgText             (CXComment Comment, unsigned ArgIdx);       // 19.
CXComment                               _0_1_BlockCommandComment_getParagraph           (CXComment Comment);                        // 20.
CXString                                _0_1_ParamCommandComment_getParamName           (CXComment Comment);                        // 21.
unsigned                                _0_1_ParamCommandComment_isParamIndexValid      (CXComment Comment);                        // 22.
unsigned                                _0_1_ParamCommandComment_getParamIndex          (CXComment Comment);                        // 23.
unsigned                                _0_1_ParamCommandComment_isDirectionExplicit    (CXComment Comment);                        // 24.
enum CXCommentParamPassDirection        _0_1_ParamCommandComment_getDirection           (CXComment Comment);                        // 25.
CXString                                _0_1_TParamCommandComment_getParamName          (CXComment Comment);                        // 26.
unsigned                                _0_1_TParamCommandComment_isParamPositionValid  (CXComment Comment);                        // 27.
unsigned                                _0_1_TParamCommandComment_getDepth              (CXComment Comment);                        // 28.
unsigned                                _0_1_TParamCommandComment_getIndex              (CXComment Comment, unsigned Depth);        // 29.
CXString                                _0_1_VerbatimBlockLineComment_getText           (CXComment Comment);                        // 30.
CXString                                _0_1_VerbatimLineComment_getText                (CXComment Comment);                        // 31.
CXString                                _0_1_HTMLTagComment_getAsString                 (CXComment Comment);                        // 32.
CXString                                _0_1_FullComment_getAsHTML                      (CXComment Comment);                        // 33.
CXString                                _0_1_FullComment_getAsXML                       (CXComment Comment);                        // 34.
