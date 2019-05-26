#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"

TEST_CASE("point creates a point")
{
	auto p = data_structures::four_tuple::point(1.1, 2.2, 3.3);
	REQUIRE(p.getW() == 1);
}

TEST_CASE("vector creates a vector")
{
	auto v = data_structures::four_tuple::vector(1.1, 2.2, 3.3);
	REQUIRE(v.getW() == 0);
}

TEST_CASE("self equality")
{
	auto p = data_structures::four_tuple::point(1.1, 2.2, 3.3);
	REQUIRE(p == p);
}

TEST_CASE("points and vectors are not equal")
{
	auto p = data_structures::four_tuple::point(1.1, 2.2, 3.3);
	auto v = data_structures::four_tuple::vector(1.1, 2.2, 3.3);
	REQUIRE(p != v);
}

TEST_CASE("adding a vector to a point is a new point")
{
	auto a1 = data_structures::four_tuple::point(3, -2, 5);
	auto a2 = data_structures::four_tuple::vector(-2, 3, 1);
	auto expected = data_structures::four_tuple::point(1, 1, 6);
	REQUIRE(expected == (a1 + a2));
}

TEST_CASE("adding a vector to a vector is a new vector")
{
	auto v = data_structures::four_tuple::vector(1.1, 2.2, 3.3);
	auto expected = data_structures::four_tuple::vector(2.2, 4.4, 6.6);
	REQUIRE(expected == (v + v));
}
