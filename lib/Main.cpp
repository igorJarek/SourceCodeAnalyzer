#include "TestFunction.h"
#include "TestFunctionOverloading.h"
#include "TestFunctionTemplate.h"
#include "TestFunctionOverloadingTemplate.h"
#include "TestLambda.h"
#include "TestFunctionDefine.h"

#include "TestClass.h"
#include "TestClassDerivedOne.h"

int main(void)
{
    testFunction(1, 2, 3, 4);

    testFunctionOverloading();
    testFunctionOverloading(1);
    testFunctionOverloading(1.0);

    testFunctionTemplate<int>   (1);
    testFunctionTemplate<double>(1.0);

    testFunctionOverloadingTemplate<int>(1, 1);
    testFunctionOverloadingTemplate<int>(1, 1.0);

    testFunctionOverloadingTemplate<double>(1.0, 1);
    testFunctionOverloadingTemplate<double>(1.0, 1.0);

    testLambda(1);

    testFunctionDefine(1, 1);

    TestFunctionPtr                                  testFunctionPtr                          = testFunction;

    TestFunctionOverloadingVoidPtr                   testFunctionOverloadingVoidPtr           = testFunctionOverloading;
    TestFunctionOverloadingIntPtr                    testFunctionOverloadingIntPtr            = testFunctionOverloading;
    TestFunctionOverloadingDoublePtr                 testFunctionOverloadingDoublePtr         = testFunctionOverloading;

    TestFunctionTemplatePtr<int>                     testFunctionTemplateIntPtr               = testFunctionTemplate;
    TestFunctionTemplatePtr<double>                  testFunctionTemplateDoublePtr            = testFunctionTemplate;

    TestFunctionOverloadingTemplateIntPtr<int>       testFunctionOverloadingTemplateIntPtr    = testFunctionOverloadingTemplate;
    TestFunctionOverloadingTemplateDoublePtr<double> testFunctionOverloadingTemplateDoublePtr = testFunctionOverloadingTemplate;

    testFunctionPtr(1, 2, 3, 4);

    testFunctionOverloadingVoidPtr  ();
    testFunctionOverloadingIntPtr   (1);
    testFunctionOverloadingDoublePtr(1.0);

    testFunctionTemplateIntPtr(1);
    testFunctionTemplateDoublePtr(1.0);

    testFunctionOverloadingTemplateIntPtr(1, 1);
    testFunctionOverloadingTemplateIntPtr(1, 1.0);

    testFunctionOverloadingTemplateDoublePtr(1.0, 1);
    testFunctionOverloadingTemplateDoublePtr(1.0, 1.0);

    // ---------------------------------------------------------

    TestClass           testClass;
    TestClassDerivedOne testClassDerivedOne;

    TestClass*          testClassPtr  = nullptr;
    TestMethodPtr       testMethodPtr = nullptr;

    testClass.testMethod(1, 2, 3, 4);

    testClass.testMethodOverloading();
    testClass.testMethodOverloading(1);
    testClass.testMethodOverloading(1.0);

    testClass.testMethodTemplate<int>   (1);
    testClass.testMethodTemplate<double>(1.0);

    testClass.testMethodOverloadingTemplate<int>(1, 1);
    testClass.testMethodOverloadingTemplate<int>(1, 1.0);

    testClass.testMethodOverloadingTemplate<double>(1.0, 1);
    testClass.testMethodOverloadingTemplate<double>(1.0, 1.0);

    testClassPtr = &testClass;
    testClassPtr->testMethodVirtual();

    testClassPtr = &testClassDerivedOne;
    testClassPtr->testMethodVirtual();

    testMethodPtr = &TestClass::testMethodVirtual;

    (testClass.*testMethodPtr)();

    testMethodPtr = &TestClass::testMethodOverloading;

    (testClass.*testMethodPtr)();

    return 0;
}