#pragma once

template<typename T>
void testFunctionTemplate(T value)
{
    
}

template<typename T>
using TestFunctionTemplatePtr = void (*)(T);
