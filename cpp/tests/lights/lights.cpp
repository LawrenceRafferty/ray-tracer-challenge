#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/color/color.cpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"
#include "../../src/lights/point_light/point_light.cpp"

using data_structures::color;
using data_structures::four_tuple;
using lights::point_light;

TEST_CASE("a point light has a position and intensity")
{
	auto position = four_tuple::point(0, 0, 0);
	auto intensity = color(1, 1, 1);
	auto light = point_light(position, intensity);
	REQUIRE(position == light.getPosition());
	REQUIRE(intensity == light.getIntensity());
}
