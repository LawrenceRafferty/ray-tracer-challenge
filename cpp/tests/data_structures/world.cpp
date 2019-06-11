#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/color/color.cpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"
#include "../../src/data_structures/material/material.cpp"
#include "../../src/data_structures/matrix/matrix.cpp"
#include "../../src/data_structures/ray/ray.cpp"
#include "../../src/data_structures/world/world.cpp"
#include "../../src/lights/point_light/point_light.cpp"
#include "../../src/shapes/sphere/sphere.cpp"

using data_structures::world;

TEST_CASE("creating a world")
{
	auto w = world();
	REQUIRE(0 == w.getObjects().size());
	REQUIRE(0 == w.getLights().size());
}
