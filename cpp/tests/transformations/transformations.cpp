#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"
#include "../../src/data_structures/matrix/matrix.cpp"
#include "../../src/transformations/transformations.cpp"

using data_structures::four_tuple;
using data_structures::matrix;

TEST_CASE("the transformation matrix for the default orientation")
{
	auto from = four_tuple::point(0, 0, 0);
	auto to = four_tuple::point(0, 0, -1);
	auto up = four_tuple::vector(0, 1, 0);
	auto viewTransform = transformations::getViewTransform(from, to, up);
	auto identityMatrix = matrix
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	REQUIRE(identityMatrix == viewTransform);
}

TEST_CASE("a view transformation matrix looking in the positive z direction")
{
	auto from = four_tuple::point(0, 0, 0);
	auto to = four_tuple::point(0, 0, 1);
	auto up = four_tuple::vector(0, 1, 0);
	auto viewTransform = transformations::getViewTransform(from, to, up);
	auto expected = matrix::scaling(-1, 1, -1);
	REQUIRE(expected == viewTransform);
}

TEST_CASE("the view transformation moves the world")
{
	auto from = four_tuple::point(0, 0, 8);
	auto to = four_tuple::point(0, 0, 0);
	auto up = four_tuple::vector(0, 1, 0);
	auto viewTransform = transformations::getViewTransform(from, to, up);
	auto expected = matrix::translation(0, 0, -8);
	REQUIRE(expected == viewTransform);
}

TEST_CASE("an arbitrary view transformation")
{
	auto from = four_tuple::point(1, 3, 2);
	auto to = four_tuple::point(4, -2, 8);
	auto up = four_tuple::vector(1, 1, 0);
	auto viewTransform = transformations::getViewTransform(from, to, up);
	auto expected = matrix
	{
		-0.50709, 0.50709,  0.67612, -2.36643,
		0.76772, 0.60609,  0.12122, -2.82843,
		-0.35857, 0.59761, -0.71714,  0.00000,
		0.00000, 0.00000,  0.00000,  1.00000
	};
	REQUIRE(expected == viewTransform);
}
