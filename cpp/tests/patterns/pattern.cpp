#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/color/color.cpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"
#include "../../src/data_structures/ray/ray.cpp"
#include "../../src/data_structures/material/material.cpp"
#include "../../src/data_structures/matrix/matrix.cpp"
#include "../../src/patterns/pattern.cpp"
#include "../../src/patterns/solid/solid.cpp"
#include "../../src/patterns/stripe/stripe.cpp"
#include "../../src/patterns/test/test.cpp"
#include "../../src/shapes/shape.cpp"
#include "../../src/shapes/sphere/sphere.cpp"

using data_structures::color;
using data_structures::four_tuple;
using data_structures::matrix;
using shapes::sphere;

auto white = color(255, 255, 255);
auto black = color();
auto whitePattern = std::make_shared<patterns::solid>(white);
auto blackPattern = std::make_shared<patterns::solid>(black);

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
	auto shapeLocalPoint = shape.getLocalPoint(four_tuple::point(2, 3, 4));
	auto c = pattern.getColorOnObjectAtPoint(shapeLocalPoint);
	REQUIRE(color(1, 1.5, 2) == c);
}

TEST_CASE("a pattern with a pattern transformation")
{
	auto shape = sphere();
	auto pattern = patterns::test();
	pattern.setTransform(std::move(matrix::scaling(2, 2, 2)));
	auto shapeLocalPoint = shape.getLocalPoint(four_tuple::point(2, 3, 4));
	auto c = pattern.getColorOnObjectAtPoint(shapeLocalPoint);
	REQUIRE(color(1, 1.5, 2) == c);
}

TEST_CASE("a pattern with both an object and a pattern transformation")
{
	auto shape = sphere();
	shape.setTransform(std::move(matrix::scaling(2, 2, 2)));
	auto pattern = patterns::test();
	pattern.setTransform(std::move(matrix::translation(0.5, 1, 1.5)));
	auto shapeLocalPoint = shape.getLocalPoint(four_tuple::point(2.5, 3, 3.5));
	auto c = pattern.getColorOnObjectAtPoint(shapeLocalPoint);
	REQUIRE(color(0.75, 0.5, 0.25) == c);
}

TEST_CASE("a solid pattern has the same color everywhere")
{
	auto c = color(1, 2, 3);
	auto solidPattern = patterns::solid(c);
	REQUIRE(c == solidPattern.getColorAtPoint(four_tuple::point(123, 456, 789)));
}

TEST_CASE("a stripe pattern is constant in y")
{

	auto stripePattern = patterns::stripe { whitePattern, blackPattern };
	REQUIRE(white == stripePattern.getColorAtPoint(four_tuple::point(0, -2.6, 0)));
	REQUIRE(white == stripePattern.getColorAtPoint(four_tuple::point(0, -1.4, 0)));
	REQUIRE(white == stripePattern.getColorAtPoint(four_tuple::point(0, 0, 0)));
	REQUIRE(white == stripePattern.getColorAtPoint(four_tuple::point(0, 1.4, 0)));
	REQUIRE(white == stripePattern.getColorAtPoint(four_tuple::point(0, 2.6, 0)));
}

TEST_CASE("a stripe pattern is constant in z")
{
	auto stripePattern = patterns::stripe { whitePattern, blackPattern };
	REQUIRE(white == stripePattern.getColorAtPoint(four_tuple::point(0, 0, -2.6)));
	REQUIRE(white == stripePattern.getColorAtPoint(four_tuple::point(0, 0, -1.4)));
	REQUIRE(white == stripePattern.getColorAtPoint(four_tuple::point(0, 0, 0)));
	REQUIRE(white == stripePattern.getColorAtPoint(four_tuple::point(0, 0, 1.4)));
	REQUIRE(white == stripePattern.getColorAtPoint(four_tuple::point(0, 0, 2.6)));
}

TEST_CASE("a stripe pattern alternates in x")
{
	auto stripePattern = patterns::stripe { whitePattern, blackPattern };
	REQUIRE(white == stripePattern.getColorAtPoint(four_tuple::point(-1.00001, 0, 0)));
	REQUIRE(black == stripePattern.getColorAtPoint(four_tuple::point(-1, 0, 0)));
	REQUIRE(black == stripePattern.getColorAtPoint(four_tuple::point(-0.00001, 0, 0)));
	REQUIRE(white == stripePattern.getColorAtPoint(four_tuple::point(0, 0, 0)));
	REQUIRE(white == stripePattern.getColorAtPoint(four_tuple::point(0.00001, 0, 0)));
	REQUIRE(black == stripePattern.getColorAtPoint(four_tuple::point(1, 0, 0)));
	REQUIRE(black == stripePattern.getColorAtPoint(four_tuple::point(1.00001, 0, 0)));
}

TEST_CASE("a stripe pattern with many different stripes")
{
	auto red = color(255, 0, 0);
	auto green = color(0, 255, 0);
	auto blue = color(0, 0, 255);
	auto stripePattern = patterns::stripe
	{
		whitePattern,
		blackPattern,
		std::make_shared<patterns::solid>(red),
		std::make_shared<patterns::solid>(green),
		std::make_shared<patterns::solid>(blue)
	};
	REQUIRE(white == stripePattern.getColorAtPoint(four_tuple::point(0, 0, 0)));
	REQUIRE(black == stripePattern.getColorAtPoint(four_tuple::point(1, 0, 0)));
	REQUIRE(red == stripePattern.getColorAtPoint(four_tuple::point(2, 0, 0)));
	REQUIRE(green == stripePattern.getColorAtPoint(four_tuple::point(3, 0, 0)));
	REQUIRE(blue == stripePattern.getColorAtPoint(four_tuple::point(4, 0, 0)));
}

TEST_CASE("stripes with an object transformation")
{
	auto object = sphere();
	object.setTransform(matrix::scaling(2, 2, 2));
	auto stripePattern = patterns::stripe
	{
		whitePattern,
		blackPattern
	};
	auto localPoint = object.getLocalPoint(four_tuple::point(1.5, 0, 0));
	auto c = stripePattern.getColorOnObjectAtPoint(localPoint);
	REQUIRE(white == c);
}

TEST_CASE("stripes with a pattern transformation")
{
	auto object = sphere();
	auto stripePattern = patterns::stripe
	{
		whitePattern,
		blackPattern
	};
	stripePattern.setTransform(matrix::scaling(2, 2, 2));
	auto localPoint = object.getLocalPoint(four_tuple::point(1.5, 0, 0));
	auto c = stripePattern.getColorOnObjectAtPoint(localPoint);
	REQUIRE(white == c);
}

TEST_CASE("stripes with both an object and pattern transformation")
{
	auto object = sphere();
	object.setTransform(matrix::scaling(2, 2, 2));
	auto stripePattern = patterns::stripe
	{
		whitePattern,
		blackPattern
	};
	stripePattern.setTransform(matrix::translation(0.5, 0, 0));
	auto localPoint = object.getLocalPoint(four_tuple::point(2.5, 0, 0));
	auto c = stripePattern.getColorOnObjectAtPoint(localPoint);
	REQUIRE(white == c);
}
