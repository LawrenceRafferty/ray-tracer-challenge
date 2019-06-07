#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/color/color.cpp"
#include "../../src/data_structures/material/material.cpp"

using data_structures::color;
using data_structures::material;

TEST_CASE("the default material")
{
	auto m = material();
	REQUIRE(color(1, 1, 1) == m.getColor());
	REQUIRE(0.1f == m.getAmbient());
	REQUIRE(0.9f == m.getDiffuse());
	REQUIRE(0.9f == m.getSpecular());
	REQUIRE(200.0f == m.getShininess());
}
