#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"
#include "../../src/data_structures/ray/ray.cpp"
#include "../../src/data_structures/matrix/matrix.cpp"
#include "../../src/shapes/sphere/sphere.cpp"

using data_structures::four_tuple;
using data_structures::matrix;
using data_structures::ray;
using shapes::sphere;

TEST_CASE("a ray intersects a sphere at two points")
{
	auto r = ray(four_tuple::point(0, 0, -5), four_tuple::vector(0, 0, 1));
	auto s = sphere();
	auto xs = s.intersect(r);
	REQUIRE(2 == xs.size());
	REQUIRE(4.0 == xs.at(0));
	REQUIRE(6.0 == xs.at(1));
}

TEST_CASE("a ray intersects a sphere at a tangent")
{
	auto r = ray(four_tuple::point(0, 1, -5), four_tuple::vector(0, 0, 1));
	auto s = sphere();
	auto xs = s.intersect(r);
	REQUIRE(2 == xs.size());
	REQUIRE(5.0 == xs.at(0));
	REQUIRE(5.0 == xs.at(1));
}

TEST_CASE("a ray misses a sphere")
{
	auto r = ray(four_tuple::point(0, 2, -5), four_tuple::vector(0, 0, 1));
	auto s = sphere();
	auto xs = s.intersect(r);
	REQUIRE(0 == xs.size());
}

TEST_CASE("a ray originates inside a sphere")
{
	auto r = ray(four_tuple::point(0, 0, 0), four_tuple::vector(0, 0, 1));
	auto s = sphere();
	auto xs = s.intersect(r);
	REQUIRE(2 == xs.size());
	REQUIRE(-1.0 == xs.at(0));
	REQUIRE(1.0 == xs.at(1));
}

TEST_CASE("a sphere is behind a ray")
{
	auto r = ray(four_tuple::point(0, 0, 5), four_tuple::vector(0, 0, 1));
	auto s = sphere();
	auto xs = s.intersect(r);
	REQUIRE(2 == xs.size());
	REQUIRE(-6.0 == xs.at(0));
	REQUIRE(-4.0 == xs.at(1));
}

TEST_CASE("a sphere's default transformation")
{
	auto s = sphere();
	auto identity = matrix
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	REQUIRE(identity == s.getTransform());
}

TEST_CASE("changing a sphere's transformation")
{
	auto s = sphere();
	auto t = matrix::translation(2, 3, 4);
	s.setTransform(t);
	REQUIRE(t == s.getTransform());
}

TEST_CASE("intersecting a scaled sphere with a ray")
{
	auto r = ray(four_tuple::point(0, 0, -5), four_tuple::vector(0, 0, 1));
	auto s = sphere();
	s.setTransform(matrix::scaling(2, 2, 2));
	auto xs = s.intersect(r);
	REQUIRE(2 == xs.size());
	REQUIRE(3 == xs.at(0));
	REQUIRE(7 == xs.at(1));
}

TEST_CASE("intersecting a translated sphere with a ray")
{
	auto r = ray(four_tuple::point(0, 0, -5), four_tuple::vector(0, 0, 1));
	auto s = sphere();
	s.setTransform(matrix::translation(5, 0, 0));
	auto xs = s.intersect(r);
	REQUIRE(0 == xs.size());
}
