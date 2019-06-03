#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"
#include "../../src/data_structures/intersection/intersection.cpp"
#include "../../src/data_structures/ray/ray.cpp"
#include "../../src/shapes/sphere/sphere.cpp"

using data_structures::intersection;
using shapes::sphere;

TEST_CASE("an intersection encapsulates t and object")
{
	auto s = std::make_shared<sphere>();
	auto i = intersection(3.5, s);
	REQUIRE(3.5 == i.getT());
	REQUIRE(s == i.getObject());
}
