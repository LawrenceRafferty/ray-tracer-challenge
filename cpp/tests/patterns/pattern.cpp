#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/color/color.cpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"
#include "../../src/data_structures/ray/ray.cpp"
#include "../../src/data_structures/material/material.cpp"
#include "../../src/data_structures/matrix/matrix.cpp"
#include "../../src/patterns/pattern.cpp"
#include "../../src/patterns/test/test.cpp"
#include "../../src/shapes/shape.cpp"
#include "../../src/shapes/sphere/sphere.cpp"

using data_structures::color;
using data_structures::four_tuple;
using data_structures::matrix;
using shapes::sphere;

TEST_CASE("the default pattern transformation")
{
	auto pattern = patterns::test();
	auto expected = matrix
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	REQUIRE(expected == pattern.getTransform());
}

TEST_CASE("assigning a transformation")
{
	auto pattern = patterns::test();
	pattern.setTransform(std::move(matrix::translation(1, 2, 3)));
	REQUIRE(matrix::translation(1, 2, 3) == pattern.getTransform());
}

TEST_CASE("a pattern with an object transformation")
{
	auto shape = sphere();
	shape.setTransform(std::move(matrix::scaling(2, 2, 2)));
	auto pattern = patterns::test();
	auto c = pattern.getColorOnObjectAtPoint(shape, four_tuple::point(2, 3, 4));
	REQUIRE(color(1, 1.5, 2) == c);
}

TEST_CASE("a pattern with a pattern transformation")
{
	auto shape = sphere();
	auto pattern = patterns::test();
	pattern.setTransform(std::move(matrix::scaling(2, 2, 2)));
	auto c = pattern.getColorOnObjectAtPoint(shape, four_tuple::point(2, 3, 4));
	REQUIRE(color(1, 1.5, 2) == c);
}

TEST_CASE("a pattern with both an object and a pattern transformation")
{
	auto shape = sphere();
	shape.setTransform(std::move(matrix::scaling(2, 2, 2)));
	auto pattern = patterns::test();
	pattern.setTransform(std::move(matrix::translation(0.5, 1, 1.5)));
	auto c = pattern.getColorOnObjectAtPoint(shape, four_tuple::point(2.5, 3, 3.5));
	REQUIRE(color(0.75, 0.5, 0.25) == c);
}
