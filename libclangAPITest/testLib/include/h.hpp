// <folder/h.hpp>
void f(int i, int j, int k);

class Klasa
{
	public:
		void f2();
};

// main.cpp
#include <folder/h.hpp>

int main(void)
{
	f(1, 2, 3);
	Klasa k;
	k.f2();
	
	return 0;
}