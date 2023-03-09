#include "include/arrayd/arrayd.hpp"
#include <iostream>
int main()
{
	ArrayD a(5);
	a.push_back(4);
	std::cout << a[0];
	return 0;
}