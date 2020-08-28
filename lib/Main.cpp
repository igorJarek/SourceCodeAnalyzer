#include <TestClass.hpp>
#include <TestFunction.hpp>

int main(void)
{
    testFunction(1, 2, 3, 4);

    TestClass class_1;
    class_1.testClassMethod();

    TestClass* class_2 = new TestClass();
    class_2->testClassMethod();
    delete class_2;

    return 0;
}