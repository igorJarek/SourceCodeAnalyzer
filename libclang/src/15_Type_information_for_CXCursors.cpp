#include "15_Type_information_for_CXCursors.h"

void _15_printTypeInformationForCXCursors(const CXTranslationUnit& translationUnit, string& strData, const CXCursor& cursor, uint32_t curLevel, bool print /* = true */)
{
    CXType                      cursorType                              = clang_getCursorType                           (cursor);                           // 1
    CXString                    typeSpelling                            = clang_getTypeSpelling                         (cursorType);                       // 2.

    if (cursorType.kind == CXType_Invalid || cursorType.kind == CXType_Unexposed)
    {
        ADD_STRING_OUT_NAME(curLevel + 1, "15. Type information for CXCursors : ")
        ADD_STRING_OUT_NL  (curLevel + 2, "clang_getTypeSpelling : ", CXString2String(typeSpelling))

        return;
    }

    CXType                      typedefDeclUnderlyingType               = clang_getTypedefDeclUnderlyingType            (cursor);                           // 3.
    CXType                      enumDeclIntegerType                     = clang_getEnumDeclIntegerType                  (cursor);                           // 4.
    int64_t                     enumConstantDeclValue                   = clang_getEnumConstantDeclValue                (cursor);                           // 5.
    uint64_t                    enumConstantDeclUnsignedValue           = clang_getEnumConstantDeclUnsignedValue        (cursor);                           // 6.
    int32_t                     fieldDeclBitWidth                       = clang_getFieldDeclBitWidth                    (cursor);                           // 7.
    int32_t                     numArguments                            = clang_Cursor_getNumArguments                  (cursor);                           // 8.

    int32_t                     cursorNumTemplateArguments              = clang_Cursor_getNumTemplateArguments          (cursor);                           // 10.
    vector<string>              templateArgumentKindStrings;
    vector<string>              templateArgumentTypeStrings;
    vector<string>              templateArgumentValueStrings;
    vector<string>              templateArgumentUnsignedValueStrings;

    for (int32_t index{ 0 }; index < cursorNumTemplateArguments; ++index)
    {
        CXTemplateArgumentKind  templateArgumentKind = clang_Cursor_getTemplateArgumentKind(cursor, index);                                                 // 11.
        templateArgumentKindStrings.push_back(CXTemplateArgumentKind2String(templateArgumentKind));

        CXType templateArgumentType = clang_Cursor_getTemplateArgumentType(cursor, index);                                                                  // 12.
        templateArgumentTypeStrings.push_back(CXType2String(templateArgumentType));

        int64_t templateArgumentValue = clang_Cursor_getTemplateArgumentValue(cursor, index);                                                               // 13.
        templateArgumentValueStrings.push_back(to_string(templateArgumentValue));

        uint64_t templateArgumentUnsignedValue = clang_Cursor_getTemplateArgumentUnsignedValue (cursor, index);                                             // 14.
        templateArgumentUnsignedValueStrings.push_back(to_string(templateArgumentUnsignedValue));
    }

    CXType                      canonicalType                           = clang_getCanonicalType                        (cursorType);                       // 16.
    uint32_t                    isConstQualifiedType                    = clang_isConstQualifiedType                    (cursorType);                       // 17.
    uint32_t                    isMacroFunctionLike                     = clang_Cursor_isMacroFunctionLike              (cursor);                           // 18.
    uint32_t                    isMacroBuiltin                          = clang_Cursor_isMacroBuiltin                   (cursor);                           // 19.
    uint32_t                    isFunctionInlined                       = clang_Cursor_isFunctionInlined                (cursor);                           // 20.
    uint32_t                    isVolatileQualifiedType                 = clang_isVolatileQualifiedType                 (cursorType);                       // 21.
    uint32_t                    isRestrictQualifiedType                 = clang_isRestrictQualifiedType                 (cursorType);                       // 22.
    uint32_t                    getAddressSpace                         = clang_getAddressSpace                         (cursorType);                       // 23.
    CXString                    getTypedefName                          = clang_getTypedefName                          (cursorType);                       // 24.
    CXType                      getPointeeType                          = clang_getPointeeType                          (cursorType);                       // 25.
    CXCursor                    getTypeDeclaration                      = clang_getTypeDeclaration                      (cursorType);                       // 26.
    CXString                    typeKindSpelling                        = clang_getTypeKindSpelling                     (cursorType.kind);                  // 29.
    CXCallingConv               functionTypeCallingConv                 = clang_getFunctionTypeCallingConv              (cursorType);                       // 30.
    CXType                      resultType                              = clang_getResultType                           (cursorType);                       // 31.
    int32_t                     exceptionSpecificationType              = clang_getExceptionSpecificationType           (cursorType);                       // 32.
    int32_t                     numArgTypes                             = clang_getNumArgTypes                          (cursorType);                       // 33.
    uint32_t                    isFunctionTypeVariadic                  = clang_isFunctionTypeVariadic                  (cursorType);                       // 40.
    CXType                      cursorResultType                        = clang_getCursorResultType                     (cursor);                           // 41.
    int32_t                     cursorExceptionSpecificationType        = clang_getCursorExceptionSpecificationType     (cursor);                           // 42.
    uint32_t                    isPODType                               = clang_isPODType                               (cursorType);                       // 43.
    CXType                      elementType                             = clang_getElementType                          (cursorType);                       // 44.
    int64_t                     numElements                             = clang_getNumElements                          (cursorType);                       // 45.
    CXType                      arrayElementType                        = clang_getArrayElementType                     (cursorType);                       // 46.
    int64_t                     arraySize                               = clang_getArraySize                            (cursorType);                       // 47.
    CXType                      namedType                               = clang_Type_getNamedType                       (cursorType);                       // 48.
    uint32_t                    isTransparentTagTypedef                 = clang_Type_isTransparentTagTypedef            (cursorType);                       // 49.
    CXTypeNullabilityKind       getNullability                          = clang_Type_getNullability                     (cursorType);                       // 50.
    int64_t                     alignOf                                 = clang_Type_getAlignOf                         (cursorType);                       // 51.
    CXType                      classType                               = clang_Type_getClassType                       (cursorType);                       // 52.
    int64_t                     sizeOf                                  = clang_Type_getSizeOf                          (cursorType);                       // 53.
    CXType                      modifiedType                            = clang_Type_getModifiedType                    (cursorType);                       // 55.
    int64_t                     offsetOfField                           = clang_Cursor_getOffsetOfField                 (cursor);                           // 56.
    uint32_t                    isAnonymous                             = clang_Cursor_isAnonymous                      (cursor);                           // 57.
    uint32_t                    isAnonymousRecordDecl                   = clang_Cursor_isAnonymousRecordDecl            (cursor);                           // 58.
    uint32_t                    isInlineNamespace                       = clang_Cursor_isInlineNamespace                (cursor);                           // 59.
    int32_t                     typeNumTemplateArguments                = clang_Type_getNumTemplateArguments            (cursorType);                       // 60.
    CXRefQualifierKind          refQualifier                            = clang_Type_getCXXRefQualifier                 (cursorType);                       // 62.
    int32_t                     isBitField                              = clang_Cursor_isBitField                       (cursor);                           // 63.
    int32_t                     isVirtualBase                           = clang_isVirtualBase                           (cursor);                           // 64.
    CX_CXXAccessSpecifier       accessSpecifier                         = clang_getCXXAccessSpecifier                   (cursor);                           // 65.
    CX_StorageClass             storageClass                            = clang_Cursor_getStorageClass                  (cursor);                           // 66.

    uint32_t                    numOverloadedDecls                      = clang_getNumOverloadedDecls                   (cursor);                           // 67.

    ADD_STRING_OUT_NAME(curLevel + 1, "15. Type information for CXCursors : ")

    ADD_STRING_OUT_NL(curLevel + 2, "clang_getTypeSpelling : ",                           CXString2String(typeSpelling))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getTypedefDeclUnderlyingType : ",              CXType2String(typedefDeclUnderlyingType))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getEnumDeclIntegerType : ",                    CXType2String(enumDeclIntegerType))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getEnumConstantDeclValue : ",                  to_string(enumConstantDeclValue))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getEnumConstantDeclUnsignedValue : ",          to_string(enumConstantDeclUnsignedValue))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getFieldDeclBitWidth : ",                      to_string(fieldDeclBitWidth))

    ADD_STRING_OUT_NL(curLevel + 2, "clang_Cursor_getNumArguments : ",                    to_string(numArguments))
    for (int32_t index{ 0 }; index < numArguments; ++index)
    {
        CXCursor cursor_getArgument = clang_Cursor_getArgument(cursor, index);                                                                              // 9.
        ADD_STRING_OUT_IF_NL(curLevel + 3, "clang_Cursor_getArgument : lib/cursors.cur -> ", to_string(saveBaseCXCursorInfo(translationUnit, cursor_getArgument)))
    }

    ADD_STRING_OUT_NL(curLevel + 2, "clang_Cursor_getNumTemplateArguments : ",            to_string(cursorNumTemplateArguments))

    for (int32_t index{ 0 }; index < cursorNumTemplateArguments; ++index)
    {
        ADD_STRING_OUT_NL(curLevel + 3, "clang_Cursor_getTemplateArgumentKind : ",          templateArgumentKindStrings[index])
        ADD_STRING_OUT_NL(curLevel + 3, "clang_Cursor_getTemplateArgumentType : ",          templateArgumentTypeStrings[index])
        ADD_STRING_OUT_NL(curLevel + 3, "clang_Cursor_getTemplateArgumentValue : ",         templateArgumentValueStrings[index])
        ADD_STRING_OUT_NL(curLevel + 3, "clang_Cursor_getTemplateArgumentUnsignedValue : ", templateArgumentUnsignedValueStrings[index])
    }

    ADD_STRING_OUT_NL(curLevel + 2, "clang_getCanonicalType : ",                            CXType2String(canonicalType))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_isConstQualifiedType : ",                        to_string(isConstQualifiedType))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_Cursor_isMacroFunctionLike : ",                  to_string(isMacroFunctionLike))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_Cursor_isMacroBuiltin : ",                       to_string(isMacroBuiltin))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_Cursor_isFunctionInlined : ",                    to_string(isFunctionInlined))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_isVolatileQualifiedType : ",                     to_string(isVolatileQualifiedType))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_isRestrictQualifiedType : ",                     to_string(isRestrictQualifiedType))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getAddressSpace : ",                             to_string(getAddressSpace))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getTypedefName : ",                              CXString2String(getTypedefName))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getPointeeType : ",                              CXType2String(getPointeeType))
    ADD_STRING_OUT_IF_NL(curLevel + 2, "clang_getTypeDeclaration : lib/cursors.cur -> ",    to_string(saveBaseCXCursorInfo(translationUnit, getTypeDeclaration)))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getTypeKindSpelling : ",                         CXString2String(typeKindSpelling))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getFunctionTypeCallingConv : ",                  CXCallingConv2String(functionTypeCallingConv))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getResultType : ",                               CXType2String(resultType))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getExceptionSpecificationType : ",               to_string(exceptionSpecificationType))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getNumArgTypes : ",                              to_string(numArgTypes))

    for (int32_t index{ 0 }; index < numArgTypes; ++index)
    {
        CXType argType = clang_getArgType(cursorType, index);                                                                                               // 34.
        ADD_STRING_OUT_NL(curLevel + 3, "clang_getArgType : ", CXType2String(argType))
    }

    ADD_STRING_OUT_NL(curLevel + 2, "clang_isFunctionTypeVariadic : ",                      to_string(isFunctionTypeVariadic))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getCursorResultType : ",                         CXType2String(cursorResultType))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getCursorExceptionSpecificationType : ",         to_string(cursorExceptionSpecificationType))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_isPODType : ",                                   to_string(isPODType))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getElementType : ",                              CXType2String(elementType))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getNumElements : ",                              to_string(numElements))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getArrayElementType : ",                         CXType2String(arrayElementType))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getArraySize : ",                                to_string(arraySize))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_Type_getNamedType : ",                           CXType2String(namedType))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_Type_isTransparentTagTypedef : ",                to_string(isTransparentTagTypedef))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_Type_getNullability : ",                         CXTypeNullabilityKind2String(getNullability))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_Type_getAlignOf : ",                             to_string(alignOf))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_Type_getClassType : ",                           CXType2String(classType))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_Type_getSizeOf : ",                              to_string(sizeOf))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_Type_getModifiedType : ",                        CXType2String(modifiedType))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_Cursor_getOffsetOfField : ",                     to_string(offsetOfField))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_Cursor_isAnonymous : ",                          to_string(isAnonymous))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_Cursor_isAnonymousRecordDecl : ",                to_string(isAnonymousRecordDecl))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_Cursor_isInlineNamespace : ",                    to_string(isInlineNamespace))

    ADD_STRING_OUT_NL(curLevel + 2, "clang_Type_getNumTemplateArguments : ",                to_string(typeNumTemplateArguments))
    for (int32_t index{ 0 }; index < typeNumTemplateArguments; ++index)
    {
        CXType templateArgumentAsType = clang_Type_getTemplateArgumentAsType(cursorType, index);                                                            // 61.
        ADD_STRING_OUT_NL(curLevel + 3, "clang_Type_getTemplateArgumentAsType : ", CXType2String(templateArgumentAsType))
    }

    ADD_STRING_OUT_NL(curLevel + 2, "clang_Type_getCXXRefQualifier : ",                     CXRefQualifierKind2String(refQualifier))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_Cursor_isBitField : ",                           to_string(isBitField))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_isVirtualBase : ",                               to_string(isVirtualBase))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_getCXXAccessSpecifier : ",                       CX_CXXAccessSpecifier2String(accessSpecifier))
    ADD_STRING_OUT_NL(curLevel + 2, "clang_Cursor_getStorageClass : ",                      CX_StorageClass2String(storageClass))

    ADD_STRING_OUT_NL(curLevel + 2, "clang_getNumOverloadedDecls : ",                       to_string(numOverloadedDecls))
    for (uint32_t index{ 0 }; index < numOverloadedDecls; ++index)
    {
        CXCursor overloadedDecl = clang_getOverloadedDecl(cursor, index);                                                                                   // 68.
        ADD_STRING_OUT_IF_NL(curLevel + 3, "clang_getOverloadedDecl : lib/cursors.cur -> ", to_string(saveBaseCXCursorInfo(translationUnit, overloadedDecl)))
    }
}

CXType                          _15_getCursorType                               (CXCursor C)
                                                                                { return clang_getCursorType(C); }

CXString                        _15_getTypeSpelling                             (CXType T)
                                                                                { return clang_getTypeSpelling(T); }

CXType                          _15_getTypedefDeclUnderlyingType                (CXCursor C)
                                                                                { return clang_getTypedefDeclUnderlyingType(C); }

CXType                          _15_getEnumDeclIntegerType                      (CXCursor C)
                                                                                { return clang_getEnumDeclIntegerType(C); }

long long                       _15_getEnumConstantDeclValue                    (CXCursor C)
                                                                                { return clang_getEnumConstantDeclValue(C); }

unsigned long long              _15_getEnumConstantDeclUnsignedValue            (CXCursor C)
                                                                                { return clang_getEnumConstantDeclUnsignedValue(C); }

int                             _15_getFieldDeclBitWidth                        (CXCursor C)
                                                                                { return clang_getFieldDeclBitWidth(C); }

int                             _15_getNumArguments                             (CXCursor C)
                                                                                { return clang_Cursor_getNumArguments(C); }

CXCursor                        _15_getArgument                                 (CXCursor C, unsigned i)
                                                                                { return clang_Cursor_getArgument(C, i); }

int                             _15_getNumTemplateArguments                     (CXCursor C)
                                                                                { return clang_Cursor_getNumTemplateArguments(C); }

enum CXTemplateArgumentKind     _15_getTemplateArgumentKind                     (CXCursor C, unsigned I)
                                                                                { return clang_Cursor_getTemplateArgumentKind(C, I); }

CXType                          _15_getTemplateArgumentType                     (CXCursor C, unsigned I)
                                                                                { return clang_Cursor_getTemplateArgumentType(C, I); }

long long                       _15_getTemplateArgumentValue                    (CXCursor C, unsigned I)
                                                                                { return clang_Cursor_getTemplateArgumentValue(C, I); }

unsigned long long              _15_getTemplateArgumentUnsignedValue            (CXCursor C, unsigned I)
                                                                                { return clang_Cursor_getTemplateArgumentUnsignedValue(C, I); }

unsigned                        _15_equalTypes                                  (CXType A, CXType B)
                                                                                { return clang_equalTypes(A, B); }

CXType                          _15_getCanonicalType                            (CXType T)
                                                                                { return clang_getCanonicalType(T); }

unsigned                        _15_isConstQualifiedType                        (CXType T)
                                                                                { return clang_isConstQualifiedType(T); }

unsigned                        _15_isMacroFunctionLike                         (CXCursor C)
                                                                                { return clang_Cursor_isMacroFunctionLike(C); }

unsigned                        _15_isMacroBuiltin                              (CXCursor C)
                                                                                { return clang_Cursor_isMacroBuiltin(C); }

unsigned                        _15_isFunctionInlined                           (CXCursor C)
                                                                                { return clang_Cursor_isFunctionInlined(C); }

unsigned                        _15_isVolatileQualifiedType                     (CXType T)
                                                                                { return clang_isVolatileQualifiedType(T); }

unsigned                        _15_isRestrictQualifiedType                     (CXType T)
                                                                                { return clang_isRestrictQualifiedType(T); }

unsigned                        _15_getAddressSpace                             (CXType T)
                                                                                { return clang_getAddressSpace(T); }

CXString                        _15_getTypedefName                              (CXType T)
                                                                                { return clang_getTypedefName(T); }

CXType                          _15_getPointeeType                              (CXType T)
                                                                                { return clang_getPointeeType(T); }

CXCursor                        _15_getTypeDeclaration                          (CXType T)
                                                                                { return clang_getTypeDeclaration(T); }

CXString                        _15_getDeclObjCTypeEncoding                     (CXCursor C)
                                                                                { return clang_getDeclObjCTypeEncoding(C); }

CXString                        _15_getObjCEncoding                             (CXType T)
                                                                                { return clang_Type_getObjCEncoding(T); }

CXString                        _15_getTypeKindSpelling                         (enum CXTypeKind TypeKind)
                                                                                { return clang_getTypeKindSpelling(TypeKind); }

enum CXCallingConv              _15_getFunctionTypeCallingConv                  (CXType T)
                                                                                { return clang_getFunctionTypeCallingConv(T); }

CXType                          _15_getResultType                               (CXType T)
                                                                                { return clang_getResultType(T); }

int                             _15_getExceptionSpecificationType               (CXType T)
                                                                                { return clang_getExceptionSpecificationType(T); }

int                             _15_getNumArgTypes                              (CXType T)
                                                                                { return clang_getNumArgTypes(T); }

CXType                          _15_getArgType                                  (CXType T, unsigned i)
                                                                                { return clang_getArgType(T, i); }

CXType                          _15_getObjCObjectBaseType                       (CXType T)
                                                                                { return clang_Type_getObjCObjectBaseType(T); }

unsigned                        _15_getNumObjCProtocolRefs                      (CXType T)
                                                                                { return clang_Type_getNumObjCProtocolRefs(T); }

CXCursor                        _15_getObjCProtocolDecl                         (CXType T, unsigned i)
                                                                                { return clang_Type_getObjCProtocolDecl(T, i); }

unsigned                        _15_getNumObjCTypeArgs                          (CXType T)
                                                                                { return clang_Type_getNumObjCTypeArgs(T); }

CXType                          _15_getObjCTypeArg                              (CXType T, unsigned i)
                                                                                { return clang_Type_getObjCTypeArg(T, i); }

unsigned                        _15_isFunctionTypeVariadic                      (CXType T)
                                                                                { return clang_isFunctionTypeVariadic(T); }

CXType                          _15_getCursorResultType                         (CXCursor C)
                                                                                { return clang_getCursorResultType(C); }

int                             _15_getCursorExceptionSpecificationType         (CXCursor C)
                                                                                { return clang_getCursorExceptionSpecificationType(C); }

unsigned                        _15_isPODType                                   (CXType T)
                                                                                { return clang_isPODType(T); }

CXType                          _15_getElementType                              (CXType T)
                                                                                { return clang_getElementType(T); }

long long                       _15_getNumElements                              (CXType T)
                                                                                { return clang_getNumElements(T); }

CXType                          _15_getArrayElementType                         (CXType T)
                                                                                { return clang_getArrayElementType(T); }

long long                       _15_getArraySize                                (CXType T)
                                                                                { return clang_getArraySize(T); }

CXType                          _15_getNamedType                                (CXType T)
                                                                                { return clang_Type_getNamedType(T); }

unsigned                        _15_isTransparentTagTypedef                     (CXType T)
                                                                                { return clang_Type_isTransparentTagTypedef(T); }

enum CXTypeNullabilityKind      _15_getNullability                              (CXType T)
                                                                                { return clang_Type_getNullability(T); }

long long                       _15_getAlignOf                                  (CXType T)
                                                                                { return clang_Type_getAlignOf(T); }

CXType                          _15_getClassType                                (CXType T)
                                                                                { return clang_Type_getClassType(T); }

long long                       _15_getSizeOf                                   (CXType T)
                                                                                { return clang_Type_getSizeOf(T); }

long long                       _15_getOffsetOf                                 (CXType T, const char *S)
                                                                                { return clang_Type_getOffsetOf(T, S); }

CXType                          _15_getModifiedType                             (CXType T)
                                                                                { return clang_Type_getModifiedType(T); }

long long                       _15_getOffsetOfField                            (CXCursor C)
                                                                                { return clang_Cursor_getOffsetOfField(C); }

unsigned                        _15_isAnonymous                                 (CXCursor C)
                                                                                { return clang_Cursor_isAnonymous(C); }

unsigned                        _15_isAnonymousRecordDecl                       (CXCursor C)
                                                                                { return clang_Cursor_isAnonymousRecordDecl(C); }

unsigned                        _15_isInlineNamespace                           (CXCursor C)
                                                                                { return clang_Cursor_isInlineNamespace(C); }

int                             _15_getNumTemplateArguments                     (CXType T)
                                                                                { return clang_Type_getNumTemplateArguments(T); }

CXType                          _15_getTemplateArgumentAsType                   (CXType T, unsigned i)
                                                                                { return clang_Type_getTemplateArgumentAsType(T, i); }

enum CXRefQualifierKind         _15_getCXXRefQualifier                          (CXType T)
                                                                                { return clang_Type_getCXXRefQualifier(T); }

unsigned                        _15_isBitField                                  (CXCursor C)
                                                                                { return clang_Cursor_isBitField(C); }

unsigned                        _15_isVirtualBase                               (CXCursor C)
                                                                                { return clang_isVirtualBase(C); }

enum CX_CXXAccessSpecifier      _15_getCXXAccessSpecifier                       (CXCursor C)
                                                                                { return clang_getCXXAccessSpecifier(C); }

enum CX_StorageClass            _15_getStorageClass                             (CXCursor C)
                                                                                { return clang_Cursor_getStorageClass(C); }

unsigned                        _15_getNumOverloadedDecls                       (CXCursor C)
                                                                                { return clang_getNumOverloadedDecls(C); }

CXCursor                        _15_getOverloadedDecl                           (CXCursor C, unsigned i)
                                                                                { return clang_getOverloadedDecl(C, i); }
