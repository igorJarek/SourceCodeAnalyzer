#pragma once

#include <clang-c/Index.h>
#include "UtilityFunctions.h"
#include <fstream>
#include <string>
#include <iostream>

using std::vector;
using std::to_string;

/*
    Used:

        1.  CXType                          clang_getCursorType                                 (CXCursor C)
        2.  CXString                        clang_getTypeSpelling                               (CXType CT)
        3.  CXType                          clang_getTypedefDeclUnderlyingType                  (CXCursor C)
        4.  CXType                          clang_getEnumDeclIntegerType                        (CXCursor C)
        5.  long long                       clang_getEnumConstantDeclValue                      (CXCursor C)
        6.  unsigned long long              clang_getEnumConstantDeclUnsignedValue              (CXCursor C)
        7.  int                             clang_getFieldDeclBitWidth                          (CXCursor C)

        8.  int                             clang_Cursor_getNumArguments                        (CXCursor C)
        9.  CXCursor                        clang_Cursor_getArgument                            (CXCursor C, unsigned i)

        10. int                             clang_Cursor_getNumTemplateArguments                (CXCursor C)
        11. enum CXTemplateArgumentKind     clang_Cursor_getTemplateArgumentKind                (CXCursor C, unsigned I)
        12. CXType                          clang_Cursor_getTemplateArgumentType                (CXCursor C, unsigned I)
        13. long long                       clang_Cursor_getTemplateArgumentValue               (CXCursor C, unsigned I)
        14. unsigned long long              clang_Cursor_getTemplateArgumentUnsignedValue       (CXCursor C, unsigned I)

        16. CXType                          clang_getCanonicalType                              (CXType T)
        17. unsigned                        clang_isConstQualifiedType                          (CXType T)
        18. unsigned                        clang_Cursor_isMacroFunctionLike                    (CXCursor C)
        19. unsigned                        clang_Cursor_isMacroBuiltin                         (CXCursor C)
        20. unsigned                        clang_Cursor_isFunctionInlined                      (CXCursor C)
        21. unsigned                        clang_isVolatileQualifiedType                       (CXType T)
        22. unsigned                        clang_isRestrictQualifiedType                       (CXType T)
        23. unsigned                        clang_getAddressSpace                               (CXType T)
        24. CXString                        clang_getTypedefName                                (CXType CT)
        25. CXType                          clang_getPointeeType                                (CXType T)
        26. CXCursor                        clang_getTypeDeclaration                            (CXType T)
        29. CXString                        clang_getTypeKindSpelling                           (enum CXTypeKind K)
        30. enum CXCallingConv              clang_getFunctionTypeCallingConv                    (CXType T)
        31. CXType                          clang_getResultType                                 (CXType T)
        32. int                             clang_getExceptionSpecificationType                 (CXType T)
        33. int                             clang_getNumArgTypes                                (CXType T)
        34. CXType                          clang_getArgType                                    (CXType T, unsigned i)

        40. unsigned                        clang_isFunctionTypeVariadic                        (CXType T)
        41. CXType                          clang_getCursorResultType                           (CXCursor C)
        42. int                             clang_getCursorExceptionSpecificationType           (CXCursor C)
        43. unsigned                        clang_isPODType                                     (CXType T)
        44. CXType                          clang_getElementType                                (CXType T)
        45. long long                       clang_getNumElements                                (CXType T)
        46. CXType                          clang_getArrayElementType                           (CXType T)
        47. long long                       clang_getArraySize                                  (CXType T)
        48. CXType                          clang_Type_getNamedType                             (CXType T)
        49. unsigned                        clang_Type_isTransparentTagTypedef                  (CXType T)
        50. enum CXTypeNullabilityKind      clang_Type_getNullability                           (CXType T)
        51. long long                       clang_Type_getAlignOf                               (CXType T)
        52. CXType                          clang_Type_getClassType                             (CXType T)
        53. long long                       clang_Type_getSizeOf                                (CXType T)
        54. long long                       clang_Type_getOffsetOf                              (CXType T, const char *S)
        55. CXType                          clang_Type_getModifiedType                          (CXType T)
        56. long long                       clang_Cursor_getOffsetOfField                       (CXCursor C)
        57. unsigned                        clang_Cursor_isAnonymous                            (CXCursor C)
        58. unsigned                        clang_Cursor_isAnonymousRecordDecl                  (CXCursor C)
        59. unsigned                        clang_Cursor_isInlineNamespace                      (CXCursor C)

        60. int                             clang_Type_getNumTemplateArguments                  (CXType T)
        61. CXType                          clang_Type_getTemplateArgumentAsType                (CXType T, unsigned i)

        62. enum CXRefQualifierKind         clang_Type_getCXXRefQualifier                       (CXType T)
        63. unsigned                        clang_Cursor_isBitField                             (CXCursor C)
        64. unsigned                        clang_isVirtualBase                                 (CXCursor)
        65. enum CX_CXXAccessSpecifier      clang_getCXXAccessSpecifier                         (CXCursor)
        66. enum CX_StorageClass            clang_Cursor_getStorageClass                        (CXCursor)

        67. unsigned                        clang_getNumOverloadedDecls                         (CXCursor cursor)
        68. CXCursor                        clang_getOverloadedDecl                             (CXCursor cursor, unsigned index)

    Unused:

        ObjC 27. CXString                   clang_getDeclObjCTypeEncoding                       (CXCursor C)
        ObjC 28. CXString                   clang_Type_getObjCEncoding                          (CXType type)

        ObjC 35. CXType                     clang_Type_getObjCObjectBaseType                    (CXType T)

        ObjC 36. unsigned                   clang_Type_getNumObjCProtocolRefs                   (CXType T);
        ObjC 37. CXCursor                   clang_Type_getObjCProtocolDecl                      (CXType T, unsigned i)

        ObjC 38. unsigned                   clang_Type_getNumObjCTypeArgs                       (CXType T)
        ObjC 39. CXType                     clang_Type_getObjCTypeArg                           (CXType T, unsigned i)

        15. unsigned                        clang_equalTypes                                    (CXType A, CXType B)
        54. long long                       clang_Type_getOffsetOf                              (CXType T, const char * S)	
    
*/

// Print Function

void _15_printTypeInformationForCXCursors(const CXTranslationUnit& translationUnit, OutputTree& astExtOutputTree, const CXCursor& cursor, uint32_t curLevel, bool cursorStopRecursion);

// Utility Function

void _15_printTypeInformationForCXType   (OutputTree& outputTree, const CXType& type, uint32_t curLevel);

// Clang Functions

CXType                          _15_getCursorType                               (CXCursor C);                   // 1.
CXString                        _15_getTypeSpelling                             (CXType T);                     // 2.
CXType                          _15_getTypedefDeclUnderlyingType                (CXCursor C);                   // 3.
CXType                          _15_getEnumDeclIntegerType                      (CXCursor C);                   // 4.
long long                       _15_getEnumConstantDeclValue                    (CXCursor C);                   // 5.
unsigned long long              _15_getEnumConstantDeclUnsignedValue            (CXCursor C);                   // 6.
int                             _15_getFieldDeclBitWidth                        (CXCursor C);                   // 7.
int                             _15_getNumArguments                             (CXCursor C);                   // 8.
CXCursor                        _15_getArgument                                 (CXCursor C, unsigned i);       // 9.
int                             _15_getNumTemplateArguments                     (CXCursor C);                   // 10.
enum CXTemplateArgumentKind     _15_getTemplateArgumentKind                     (CXCursor C, unsigned I);       // 11.
CXType                          _15_getTemplateArgumentType                     (CXCursor C, unsigned I);       // 12.
long long                       _15_getTemplateArgumentValue                    (CXCursor C, unsigned I);       // 13.
unsigned long long              _15_getTemplateArgumentUnsignedValue            (CXCursor C, unsigned I);       // 14.
unsigned                        _15_equalTypes                                  (CXType A, CXType B);           // 15.
CXType                          _15_getCanonicalType                            (CXType T);                     // 16.
unsigned                        _15_isConstQualifiedType                        (CXType T);                     // 17.
unsigned                        _15_isMacroFunctionLike                         (CXCursor C);                   // 18.
unsigned                        _15_isMacroBuiltin                              (CXCursor C);                   // 19.
unsigned                        _15_isFunctionInlined                           (CXCursor C);                   // 20.
unsigned                        _15_isVolatileQualifiedType                     (CXType T);                     // 21.
unsigned                        _15_isRestrictQualifiedType                     (CXType T);                     // 22.
unsigned                        _15_getAddressSpace                             (CXType T);                     // 23.
CXString                        _15_getTypedefName                              (CXType T);                     // 24.
CXType                          _15_getPointeeType                              (CXType T);                     // 25.
CXCursor                        _15_getTypeDeclaration                          (CXType T);                     // 26.
CXString                        _15_getDeclObjCTypeEncoding                     (CXCursor C);                   // 27.
CXString                        _15_getObjCEncoding                             (CXType T);                     // 28.
CXString                        _15_getTypeKindSpelling                         (enum CXTypeKind TypeKind);     // 29.
enum CXCallingConv              _15_getFunctionTypeCallingConv                  (CXType T);                     // 30.
CXType                          _15_getResultType                               (CXType T);                     // 31.
int                             _15_getExceptionSpecificationType               (CXType T);                     // 32.
int                             _15_getNumArgTypes                              (CXType T);                     // 33.
CXType                          _15_getArgType                                  (CXType T, unsigned i);         // 34.
CXType                          _15_getObjCObjectBaseType                       (CXType T);                     // 35.
unsigned                        _15_getNumObjCProtocolRefs                      (CXType T);                     // 36.
CXCursor                        _15_getObjCProtocolDecl                         (CXType T, unsigned i);         // 37.
unsigned                        _15_getNumObjCTypeArgs                          (CXType T);                     // 38.
CXType                          _15_getObjCTypeArg                              (CXType T, unsigned i);         // 39.
unsigned                        _15_isFunctionTypeVariadic                      (CXType T);                     // 40.
CXType                          _15_getCursorResultType                         (CXCursor C);                   // 41.
int                             _15_getCursorExceptionSpecificationType         (CXCursor C);                   // 42.
unsigned                        _15_isPODType                                   (CXType T);                     // 43.
CXType                          _15_getElementType                              (CXType T);                     // 44.
long long                       _15_getNumElements                              (CXType T);                     // 45.
CXType                          _15_getArrayElementType                         (CXType T);                     // 46.
long long                       _15_getArraySize                                (CXType T);                     // 47.
CXType                          _15_getNamedType                                (CXType T);                     // 48.
unsigned                        _15_isTransparentTagTypedef                     (CXType T);                     // 49.
enum CXTypeNullabilityKind      _15_getNullability                              (CXType T);                     // 50.
long long                       _15_getAlignOf                                  (CXType T);                     // 51.
CXType                          _15_getClassType                                (CXType T);                     // 52.
long long                       _15_getSizeOf                                   (CXType T);                     // 53.
long long                       _15_getOffsetOf                                 (CXType T, const char *S);      // 54.
CXType                          _15_getModifiedType                             (CXType T);                     // 55.
long long                       _15_getOffsetOfField                            (CXCursor C);                   // 56.
unsigned                        _15_isAnonymous                                 (CXCursor C);                   // 57.
unsigned                        _15_isAnonymousRecordDecl                       (CXCursor C);                   // 58.
unsigned                        _15_isInlineNamespace                           (CXCursor C);                   // 59.
int                             _15_getNumTemplateArguments                     (CXType T);                     // 60.
CXType                          _15_getTemplateArgumentAsType                   (CXType T, unsigned i);         // 61.
enum CXRefQualifierKind         _15_getCXXRefQualifier                          (CXType T);                     // 62.
unsigned                        _15_isBitField                                  (CXCursor C);                   // 63.
unsigned                        _15_isVirtualBase                               (CXCursor C);                   // 64.
enum CX_CXXAccessSpecifier      _15_getCXXAccessSpecifier                       (CXCursor C);                   // 65.
enum CX_StorageClass            _15_getStorageClass                             (CXCursor C);                   // 66.
unsigned                        _15_getNumOverloadedDecls                       (CXCursor C);                   // 67.
CXCursor                        _15_getOverloadedDecl                           (CXCursor C, unsigned i);       // 68.
