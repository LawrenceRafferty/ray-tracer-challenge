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

TEST_CASE("matrix equality with identical matrices")
{
	auto a = matrix
	{
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 8, 7, 6,
		5, 4, 3, 2
	};

	auto b = matrix
	{
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 8, 7, 6,
		5, 4, 3, 2
	};

	REQUIRE(a == b);
}

TEST_CASE("matrix equality with different matrices")
{
	auto a = matrix
	{
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 8, 7, 6,
		5, 4, 3, 2
	};

	auto b = matrix
	{
		2, 3, 4, 5,
		6, 7, 8, 9,
		8, 7, 6, 5,
		4, 3, 2, 1
	};

	REQUIRE(a != b);
}

TEST_CASE("multiplying two matrices")
{
	auto a = matrix
	{
		1, 2, 3, 4, 
		5, 6, 7, 8, 
		9, 8, 7, 6, 
		5, 4, 3, 2
	};

	auto b = matrix
	{
		-2, 1, 2, 3, 
		3, 2, 1, -1, 
		4, 3, 6, 5, 
		1, 2, 7, 8
	}; 
	
	auto expected = matrix
	{
		20, 22, 50, 48, 
		44, 54, 114, 108, 
		40, 58, 110, 102, 
		16, 26, 46, 42
	};
 
	REQUIRE(expected == a * b);
}

TEST_CASE("constructing and inspecting a 2x4 matrix")
{
	auto m = matrix(2, 4,
	{
		1, 2, 3, 4,
		5, 6, 7, 8
	});

	REQUIRE(1 == m.getElementAt(0, 0));
	REQUIRE(2 == m.getElementAt(0, 1));
	REQUIRE(3 == m.getElementAt(0, 2));
	REQUIRE(4 == m.getElementAt(0, 3));
	REQUIRE(5 == m.getElementAt(1, 0));
	REQUIRE(6 == m.getElementAt(1, 1));
	REQUIRE(7 == m.getElementAt(1, 2));
	REQUIRE(8 == m.getElementAt(1, 3));
}

TEST_CASE("multiplying matrices with different dimensions")
{
	auto fourByThree = matrix(4, 3,
	{
		1, 1, 1,
		2, 2, 2,
		3, 3, 3,
		4, 4, 4
	});

	auto threeByTwo = matrix(3, 2,
	{
		1, 2,
		3, 4,
		5, 6,
	});

	auto fourByTwo = matrix(4, 2,
	{
		9, 12,
		18, 24,
		27, 36,
		36, 48
	});

	REQUIRE(fourByTwo == fourByThree * threeByTwo);
}
