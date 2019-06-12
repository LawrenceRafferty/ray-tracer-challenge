#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/color/color.cpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"
#include "../../src/data_structures/intersection/intersection.cpp"
#include "../../src/data_structures/intersection_computations/intersection_computations.cpp"
#include "../../src/data_structures/intersections/intersections.cpp"
#include "../../src/data_structures/material/material.cpp"
#include "../../src/data_structures/matrix/matrix.cpp"
#include "../../src/data_structures/ray/ray.cpp"
#include "../../src/data_structures/world/world.cpp"
#include "../../src/shapes/sphere/sphere.cpp"

using data_structures::intersection;
using data_structures::intersection_computations;
using data_structures::intersections;
using data_structures::ray;
using shapes::sphere;

TEST_CASE("an intersection encapsulates t and object")
{
	auto s = std::make_shared<sphere>();
	auto i = intersection(3.5, s);
	REQUIRE(3.5 == i.getT());
	REQUIRE(s == i.getObject());
}

TEST_CASE("aggregating intersections")
{
	auto s = std::make_shared<sphere>();
	auto i1 = intersection(1, s);
	auto i2 = intersection(2, s);
	auto xs = intersections { i1, i2 };
	REQUIRE(2 == xs.size());
	REQUIRE(1 == xs.at(0).getT());
	REQUIRE(2 == xs.at(1).getT());
}

TEST_CASE("find sets the object on the intersection")
{
	auto r = ray(four_tuple::point(0, 0, -5), four_tuple::vector(0, 0, 1));
	auto s = std::make_shared<sphere>();
	auto xs = intersections::find(s, r);
	REQUIRE(2 == xs.size());
	REQUIRE(s == xs.at(0).getObject());
	REQUIRE(s == xs.at(1).getObject());
}

TEST_CASE("a negative intersection is not a hit candidate")
{
	auto s = std::make_shared<sphere>();
	auto i = intersection(-1, s);
	REQUIRE(false == i.isHitCandidate());
}

TEST_CASE("an intersection at 0 is a hit candidate")
{
	auto s = std::make_shared<sphere>();
	auto i = intersection(0, s);
	REQUIRE(true == i.isHitCandidate());
}

TEST_CASE("a positve intersection is a hit candidate")
{
	auto s = std::make_shared<sphere>();
	auto i = intersection(1, s);
	REQUIRE(true == i.isHitCandidate());
}

TEST_CASE("the hit, when all intersections have positive t")
{
	auto s = std::make_shared<sphere>();
	auto i1 = intersection(1, s);
	auto i2 = intersection(2, s);
	auto xs = intersections { i2, i1 };
	auto i = xs.getHit();
	REQUIRE(i1 == *i);
}

TEST_CASE("the hit, when some intersections have negative t")
{
	auto s = std::make_shared<sphere>();
	auto i1 = intersection(-1, s);
	auto i2 = intersection(1, s);
	auto xs = intersections { i2, i1 };
	auto i = xs.getHit();
	REQUIRE(i2 == *i);
}

TEST_CASE("the hit, when all intersections have negative t")
{
	auto s = std::make_shared<sphere>();
	auto i1 = intersection(-2, s);
	auto i2 = intersection(-1, s);
	auto xs = intersections { i2, i1 };
	auto i = xs.getHit();
	REQUIRE(nullptr == i);
}

TEST_CASE("the hit is always the lowest nonnegative intersection")
{
	auto s = std::make_shared<sphere>();
	auto i1 = intersection(5, s);
	auto i2 = intersection(7, s);
	auto i3 = intersection(-3, s);
	auto i4 = intersection(2, s);
	auto xs = intersections { i1, i2, i3, i4 };
	auto i = xs.getHit();
	REQUIRE(i4 == *i);
}

TEST_CASE("precomputing the state of an intersection")
{
	auto r = ray(four_tuple::point(0, 0, -5), four_tuple::vector(0, 0, 1));
	auto shape = std::make_shared<sphere>();
	auto i = intersection(4, shape);
	auto computations = intersection_computations::prepare(i, r);
	REQUIRE(i.getT() == computations.getT());
	REQUIRE(i.getObject() == computations.getObject());
	REQUIRE(four_tuple::point(0, 0, -1) == computations.getPoint());
	REQUIRE(four_tuple::vector(0, 0, -1) == computations.getEyeVector());
	REQUIRE(four_tuple::vector(0, 0, -1) == computations.getNormalVector());
}
