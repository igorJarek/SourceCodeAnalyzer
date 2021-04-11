#include "15_Type_information_for_CXCursors.h"

void _15_printTypeInformationForCXCursors(const CXTranslationUnit& translationUnit, OutputTree& astExtOutputTree, const CXCursor& cursor, uint32_t curLevel, bool cursorStopRecursion)
{
    if(isOptionNotEnabled(CATEGORY_15))
        return;

    CXType                      cursorType                              = clang_getCursorType                           (cursor);                           // 1
    CXString                    typeSpelling                            = clang_getTypeSpelling                         (cursorType);                       // 2.

    if (cursorType.kind == CXType_Invalid || cursorType.kind == CXType_Unexposed)
    {
        astExtOutputTree.addString(curLevel + 1, "15. Type information for CXCursors : ");
        astExtOutputTree.addString(curLevel + 2, "clang_getTypeSpelling : ", typeSpelling);

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
        templateArgumentKindStrings.push_back(std::to_string(templateArgumentKind));

        CXType templateArgumentType = clang_Cursor_getTemplateArgumentType(cursor, index);                                                                  // 12.
        templateArgumentTypeStrings.push_back("clang_getEnumDeclIntegerType : lib/types.type -> " + to_string(saveBaseCXTypeInfo(nullptr, &templateArgumentType, InfoAction::ADD_INFO)));

        int64_t templateArgumentValue = clang_Cursor_getTemplateArgumentValue(cursor, index);                                                               // 13.
        templateArgumentValueStrings.push_back(to_string(templateArgumentValue));

        uint64_t templateArgumentUnsignedValue = clang_Cursor_getTemplateArgumentUnsignedValue (cursor, index);                                             // 14.
        templateArgumentUnsignedValueStrings.push_back(to_string(templateArgumentUnsignedValue));
    }

    uint32_t                    isMacroFunctionLike                     = clang_Cursor_isMacroFunctionLike              (cursor);                           // 18.
    uint32_t                    isMacroBuiltin                          = clang_Cursor_isMacroBuiltin                   (cursor);                           // 19.
    uint32_t                    isFunctionInlined                       = clang_Cursor_isFunctionInlined                (cursor);                           // 20.
    CXCursor                    getTypeDeclaration                      = clang_getTypeDeclaration                      (cursorType);                       // 26.
    CXString                    typeKindSpelling                        = clang_getTypeKindSpelling                     (cursorType.kind);                  // 29.
    CXType                      cursorResultType                        = clang_getCursorResultType                     (cursor);                           // 41.
    int32_t                     cursorExceptionSpecificationType        = clang_getCursorExceptionSpecificationType     (cursor);                           // 42.
    int64_t                     offsetOfField                           = clang_Cursor_getOffsetOfField                 (cursor);                           // 56.
    uint32_t                    isAnonymous                             = clang_Cursor_isAnonymous                      (cursor);                           // 57.
    uint32_t                    isAnonymousRecordDecl                   = clang_Cursor_isAnonymousRecordDecl            (cursor);                           // 58.
    uint32_t                    isInlineNamespace                       = clang_Cursor_isInlineNamespace                (cursor);                           // 59.
    int32_t                     isBitField                              = clang_Cursor_isBitField                       (cursor);                           // 63.
    int32_t                     isVirtualBase                           = clang_isVirtualBase                           (cursor);                           // 64.
    CX_CXXAccessSpecifier       accessSpecifier                         = clang_getCXXAccessSpecifier                   (cursor);                           // 65.
    CX_StorageClass             storageClass                            = clang_Cursor_getStorageClass                  (cursor);                           // 66.

    uint32_t                    numOverloadedDecls                      = clang_getNumOverloadedDecls                   (cursor);                           // 67.

    astExtOutputTree.addString(curLevel + 1, "15. Type information for CXCursors : ");

    astExtOutputTree.addString(curLevel + 2, "clang_getTypeKindSpelling : ",                            typeKindSpelling);
    astExtOutputTree.addString(curLevel + 2, "clang_getTypeSpelling : ",                                typeSpelling);
    astExtOutputTree.addString(curLevel + 2, "clang_getTypedefDeclUnderlyingType : lib/types.type -> ", saveBaseCXTypeInfo(nullptr, &typedefDeclUnderlyingType, InfoAction::ADD_INFO));
    astExtOutputTree.addString(curLevel + 2, "clang_getEnumDeclIntegerType : lib/types.type -> ",       saveBaseCXTypeInfo(nullptr, &enumDeclIntegerType, InfoAction::ADD_INFO));
    astExtOutputTree.addString(curLevel + 2, "clang_getEnumConstantDeclValue : ",                       enumConstantDeclValue);
    astExtOutputTree.addString(curLevel + 2, "clang_getEnumConstantDeclUnsignedValue : ",               enumConstantDeclUnsignedValue);
    astExtOutputTree.addString(curLevel + 2, "clang_getFieldDeclBitWidth : ",                           fieldDeclBitWidth);

    astExtOutputTree.addString(curLevel + 2, "clang_Cursor_getNumArguments : ",                         numArguments);
    for (int32_t index{ 0 }; index < numArguments; ++index)
    {
        CXCursor cursor_getArgument = clang_Cursor_getArgument(cursor, index);                                                                              // 9.

        if(cursorStopRecursion)
            astExtOutputTree.addString(curLevel + 3, "clang_Cursor_getArgument : lib/cursors.cur -> ", saveBaseCXCursorInfo(&translationUnit, &cursor_getArgument, InfoAction::ADD_INFO));
        else
            astExtOutputTree.addString(curLevel + 3, "clang_Cursor_getArgument : lib/cursors.cur -> -Not Printed-");
    }

    astExtOutputTree.addString(curLevel + 2, "clang_Cursor_getNumTemplateArguments : ",            cursorNumTemplateArguments);

    for (int32_t index{ 0 }; index < cursorNumTemplateArguments; ++index)
    {
        astExtOutputTree.addString(curLevel + 3, "clang_Cursor_getTemplateArgumentKind : ",          templateArgumentKindStrings[index]);
        astExtOutputTree.addString(curLevel + 3, "clang_Cursor_getTemplateArgumentType : ",          templateArgumentTypeStrings[index]);
        astExtOutputTree.addString(curLevel + 3, "clang_Cursor_getTemplateArgumentValue : ",         templateArgumentValueStrings[index]);
        astExtOutputTree.addString(curLevel + 3, "clang_Cursor_getTemplateArgumentUnsignedValue : ", templateArgumentUnsignedValueStrings[index]);
    }

    astExtOutputTree.addString(curLevel + 2, "clang_Cursor_isMacroFunctionLike : ",                  isMacroFunctionLike);
    astExtOutputTree.addString(curLevel + 2, "clang_Cursor_isMacroBuiltin : ",                       isMacroBuiltin);
    astExtOutputTree.addString(curLevel + 2, "clang_Cursor_isFunctionInlined : ",                    isFunctionInlined);

    if(cursorStopRecursion)
    {
        uint64_t baseInfoLine = saveBaseCXCursorInfo(&translationUnit, &getTypeDeclaration, InfoAction::ADD_INFO);
        string   isEqualStr   = _19_equalCursors(getTypeDeclaration, cursor) ? " (Equal)" : " (Unequal)";
        astExtOutputTree.addString(curLevel + 2, "clang_getTypeDeclaration : lib/cursors.cur -> ", to_string(baseInfoLine) + isEqualStr);
    }
    else
        astExtOutputTree.addString(curLevel + 2, "clang_getTypeDeclaration : lib/cursors.cur -> -Not Printed-");

    astExtOutputTree.addString(curLevel + 2, "clang_getCursorResultType : lib/types.type -> ",      saveBaseCXTypeInfo(nullptr, &cursorResultType, InfoAction::ADD_INFO));
    astExtOutputTree.addString(curLevel + 2, "clang_getCursorExceptionSpecificationType : ",         cursorExceptionSpecificationType);
    astExtOutputTree.addString(curLevel + 2, "clang_Cursor_getOffsetOfField : ",                     offsetOfField);
    astExtOutputTree.addString(curLevel + 2, "clang_Cursor_isAnonymous : ",                          isAnonymous);
    astExtOutputTree.addString(curLevel + 2, "clang_Cursor_isAnonymousRecordDecl : ",                isAnonymousRecordDecl);
    astExtOutputTree.addString(curLevel + 2, "clang_Cursor_isInlineNamespace : ",                    isInlineNamespace);
    astExtOutputTree.addString(curLevel + 2, "clang_Cursor_isBitField : ",                           isBitField);
    astExtOutputTree.addString(curLevel + 2, "clang_isVirtualBase : ",                               isVirtualBase);
    astExtOutputTree.addString(curLevel + 2, "clang_getCXXAccessSpecifier : ",                       accessSpecifier);
    astExtOutputTree.addString(curLevel + 2, "clang_Cursor_getStorageClass : ",                      storageClass);

    astExtOutputTree.addString(curLevel + 2, "clang_getNumOverloadedDecls : ",                       numOverloadedDecls);
    for (uint32_t index{ 0 }; index < numOverloadedDecls; ++index)
    {
        CXCursor overloadedDecl = clang_getOverloadedDecl(cursor, index);                                                                                   // 68.
        if(cursorStopRecursion)
            astExtOutputTree.addString(curLevel + 3, "clang_getOverloadedDecl : lib/cursors.cur -> ", saveBaseCXCursorInfo(&translationUnit, &overloadedDecl, InfoAction::ADD_INFO));
        else
            astExtOutputTree.addString(curLevel + 3, "clang_getOverloadedDecl : lib/cursors.cur -> -Not Printed-");
    }

    astExtOutputTree.addNewLine(curLevel + 2);

    _15_printTypeInformationForCXType(astExtOutputTree, cursorType, curLevel + 2);
}

void _15_printTypeInformationForCXType(OutputTree& outputTree, const CXType& type, uint32_t curLevel)
{
    uint32_t                isConstQualifiedType        = _15_isConstQualifiedType          (type);                       // 17.
    uint32_t                isVolatileQualifiedType     = _15_isVolatileQualifiedType       (type);                       // 21.
    uint32_t                isRestrictQualifiedType     = _15_isRestrictQualifiedType       (type);                       // 22.
    uint32_t                getAddressSpace             = _15_getAddressSpace               (type);                       // 23.
    CXString                getTypedefName              = _15_getTypedefName                (type);                       // 24.
    CXCallingConv           functionTypeCallingConv     = _15_getFunctionTypeCallingConv    (type);                       // 30.
    int32_t                 exceptionSpecificationType  = _15_getExceptionSpecificationType (type);                       // 32.
    int32_t                 numArgTypes                 = _15_getNumArgTypes                (type);                       // 33.
    uint32_t                isFunctionTypeVariadic      = _15_isFunctionTypeVariadic        (type);                       // 40.
    uint32_t                isPODType                   = _15_isPODType                     (type);                       // 43.
    int64_t                 numElements                 = _15_getNumElements                (type);                       // 45.
    int64_t                 arraySize                   = _15_getArraySize                  (type);                       // 47.
    uint32_t                isTransparentTagTypedef     = _15_isTransparentTagTypedef       (type);                       // 49.
    CXTypeNullabilityKind   getNullability              = _15_getNullability                (type);                       // 50.
    int64_t                 alignOf                     = _15_getAlignOf                    (type);                       // 51.
    int64_t                 sizeOf                      = _15_getSizeOf                     (type);                       // 53.
    int32_t                 typeNumTemplateArguments    = _15_getNumTemplateArguments       (type);                       // 60.
    CXRefQualifierKind      refQualifier                = _15_getCXXRefQualifier            (type);                       // 62.

    outputTree.addString(curLevel, "clang_isConstQualifiedType : ",          isConstQualifiedType);
    outputTree.addString(curLevel, "clang_isVolatileQualifiedType : ",       isVolatileQualifiedType);
    outputTree.addString(curLevel, "clang_isRestrictQualifiedType : ",       isRestrictQualifiedType);
    outputTree.addString(curLevel, "clang_getAddressSpace : ",               getAddressSpace);
    outputTree.addString(curLevel, "clang_getTypedefName : ",                getTypedefName);
    outputTree.addString(curLevel, "clang_getFunctionTypeCallingConv : ",    functionTypeCallingConv);
    outputTree.addString(curLevel, "clang_getExceptionSpecificationType : ", exceptionSpecificationType);
    outputTree.addString(curLevel, "clang_getNumArgTypes : ",                numArgTypes);

    outputTree.addString(curLevel, "clang_isFunctionTypeVariadic : ",        isFunctionTypeVariadic);
    outputTree.addString(curLevel, "clang_isPODType : ",                     isPODType);
    outputTree.addString(curLevel, "clang_getNumElements : ",                numElements);
    outputTree.addString(curLevel, "clang_getArraySize : ",                  arraySize);
    outputTree.addString(curLevel, "clang_isTransparentTagTypedef : ",       isTransparentTagTypedef);
    outputTree.addString(curLevel, "clang_getNullability : ",                getNullability);
    outputTree.addString(curLevel, "clang_getAlignOf : ",                    alignOf);
    outputTree.addString(curLevel, "clang_getSizeOf : ",                     sizeOf);
    outputTree.addString(curLevel, "clang_getNumTemplateArguments : ",       typeNumTemplateArguments);
    outputTree.addString(curLevel, "clang_getCXXRefQualifier : ",            refQualifier);

    outputTree.addNewLine(curLevel);

    CXType canonicalType = _15_getCanonicalType(type);                                      // 16.
    if(canonicalType.kind != CXType_Invalid)
        outputTree.addString(curLevel, "clang_getCanonicalType : ", canonicalType);
    else
        outputTree.addString(curLevel, "clang_getCanonicalType : CXType_Invalid");

    CXType getPointeeType = _15_getPointeeType(type);                                       // 25.
    if(getPointeeType.kind != CXType_Invalid)
        outputTree.addString(curLevel, "clang_getPointeeType : ", getPointeeType);
    else
        outputTree.addString(curLevel, "clang_getPointeeType : CXType_Invalid");

    CXType resultType = _15_getResultType(type);                                            // 31.
    if(resultType.kind != CXType_Invalid)
        outputTree.addString(curLevel, "clang_getResultType : ", resultType);
    else
        outputTree.addString(curLevel, "clang_getResultType : CXType_Invalid");

    for(int32_t index{ 0 }; index < numArgTypes; ++index)
    {
        CXType argType = clang_getArgType(type, index);                                     // 34.
        outputTree.addString(curLevel + 1, "clang_getArgType : ", argType);
    }

    CXType elementType = _15_getElementType(type);                                          // 44.
    if(elementType.kind != CXType_Invalid)
        outputTree.addString(curLevel, "clang_getElementType : ", elementType);
    else
        outputTree.addString(curLevel, "clang_getElementType : CXType_Invalid");

    CXType arrayElementType = _15_getArrayElementType(type);                                // 46.
    if(arrayElementType.kind != CXType_Invalid)
        outputTree.addString(curLevel, "clang_getArrayElementType : ", arrayElementType);
    else
        outputTree.addString(curLevel, "clang_getArrayElementType : CXType_Invalid");

    CXType namedType = _15_getNamedType(type);                                              // 48.
    if(namedType.kind != CXType_Invalid)
        outputTree.addString(curLevel, "clang_Type_getNamedType : ", namedType);
    else
        outputTree.addString(curLevel, "clang_Type_getNamedType : CXType_Invalid");

    CXType classType = _15_getClassType(type);                                              // 52.
    if(classType.kind != CXType_Invalid)
        outputTree.addString(curLevel, "clang_Type_getClassType : ", classType);
    else
        outputTree.addString(curLevel, "clang_Type_getClassType : CXType_Invalid");

    CXType modifiedType = _15_getModifiedType(type);                                        // 55.
    if(modifiedType.kind != CXType_Invalid)
        outputTree.addString(curLevel, "clang_Type_getModifiedType : ", modifiedType);
    else
        outputTree.addString(curLevel, "clang_Type_getModifiedType : CXType_Invalid");

    for(int32_t index{ 0 }; index < typeNumTemplateArguments; ++index)
    {
        CXType templateArgumentAsType = clang_Type_getTemplateArgumentAsType(type, index);  // 61.
        outputTree.addString(curLevel + 1, "clang_Type_getTemplateArgumentAsType : ", templateArgumentAsType);
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
