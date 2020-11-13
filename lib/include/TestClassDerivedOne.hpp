#pragma once

#include <TestClass.hpp>

class TestClassDerivedOne : public TestClass
{
    public:
        virtual ~TestClassDerivedOne();

    public:
        virtual void testMethodVirtual(void) override;
};