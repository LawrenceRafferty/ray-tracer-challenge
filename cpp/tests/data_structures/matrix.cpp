#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/matrix/matrix.cpp"

using data_structures::matrix;

TEST_CASE("a new matrix is initialized with zeros")
{
	int dimension = 4;
	auto m = matrix(dimension);
	for (int row = 0; row < dimension; row++)
	{
		for (int column = 0; column < dimension; column++)
			REQUIRE(0 == m.getElementAt(row, column));
	}
}

TEST_CASE("constructing and inspecting a 4x4 matrix")
{
	auto m = matrix
	{
		1, 2, 3, 4, 
		5.5, 6.5, 7.5, 8.5, 
		9, 10, 11, 12, 
		13.5, 14.5, 15.5, 16.5
	};

	REQUIRE(1 == m.getElementAt(0, 0));
	REQUIRE(4 == m.getElementAt(0, 3));
	REQUIRE(5.5 == m.getElementAt(1, 0));
	REQUIRE(7.5 == m.getElementAt(1, 2));
	REQUIRE(11 == m.getElementAt(2, 2));
	REQUIRE(13.5 == m.getElementAt(3, 0));
	REQUIRE(15.5 == m.getElementAt(3, 2));
}

TEST_CASE("a 2x2 matrix ought to be representable")
{
	auto m = matrix
	{
		-3, 5,
		1, -2
	};

	REQUIRE(-3 == m.getElementAt(0, 0));
	REQUIRE(5 == m.getElementAt(0, 1));
	REQUIRE(1 == m.getElementAt(1, 0));
	REQUIRE(-2 == m.getElementAt(1, 1));
}

TEST_CASE("a 3x3 matrix ought to be representable")
{
	auto m = matrix
	{
		-3, 5, 0,
		1, -2, -7,
		0, 1, 1
	};

	REQUIRE(-3 == m.getElementAt(0, 0));
	REQUIRE(-2 == m.getElementAt(1, 1));
	REQUIRE(1 == m.getElementAt(2, 2));
}
