#pragma once

void testFunctionOverloading(void);
void testFunctionOverloading(int i);
void testFunctionOverloading(double d);

using TestFunctionOverloadingVoidPtr   = void (*)(void);
using TestFunctionOverloadingIntPtr    = void (*)(int);
using TestFunctionOverloadingDoublePtr = void (*)(double);
