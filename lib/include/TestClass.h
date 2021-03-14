#pragma once

class TestClass;

using TestMethodPtr = void(TestClass::*)();

class TestClass
{
    public:
        virtual ~TestClass();

    public:
        void testMethod(unsigned char i, unsigned short j, unsigned int k, unsigned long l);

        void testMethodOverloading(void);
        void testMethodOverloading(int i);
        void testMethodOverloading(double d);

        template<typename T>
        void testMethodTemplate(T value)
        {
            
        }

        template<typename T>
        void testMethodOverloadingTemplate(T v, int i)
        {
            
        }

        template<typename T>
        void testMethodOverloadingTemplate(T v, double d)
        {
            
        }

        virtual void testMethodVirtual(void);
};