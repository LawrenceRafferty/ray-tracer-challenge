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
