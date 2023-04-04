#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <arrayd/arrayd.hpp>

#include <doctest/doctest.h>

TEST_CASE("CONSTRUCTORS") {
	SUBCASE("CONSTRUCTOR WITHOUT PARAMETRS") {
		ArrayD a;
		CHECK(a.ssize() == 0);
	}
	SUBCASE("MEMORY ALLOCATION") {
		ArrayD a;
		CHECK_THROWS_AS(a[0] = 0, std::out_of_range);
	}
	SUBCASE("CONSTRUCTOR WITH SIZE") {
		size_t size = 5;
		ArrayD a(size);
		a[1] = 2;
		a[2] = 3;
		SUBCASE("SIZE") {
			CHECK(a.ssize() == size);
		}
		SUBCASE("ArrayD VALUES") {
			CHECK(a[1] == 2);
			CHECK(a[2] == 3);
		}
		SUBCASE("CHANGE VALUE") {
			a[1] = 10;
			CHECK(a[1] == 10);
		}
		SUBCASE("DEFAULT VALUE") {
			CHECK(a[0] == 0);
		}
	}
	SUBCASE("CONSTRUCTOR FROM ANOTHER INSTANCE") {
		size_t size = 3;
		ArrayD b(size);
		b[0] = 1;
		b[1] = 2;
		b[2] = -3;
		ArrayD a(b);
		SUBCASE("SIZE") {
			CHECK(a.ssize() == b.ssize());
			CHECK(a.ssize() == size);
		}
		SUBCASE("ArrayD VALUES") {
			CHECK(a[0] == b[0]);
			CHECK(a[0] == 1);
			CHECK(a[2] == b[2]);
			CHECK(a[2] == -3);
		}
		SUBCASE("CHANGE VALUES") {
			b[0] = 10;
			CHECK(a[0] != b[0]);
			CHECK(b[0] == 10);
			CHECK(a[0] == 1);
		}
	}
}
TEST_CASE("INTERFACE")
{
	SUBCASE("EQUIVALENCE") {
		size_t size = 4;
		ArrayD b(size);
		b[0] = 1;
		b[1] = 2;
		b[2] = -3;
		ArrayD a=b;
		SUBCASE("SIZE") {
			CHECK(a.ssize() == b.ssize());
			CHECK(a.ssize() == size);
		}
		SUBCASE("ArrayD VALUES") {
			CHECK(a[0] == b[0]);
			CHECK(a[0] == 1);
			CHECK(a[2] == b[2]);
			CHECK(a[2] == -3);
		}
		SUBCASE("CHANGE VALUES") {
			b[0] = 10;
			CHECK(a[0] != b[0]);
			CHECK(b[0] == 10);
			CHECK(a[0] == 1);
			a[0] = 3;
			CHECK(a[0] != b[0]);
			CHECK(b[0] == 10);
			CHECK(a[0] == 3);
		}
	}
	SUBCASE("A=A") {
		size_t size = 4;
		ArrayD b(size);
		SUBCASE("0") {
			CHECK(b[0] == 0);
		}
		b = b;
		b[2] = 2;
		SUBCASE("SIZE") {
			CHECK(b.ssize() == size);
		}
		SUBCASE("ArrayD VALUES") {
			CHECK(b[2] == 2);
			CHECK(b[0] == 0);
		}
		SUBCASE("CHANGE VALUES") {
			b[0] = 10;
			CHECK(b[0] == 10);
		}
	}
	SUBCASE("INDEX") {
		size_t size = 4;
		ArrayD a(size);
		a[0] = 1.2;
		SUBCASE("LHS") {
			double b=3.14;
			a[1] = b;
			CHECK(a[1] == b);
		}
		SUBCASE("RHS") {
			double b = 3.14;
			b = a[0];
			CHECK(b==1.2);
		}
		SUBCASE("INDEX OUT OF RANGE(>=SIZE)"){
			double b = 3.14;
			CHECK_THROWS_AS(a[size] = b, std::out_of_range);
		}
		SUBCASE("INDEX OUT OF RANGE(<=0)") {
			double b = 3.14;
			CHECK_THROWS_AS(a[-1] = b, std::out_of_range);
		}
	}
	SUBCASE("SIZE AND CAPACITY") {
		SUBCASE("SSIZE") {
			size_t size = 3;
			ArrayD a(size);
			CHECK(a.ssize() == size);
		}
		SUBCASE("RESIZE>SIZE") {
			size_t size = 3;
			ArrayD a(size);
			a[2] = 5.2;
			size_t new_size = 5;
			a.resize(new_size);
			CHECK(a.ssize() == new_size);
			CHECK(a[2] == 5.2);
			CHECK(a[0] == 0);
			CHECK(a[new_size - 1] == 0);
			CHECK_THROWS_AS(a[new_size] = 1, std::out_of_range);
		}
		SUBCASE("RESIZE<SIZE") {
			size_t size = 4;
			ArrayD a(size);
			
			a[1] = 5.2;
			size_t new_size = 3;
			a.resize(new_size);
			CHECK(a.ssize() == new_size);
			CHECK(a[1] == 5.2);
			CHECK(a[0] == 0);
			CHECK(a[new_size - 1] == 0);
			CHECK_THROWS_AS(a[new_size] = 1, std::out_of_range);
		}
		SUBCASE("RESIZE 0") {
			size_t size = 3;
			ArrayD a(size);
			CHECK_THROWS_AS(a.resize(0), std::invalid_argument);
		}
	}
	SUBCASE("INSERT") {
		size_t size = 3;
		ArrayD a(size);
		a[1] = 2.5;
		SUBCASE("IN RANGE") {
			a.insert(1, 3.14);
			CHECK(a[1] == 3.14);
			CHECK(a[2] == 2.5);
			CHECK(a.ssize() == size + 1);
		}
		SUBCASE("IN SIZE") {
			CHECK_NOTHROW(a.insert(size, 3.14));
			CHECK(a[size] == 3.14);
			CHECK(a.ssize() == size + 1);
		}
		SUBCASE("OUT OF RANGE(>SIZE)") {
			CHECK_THROWS_AS(a.insert(size+1,3.14), std::out_of_range);
		}
		SUBCASE("OUT OF RANGE(<=0)") {
			CHECK_THROWS_AS(a.insert(-1, 3.14), std::out_of_range);
		}
	}
	SUBCASE("REMOVE") {
		size_t size = 3;
		ArrayD a(size);
		a[2] = 2.5;
		SUBCASE("IN RANGE") {
			a.remove(1);
			CHECK(a[1] == 2.5);
			CHECK(a[0] == 0);
			CHECK(a.ssize() == size - 1);
		}
		SUBCASE("OUT OF RANGE(>SIZE)") {
			CHECK_THROWS_AS(a.remove(size + 1), std::out_of_range);
		}
		SUBCASE("OUT OF RANGE(<=0)") {
			CHECK_THROWS_AS(a.remove(-1), std::out_of_range);
		}
	}
}