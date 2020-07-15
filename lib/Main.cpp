#include <Class.hpp>
#include <Function.hpp>

int main(void)
{
    function(1, 2, 3, 4);

    Class class_1;
    class_1.classMethod();

    Class* class_2 = new Class();
    class_2->classMethod();
    delete class_2;

    return 0;
}