#include "Primitives.hpp"

void primitivesFunction()
{
    bool    boolVar1     = true;
    bool    boolVar2     {true};

    char    charVar     = 'a';

    int     intVar1      = 1;
    int     intVar2      = 2;
    int     intVar3      { 1.1 };               // compile error

    int     intVar4     = intVar1 + intVar2;
    int     intVar5     = intVar1 - intVar2;
    int     intVar6     = intVar1 * intVar2;

    intVar1++;
    intVar2 += intVar2;

    double  doubleVar1   = 1.0;
    double  doubleVar2   = doubleVar1 / 0.0;    // what do you do, Clang ? :)

    const int constIntVar = 0;
    //constexpr

    char array[10] = {1, 2, 3};
    char* arrayPtr = nullptr;
    arrayPtr = &array[1];

    unsigned int intForLoop = 5; 
    for(int index = 0; index < intForLoop; ++index) 
    {

    }

    while(true)
    {
        
    }

    do
    {
        intForLoop += 1;
    }while(intForLoop < 10);
}