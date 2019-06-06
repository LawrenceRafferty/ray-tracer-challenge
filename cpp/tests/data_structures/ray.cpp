#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"
#include "../../src/data_structures/matrix/matrix.cpp"
#include "../../src/data_structures/ray/ray.cpp"

using data_structures::four_tuple;
using data_structures::matrix;
using data_structures::ray;

TEST_CASE("creating and querying a ray")
{
	auto origin = four_tuple::point(1, 2, 3);
	auto direction = four_tuple::vector(4, 5, 6);
	auto r = ray(origin, direction);
	REQUIRE(origin == r.getOrigin());
	REQUIRE(direction == r.getDirection());
}

TEST_CASE("computing a point from a distance")
{
	auto origin = four_tuple::point(2, 3, 4);
	auto r = ray(origin, four_tuple::vector(1, 0, 0));
	REQUIRE(origin == r.getPositionAt(0));
	auto expected = four_tuple::point(3, 3, 4);
	REQUIRE(expected == r.getPositionAt(1));
	expected = four_tuple::point(1, 3, 4);
	REQUIRE(expected == r.getPositionAt(-1));
	expected = four_tuple::point(4.5, 3, 4);
	REQUIRE(expected == r.getPositionAt(2.5));
}

TEST_CASE("translating a ray")
{
	auto r = ray(four_tuple::point(1, 2, 3), four_tuple::vector(0, 1, 0));
	auto m = matrix::translation(3, 4, 5);
	auto r2 = r.getTransformed(m);
	REQUIRE(four_tuple::point(4, 6, 8) == r2.getOrigin());
	REQUIRE(four_tuple::vector(0, 1, 0) == r2.getDirection());
}

TEST_CASE("scaling a ray")
{
	auto r = ray(four_tuple::point(1, 2, 3), four_tuple::vector(0, 1, 0));
	auto m = matrix::scaling(2, 3, 4);
	auto r2 = r.getTransformed(m);
	REQUIRE(four_tuple::point(2, 6, 12) == r2.getOrigin());
	REQUIRE(four_tuple::vector(0, 3, 0) == r2.getDirection());
}
