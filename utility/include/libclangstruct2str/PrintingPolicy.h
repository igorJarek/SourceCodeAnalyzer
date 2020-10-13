#pragma once

/*
* Simplify LibClang struct implementation
* https://clang.llvm.org/doxygen/structclang_1_1PrintingPolicy.html
*/

struct PrintingPolicy 
{
    unsigned Indentation                            : 8;
    unsigned SuppressSpecifiers                     : 1;
    unsigned SuppressTagKeyword                     : 1;
    unsigned IncludeTagDefinition                   : 1;
    unsigned SuppressScope                          : 1;
    unsigned SuppressUnwrittenScope                 : 1;
    unsigned SuppressInitializers                   : 1;
    unsigned ConstantArraySizeAsWritten             : 1;
    unsigned AnonymousTagLocations                  : 1;
    unsigned SuppressStrongLifetime                 : 1;
    unsigned SuppressLifetimeQualifiers             : 1;
    unsigned SuppressTemplateArgsInCXXConstructors  : 1;
    unsigned Bool                                   : 1;
    unsigned Restrict                               : 1;
    unsigned Alignof                                : 1;
    unsigned UnderscoreAlignof                      : 1;
    unsigned UseVoidForZeroParams                   : 1;
    unsigned TerseOutput                            : 1;
    unsigned PolishForDeclaration                   : 1;
    unsigned Half                                   : 1;
    unsigned MSWChar                                : 1;
    unsigned IncludeNewlines                        : 1;
    unsigned MSVCFormatting                         : 1;
    unsigned ConstantsAsWritten                     : 1;
    unsigned SuppressImplicitBase                   : 1;
    unsigned FullyQualifiedName                     : 1;
    unsigned RemapFilePaths                         : 1;
    unsigned PrintCanonicalTypes                    : 1;
};