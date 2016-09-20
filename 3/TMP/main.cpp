#include <iostream>

template<unsigned int x>
struct factorial {
	enum { value = factorial<x - 1>::value * x };
};

template<>
struct factorial<0> {
	enum { value = 1 };
};

int main (int argc, char ** argv) {
	unsigned int Fact15 = factorial<15>::value;
	std::cout<<"15! = " << Fact15 << std::endl;
	return 0;
}
