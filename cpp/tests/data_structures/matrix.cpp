#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"
#include "../../src/data_structures/matrix/matrix.cpp"

using data_structures::four_tuple;
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

TEST_CASE("a matrix multiplied by a tuple")
{
	auto a = matrix
	{
		1, 2, 3, 4,
		2, 4, 4, 2,
		8, 6, 4, 1,
		0, 0, 0, 1
	};

	auto b = four_tuple(1, 2, 3, 1);
	auto expected = four_tuple(18, 24, 33, 1);
	REQUIRE(expected == a * b);
}

TEST_CASE("multiplying a matrix by the identity matrix")
{
	auto a = matrix
	{
		0, 1, 2, 4,
		1, 2, 4, 8,
		2, 4, 8, 16,
		4, 8, 16, 32
	};

	auto identity = matrix
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	REQUIRE(a == a * identity);
}

TEST_CASE("multiplying the identity matrix by a tuple")
{
	auto a = four_tuple(1, 2, 3, 4);
	auto identity = matrix
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	REQUIRE(a == identity * a);
}

TEST_CASE("transposing a matrix")
{
	auto a = matrix
	{
		0, 9, 3, 0,
		9, 8, 0, 8,
		1, 8, 5, 3,
		0, 0, 5, 8
	};

	auto expected = matrix
	{
		0, 9, 1, 0,
		9, 8, 8, 0,
		3, 0, 5, 5,
		0, 8, 3, 8
	};

	REQUIRE(expected == a.getTransposed());
}

TEST_CASE("transposing the identity matrix")
{
	auto identity = matrix
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	auto a = identity.getTransposed();
	REQUIRE(identity == a);
}

TEST_CASE("calculating the determinant of a 2x2 matrix")
{
	auto a = matrix
	{
		1, 5,
		-3, 2
	};

	REQUIRE(17 == a.getDeterminant());
}

TEST_CASE("a submatrix of a 3x3 matrix is a 2x2 matrix")
{
	auto threeByThree = matrix
	{
		1, 5, 0,
		-3, 2, 7,
		0, 6, -3
	};

	auto twoByTwo = matrix{
		-3, 2,
		0, 6
	};

	REQUIRE(twoByTwo == threeByThree.getSubmatrix(0, 2));
}

TEST_CASE("a submatrix of a 4x4 matrix is a 3x3 matrix")
{
	auto fourByFour = matrix
	{
		-6, 1, 1, 6,
		-8, 5, 8, 6,
		-1, 0, 8, 2,
		-7, 1, -1, 1
	};

	auto threeByThree = matrix
		{
		-6, 1, 6,
		-8, 8, 6,
		-7, -1, 1
	};

	REQUIRE(threeByThree == fourByFour.getSubmatrix(2, 1));
}

TEST_CASE("excercise move assignment")
{
	matrix m {2};
	m = matrix
	{
		1, 2,
		3, 4
	};
	REQUIRE(1 == m.getElementAt(0, 0));
}

TEST_CASE("calculating a minor of a 3x3 matrix")
{
	auto a = matrix
	{
		3, 5, 0,
		2, -1, -7,
		6, -1, 5
	};

	auto b = a.getSubmatrix(1, 0);
	REQUIRE(25 == b.getDeterminant());
	REQUIRE(25 == a.getMinorOfElementAt(1, 0));
}

TEST_CASE("calculating a cofactor of a 3x3 matrix")
{
	auto a = matrix
	{
		3, 5, 0,
		2, -1, -7,
		6, -1, 5
	};

	REQUIRE(-12 == a.getMinorOfElementAt(0, 0));
	REQUIRE(-12 == a.getCofactorOfElementAt(0, 0));
	REQUIRE(25 == a.getMinorOfElementAt(1, 0));
	REQUIRE(-25 == a.getCofactorOfElementAt(1, 0));
}

TEST_CASE("calculating the determinant of a 3x3 matrix")
{
	auto a = matrix
	{
		1, 2, 6,
		-5, 8, -4,
		2, 6, 4
	};

	REQUIRE(56 == a.getCofactorOfElementAt(0, 0));
	REQUIRE(12 == a.getCofactorOfElementAt(0, 1));
	REQUIRE(-46 == a.getCofactorOfElementAt(0, 2));
	REQUIRE(-196 == a.getDeterminant());
}

TEST_CASE("calculating the determinant of a 4x4 matrix")
{
	auto a = matrix
	{
		-2, -8, 3, 5,
		-3, 1, 7, 3,
		1, 2, -9, 6,
		-6, 7, 7, -9
	};

	REQUIRE(690 == a.getCofactorOfElementAt(0, 0));
	REQUIRE(447 == a.getCofactorOfElementAt(0, 1));
	REQUIRE(210 == a.getCofactorOfElementAt(0, 2));
	REQUIRE(51 == a.getCofactorOfElementAt(0, 3));
	REQUIRE(-4071 == a.getDeterminant());
}

TEST_CASE("testing an invertible matrix for invertibility")
{
	auto a = matrix
	{
		6, 4, 4, 4,
		5, 5, 7, 6,
		4, -9, 3, -7,
		9, 1, 7, -6
	};

	REQUIRE(-2120 == a.getDeterminant());
	REQUIRE(true == a.isInvertible());
}

TEST_CASE("testing a noninvertible matrix for invertibility")
{
	auto a = matrix
	{
		-4, 2, -2, -3,
		9, 6, 2, 6,
		0, -5, 1, -5,
		0, 0, 0, 0
	};

	REQUIRE(0 == a.getDeterminant());
	REQUIRE(false == a.isInvertible());
}

TEST_CASE("calculating the inverse of a matrix")
{
	auto a = matrix
	{
		-5, 2, 6, -8,
		1, -5, 1, 8,
		7, 7, -6, -7,
		1, -3, 7, 4
	};

	auto b = a.getInverse();
	REQUIRE(532 == a.getDeterminant());
	REQUIRE(-160 == a.getCofactorOfElementAt(2, 3));
	REQUIRE(-160.0f / 532.0f == b.getElementAt(3, 2));
	REQUIRE(105 == a.getCofactorOfElementAt(3, 2));
	REQUIRE(105.0f / 532.0f == b.getElementAt(2, 3));

	auto expected = matrix
	{
		0.21805, 0.45113, 0.24060, -0.04511,
		-0.80827, -1.45677, -0.44361, 0.52068,
		-0.07895, -0.22368, -0.05263, 0.19737,
		-0.52256, -0.81391, -0.30075, 0.30639
	};

	REQUIRE(expected == b);
}

TEST_CASE("calculating the inverse of another matrix")
{
	auto a = matrix
	{
		8, -5, 9, 2,
		7, 5, 6, 1,
		-6, 0, 9, 6,
		-3, 0, -9, -4
	};

	auto expected = matrix
	{
		-0.15385, -0.15385, -0.28205, -0.53846,
		-0.07692, 0.12308, 0.02564, 0.03077,
		0.35897, 0.35897, 0.43590, 0.92308,
		-0.69231, -0.69231, -0.76923, -1.92308
	};

	REQUIRE(expected == a.getInverse());
}

TEST_CASE("calculating the inverse of a third matrix")
{
	auto a = matrix
	{
		9, 3, 0, 9,
		-5, -2, -6, -3,
		-4, 9, 6, 4,
		-7, 6, 6, 2
	};

	auto expected = matrix
	{
		-0.04074, -0.07778, 0.14444, -0.22222,
		-0.07778, 0.03333, 0.36667, -0.33333,
		-0.02901, -0.14630, -0.10926, 0.12963,
		0.17778, 0.06667, -0.26667, 0.33333
	};

	REQUIRE(expected == a.getInverse());
}

TEST_CASE("multiplying a product by its inverse")
{
	auto identity = matrix
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	auto a = matrix
	{
		3, -9, 7, 3,
		3, -8, 2, -9,
		-4, 4, 4, 1,
		-6, 5, -1, 1
	};

	auto inverse_a = a.getInverse();
	REQUIRE(identity == a * inverse_a);

	auto b = matrix
	{
		8, 2, 2, 2,
		3, -1, 7, 0,
		7, 0, 5, 4,
		6, -2, 0, 5
	};

	auto inverse_b = b.getInverse();
	REQUIRE(identity == b * inverse_b);

	auto c = a * b;
	REQUIRE(a == c * inverse_b);
}
