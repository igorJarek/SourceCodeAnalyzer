#pragma once

void testFunction(unsigned char i, unsigned short j, unsigned int k, unsigned long l);

using TestFunctionPtr = void (*)(unsigned char, unsigned short, unsigned int, unsigned long);
