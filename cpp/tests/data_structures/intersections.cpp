#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"
#include "../../src/data_structures/intersection/intersection.cpp"
#include "../../src/data_structures/intersections/intersections.cpp"
#include "../../src/data_structures/ray/ray.cpp"
#include "../../src/shapes/sphere/sphere.cpp"

using data_structures::intersection;
using data_structures::intersections;
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
