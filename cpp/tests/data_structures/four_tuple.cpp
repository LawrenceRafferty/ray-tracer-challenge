#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"

data_structures::four_tuple point(float x, float y, float z)
{
	return data_structures::four_tuple::point(x, y, z);
}

data_structures::four_tuple vector(float x, float y, float z)
{
	return data_structures::four_tuple::vector(x, y, z);
}

TEST_CASE("point creates a point")
{
	auto p = point(1.1, 2.2, 3.3);
	REQUIRE(p.getW() == 1);
}

TEST_CASE("vector creates a vector")
{
	auto v = vector(1.1, 2.2, 3.3);
	REQUIRE(v.getW() == 0);
}

TEST_CASE("self equality")
{
	auto p = point(1.1, 2.2, 3.3);
	REQUIRE(p == p);
}

TEST_CASE("points and vectors are not equal")
{
	auto p = point(1.1, 2.2, 3.3);
	auto v = vector(1.1, 2.2, 3.3);
	REQUIRE(p != v);
}

TEST_CASE("adding a vector to a point is a new point")
{
	auto a1 = point(3, -2, 5);
	auto a2 = vector(-2, 3, 1);
	auto expected = point(1, 1, 6);
	REQUIRE(expected == (a1 + a2));
}

TEST_CASE("adding a vector to a vector is a new vector")
{
	auto v = vector(1.1, 2.2, 3.3);
	auto expected = vector(2.2, 4.4, 6.6);
	REQUIRE(expected == (v + v));
}

TEST_CASE("subtracting two points is a vector")
{
	auto p1 = point(3, 2, 1);
	auto p2 = point(5, 6, 7);
	auto expected = vector(-2, -4, -6);
	REQUIRE(expected == (p1 - p2));
}

TEST_CASE("subtracting a vector from a point is a point")
{
	auto p = point(3, 2, 1);
	auto v = vector(5, 6, 7);
	auto expected = point(-2, -4, -6);
	REQUIRE(expected == (p - v));
}

TEST_CASE("subtracting a vector from a vector is a vector")
{
	auto v1 = vector(3, 2, 1);
	auto v2 = vector(5, 6, 7);
	auto expected = vector(-2, -4, -6);
	REQUIRE(expected == (v1 - v2));
}

TEST_CASE("subtracting a vector from the zero vector")
{
	auto zero = vector(0, 0, 0);
	auto v = vector(1, -2, 3);
	auto expected = vector(-1, 2, -3);
	REQUIRE(expected == (zero - v));
}

TEST_CASE("negating a vector")
{
	auto v = vector(1, -2, 3);
	auto expected = vector(-1, 2, -3);
	REQUIRE(expected == -v);
}

TEST_CASE("multiplying a vector by a scalar")
{
	auto v = vector(1, -2, 3);
	auto expected = vector(3.5, -7, 10.5);
	REQUIRE(expected == (v * 3.5f));
}

TEST_CASE("multiplying a vector by a fraction")
{
	auto v = vector(1, -2, 3);
	auto expected = vector(0.5, -1, 1.5);
	REQUIRE(expected == (v * 0.5f));
}

TEST_CASE("dividing a vector by a scalar")
{
	auto v = vector(1, -2, 3);
	auto expected = vector(0.5, -1, 1.5);
	REQUIRE(expected == (v / 2));
}
