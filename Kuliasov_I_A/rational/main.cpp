#include "rational.hpp"
#include <iostream>
int main()
{
	Rational a(1,2);
	Rational b(2,6);
	Rational c = a * b;
	Rational d;
	Rational p;
	std::cin >> d >> p;
	std::cout << --d << std::endl;
	std::cout << --p << std::endl;
	std::cout << c+d << std::endl;
	return 0;
}