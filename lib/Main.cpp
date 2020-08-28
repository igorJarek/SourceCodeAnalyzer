#include <TestClass.hpp>
#include <TestFunction.hpp>

int main(void)
{
    testFunction(1, 2, 3, 4);

    TestClass testClass;
    testClass.testClassMethod();

    TestClass* testClassPtr = new TestClass();
    testClassPtr->testClassMethod();
    delete testClassPtr;

    return 0;
}