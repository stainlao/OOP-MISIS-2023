#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <matrixs/matrixs.hpp>

#include <doctest/doctest.h>

TEST_CASE("CONSTRUCTORS") {
	SUBCASE("CONSTRUCTOR WITHOUT PARAMETRS") {
		MatrixS a;
		CHECK(a.ssize() == std::make_tuple(0, 0));
		CHECK(a.nCols() == 0);
		CHECK(a.nRows() == 0);
	}
	SUBCASE("MEMORY ALLOCATION") {
		MatrixS a;
		CHECK_THROWS_AS(a.at(0,0) = 0, std::out_of_range);
	}
	SUBCASE("CONSTRUCTOR WITH SIZE") {
		auto size = std::make_tuple(2,2);
		MatrixS a(size);
		a.at(0,0) = 2;
		a.at(1,1) = 3;
		SUBCASE("SIZE") {
			CHECK(a.ssize() == size);
		}
		SUBCASE("VALUES") {
			CHECK(a.at(0, 0) == 2);
			CHECK(a.at(1, 1) == 3);
		}
		SUBCASE("DEFAULT VALUE") {
			CHECK(a.at(0,1) == 0);
		}
		SUBCASE("TUPLE VALUE") {
			a.at(std::make_tuple(0, 1)) = 5;
			CHECK(a.at(std::make_tuple(0, 1)) == 5);
		}
	}
	SUBCASE("CONSTRUCTOR FROM ANOTHER INSTANCE") {
		auto size = std::make_tuple(2, 2);
		MatrixS b(size);
		b.at(0, 0) = 2;
		b.at(1, 1) = 3;
		MatrixS a(b);
		SUBCASE("SIZE") {
			CHECK(a.ssize() == b.ssize());
			CHECK(a.ssize() == size);
		}
		SUBCASE("MatrixS VALUES") {
			CHECK(a.at(0, 0) == b.at(0, 0));
			CHECK(a.at(1, 1) == b.at(1, 1));
			CHECK(a.at(1, 1) == 3);
		}
		SUBCASE("CHANGE VALUES") {
			b.at(1,1) = 10;
			CHECK(a.at(1, 1) != b.at(1, 1));
			CHECK(b.at(1, 1) == 10);
			CHECK(a.at(1, 1) == 3);
		}
	}
	SUBCASE("MATRIXS 2*3") {
		auto size = std::make_tuple(2, 3);
		MatrixS b(size);
		b.at(0, 0) = 0;
		b.at(0, 1) = 1;
		b.at(0, 2) = 2;
		b.at(1, 0) = 4;
		b.at(1, 1) = 5;
		b.at(1, 2) = 6;
		MatrixS a(b);
		CHECK(a.at(0, 0) == 0);
		CHECK(a.at(0, 1) == 1);
		CHECK(a.at(0, 2) == 2);
		CHECK(a.at(1, 0) == 4);
		CHECK(a.at(1, 1) == 5);
		CHECK(a.at(1, 2) == 6);	
	}
	SUBCASE("MATRIXS 3*2") {
		auto size = std::make_tuple(3,2);
		MatrixS b(size);
		b.at(0, 0) = 0;
		b.at(0, 1) = 1;
		b.at(1, 0) = 2;
		b.at(1, 1) = 4;
		b.at(2, 0) = 5;
		b.at(2, 1) = 6;
		MatrixS a(b);
		CHECK(a.at(0, 0) == 0);
		CHECK(a.at(0, 1) == 1);
		CHECK(a.at(1, 0) == 2);
		CHECK(a.at(1, 1) == 4);
		CHECK(a.at(2, 0) == 5);
		CHECK(a.at(2, 1) == 6);
	}
}
TEST_CASE("INTERFACE")
{
	SUBCASE("EQUIVALENCE") {
		auto size = std::make_tuple(2, 2);
		MatrixS b(size);
		b.at(0, 0) = 2;
		b.at(1, 1) = 3;
		MatrixS a = b;
		SUBCASE("SIZE") {
			CHECK(a.ssize() == b.ssize());
			CHECK(a.ssize() == size);
		}
		SUBCASE("MatrixS VALUES") {
			CHECK(a.at(0, 0) == b.at(0, 0));
			CHECK(a.at(1, 1) == b.at(1, 1));
			CHECK(a.at(1, 1) == 3);
		}
		SUBCASE("CHANGE VALUES") {
			b.at(1, 1) = 10;
			CHECK(a.at(1, 1) != b.at(1, 1));
			CHECK(b.at(1, 1) == 10);
			CHECK(a.at(1, 1) == 3);
		}
		SUBCASE("A=A") {
			auto size = std::make_tuple(2, 2);
			MatrixS b(size);
			SUBCASE("0") {
				CHECK(b.at(0, 0) == 0);
			}
			b = b;
			b.at(1, 1) = 2;
			SUBCASE("SIZE") {
				CHECK(b.ssize() == size);
			}
			SUBCASE("ArrayD VALUES") {
				CHECK(b.at(0, 0) == 0);
				CHECK(b.at(1, 1) == 2);
			}
			SUBCASE("CHANGE VALUES") {
				b.at(1, 1) = 10;
				CHECK(b.at(1, 1) == 10);
			}
		}
		SUBCASE("INDEX") {
			auto size = std::make_tuple(2, 2);
			MatrixS a(size);
			a.at(0, 0) = 1;
			SUBCASE("LHS") {
				int b = 3;
				a.at(1, 1) = b;
				CHECK(a.at(1, 1) == b);
			}
			SUBCASE("RHS") {
				int b = 3;
				a.at(1, 1) = b;
				CHECK(b == a.at(1, 1));
			}
			SUBCASE("INDEX OUT OF RANGE(>=size)") {
				int b = 3;
				CHECK_THROWS_AS(a.at(size) = b, std::out_of_range);
			}
			SUBCASE("INDEX OUT OF RANGE(<(0,0)") {
				int b = 3;
				CHECK_THROWS_AS(a.at(-1, -1) = b, std::out_of_range);
			}
			SUBCASE("INDEX OUT OF RANGE(COLS)") {
				int b = 3;
				CHECK_THROWS_AS(a.at(0, a.nCols()) = b, std::out_of_range);
			}
			SUBCASE("INDEX OUT OF RANGE(ROWS)") {
				int b = 3;
				CHECK_THROWS_AS(a.at(a.nRows(), 0) = b, std::out_of_range);
			}
		}
		SUBCASE("SIZE AND CAPACITY") {
			SUBCASE("SSIZE") {
				auto size = std::make_tuple(2, 2);
				MatrixS a(size);
				CHECK(a.ssize() == size);
			}
			SUBCASE("RESIZE>SIZE") {
				auto size = std::make_tuple(2, 2);
				MatrixS a(size);
				a.at(1, 1) = 5;
				a.at(1, 0) = 6;
				auto new_size = std::make_tuple(2, 3);
				a.resize(new_size);
				CHECK(a.ssize() == new_size);
				CHECK(a.at(1, 1) == 5);
				CHECK(a.at(0, 0) == 0);
				CHECK(a.at(1, 0) == 6);
				CHECK(a.at(1, 2) == 0);
				CHECK_THROWS_AS(a.at(new_size) = 0, std::out_of_range);
			}
			SUBCASE("RESIZE<SIZE") {
				auto size = std::make_tuple(3, 3);
				MatrixS a(size);
				a.at(1, 1) = 5;
				auto new_size = std::make_tuple(2, 2);
				a.resize(new_size);
				CHECK(a.ssize() == new_size);
				CHECK(a.at(1, 1) == 5);
				CHECK(a.at(0, 0) == 0);
				CHECK(a.at(0, 1) == 0);
				CHECK_THROWS_AS(a.at(new_size) = 1, std::out_of_range);
			}
			SUBCASE("RESIZE 0") {
				auto size = std::make_tuple(3, 3);
				MatrixS a(size);
				CHECK_THROWS_AS(a.resize(0, 0), std::invalid_argument);
			}
		}
	}
}