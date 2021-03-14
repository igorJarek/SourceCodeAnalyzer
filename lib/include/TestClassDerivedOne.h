#pragma once

#include "TestClass.h"

class TestClassDerivedOne : public TestClass
{
    public:
        virtual ~TestClassDerivedOne();

    public:
        virtual void testMethodVirtual(void) override;
};