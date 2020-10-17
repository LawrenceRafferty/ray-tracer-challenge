#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/color/color.cpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"
#include "../../src/data_structures/ray/ray.cpp"
#include "../../src/data_structures/material/material.cpp"
#include "../../src/data_structures/matrix/matrix.cpp"
#include "../../src/shapes/shape.cpp"
#include "../../src/shapes/plane/plane.cpp"

using data_structures::four_tuple;
using data_structures::material;
using data_structures::matrix;
using data_structures::ray;
using shapes::plane;

TEST_CASE("the normal of a plane is constant everywhere")
{
	auto p = plane();
	auto n1 = p.getLocalNormalAtLocalPoint_test(four_tuple::point(0, 0, 0));
	auto n2 = p.getLocalNormalAtLocalPoint_test(four_tuple::point(10, 0, -10));
	auto n3 = p.getLocalNormalAtLocalPoint_test(four_tuple::point(-5, 0, 150));
	REQUIRE(four_tuple::vector(0, 1, 0) == n1);
	REQUIRE(four_tuple::vector(0, 1, 0) == n2);
	REQUIRE(four_tuple::vector(0, 1, 0) == n3);
}

TEST_CASE("intersect with a ray parallel to the plane")
{
	auto p = plane();
	auto r = ray(four_tuple::point(0, 10, 0), four_tuple::vector(0, 0, 1));
	auto xs = p.localIntersect_test(r);
	REQUIRE(xs.empty());
}

TEST_CASE("a ray intersecting a plane from above")
{
	auto p = plane();
	auto r = ray(four_tuple::point(0, 1, 0), four_tuple::vector(0, -1, 0));
	auto xs = p.localIntersect_test(r);
	REQUIRE (1 == xs.size());
	REQUIRE(1 == xs.at(0));
}

TEST_CASE("a ray intersecting a plane from below")
{
	auto p = plane();
	auto r = ray(four_tuple::point(0, -1, 0), four_tuple::vector(0, 1, 0));
	auto xs = p.localIntersect_test(r);
	REQUIRE(1 == xs.size());
	REQUIRE(1 == xs.at(0));
}
