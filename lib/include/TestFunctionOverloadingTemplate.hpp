#pragma once

template<typename T>
void testFunctionOverloadingTemplate(T v, int i)
{
    
}

template<typename T>
void testFunctionOverloadingTemplate(T v, double d)
{
    
}

template<typename T>
using TestFunctionOverloadingTemplateIntPtr    = void (*)(T, int);

template<typename T>
using TestFunctionOverloadingTemplateDoublePtr = void (*)(T, double);
