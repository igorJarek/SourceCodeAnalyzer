
CXString            _9_getCursorUSR                         (CXCursor C)
                                                            { return clang_getCursorUSR(C); }

CXString            _9_constructUSR_ObjCClass               (const char *class_name)
                                                            { return clang_constructUSR_ObjCClass(class_name); }

CXString            _9_constructUSR_ObjCCategory            (const char *class_name, const char *category_name)
                                                            { return clang_constructUSR_ObjCCategory(class_name, category_name); }

CXString            _9_constructUSR_ObjCProtocol            (const char *protocol_name)
                                                            { return clang_constructUSR_ObjCProtocol(protocol_name); }

CXString            _9_constructUSR_ObjCIvar                (const char *name, CXString classUSR)
                                                            { return clang_constructUSR_ObjCIvar(name, classUSR); }

CXString            _9_constructUSR_ObjCMethod              (const char *name, unsigned isInstanceMethod, CXString classUSR)
                                                            { return clang_constructUSR_ObjCMethod(name, isInstanceMethod, classUSR); }

CXString            _9_constructUSR_ObjCProperty            (const char *property, CXString classUSR)
                                                            { return clang_constructUSR_ObjCProperty(property, classUSR); }

CXString            _9_getCursorSpelling                    (CXCursor C)
                                                            { return clang_getCursorSpelling(C); }

CXSourceRange       _9_Cursor_getSpellingNameRange          (CXCursor C, unsigned pieceIndex, unsigned options)
                                                            { return clang_Cursor_getSpellingNameRange(C, pieceIndex, options); }

unsigned            _9_PrintingPolicy_getProperty           (CXPrintingPolicy Policy, enum CXPrintingPolicyProperty Property)
                                                            { return clang_PrintingPolicy_getProperty(Policy, Property); }

void                _9_PrintingPolicy_setProperty           (CXPrintingPolicy Policy, enum CXPrintingPolicyProperty Property, unsigned Value)
                                                            { return clang_PrintingPolicy_setProperty(Policy, Property, Value); }

CXPrintingPolicy    _9_getCursorPrintingPolicy              (CXCursor C)
                                                            { return clang_getCursorPrintingPolicy(C); }

void                _9_PrintingPolicy_dispose               (CXPrintingPolicy Policy)
                                                            { return clang_PrintingPolicy_dispose(Policy); }

CXString            _9_getCursorPrettyPrinted               (CXCursor Cursor, CXPrintingPolicy Policy)
                                                            { return clang_getCursorPrettyPrinted(Cursor, Policy); }

CXString            _9_getCursorDisplayName                 (CXCursor C)
                                                            { return clang_getCursorDisplayName(C); }

CXCursor            _9_getCursorReferenced                  (CXCursor C)
                                                            { return clang_getCursorReferenced(C); }

CXCursor            _9_getCursorDefinition                  (CXCursor C)
                                                            { return clang_getCursorDefinition(C); }

unsigned            _9_isCursorDefinition                   (CXCursor C)
                                                            { return clang_isCursorDefinition(C); }

CXCursor            _9_getCanonicalCursor                   (CXCursor C)
                                                            { return clang_getCanonicalCursor(C); }

int                 _9_getObjCSelectorIndex                 (CXCursor C)
                                                            { return clang_Cursor_getObjCSelectorIndex(C); }

int                 _9_isDynamicCall                        (CXCursor C)
                                                            { return clang_Cursor_isDynamicCall(C); }

CXType              _9_getReceiverType                      (CXCursor C)
                                                            { return clang_Cursor_getReceiverType(C); }

unsigned            _9_getObjCPropertyAttributes            (CXCursor C, unsigned reserved)
                                                            { return clang_Cursor_getObjCPropertyAttributes(C, reserved); }

CXString            _9_getObjCPropertyGetterName            (CXCursor C)
                                                            { return clang_Cursor_getObjCPropertyGetterName(C); }

CXString            _9_getObjCPropertySetterName            (CXCursor C)
                                                            { return clang_Cursor_getObjCPropertySetterName(C); }

unsigned            _9_getObjCDeclQualifiers                (CXCursor C)
                                                            { return clang_Cursor_getObjCDeclQualifiers(C); }

unsigned            _9_isObjCOptional                       (CXCursor C)
                                                            { return clang_Cursor_isObjCOptional(C); }

unsigned            _9_isVariadic                           (CXCursor C)
                                                            { return clang_Cursor_isVariadic(C); }

unsigned            _9_isExternalSymbol                     (CXCursor C, CXString *language, CXString *definedIn, unsigned *isGenerated)
                                                            { return clang_Cursor_isExternalSymbol(C, language, definedIn, isGenerated); }

CXSourceRange       _9_getCommentRange                      (CXCursor C)
                                                            { return clang_Cursor_getCommentRange(C); }

CXString            _9_getRawCommentText                    (CXCursor C)
                                                            { return clang_Cursor_getRawCommentText(C); }

CXString            _9_getBriefCommentText                  (CXCursor C)
                                                            { return clang_Cursor_getBriefCommentText(C); }
