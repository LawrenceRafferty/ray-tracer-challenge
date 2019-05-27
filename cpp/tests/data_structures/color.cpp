#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/color/color.cpp"

using data_structures::color;

TEST_CASE("colors are (red, green, blue) tuples")
{
	auto c = color(-0.5f, 0.4f, 1.7f);
	REQUIRE(-0.5f == c.getRed());
	REQUIRE(0.4f == c.getGreen());
	REQUIRE(1.7f == c.getBlue());
}

TEST_CASE("color equality")
{
	auto c = color(0.9, 0.6, 0.75);
	REQUIRE(c == c);
}

TEST_CASE("color inequality")
{
	auto c1 = color(0.9, 0.6, 0.75);
	auto c2 = color(0.7, 0.1, 0.25);
	REQUIRE(c1 != c2);
}

TEST_CASE("adding colors")
{
	auto c1 = color(0.9, 0.6, 0.75);
	auto c2 = color(0.7, 0.1, 0.25);
	auto expected = color(1.6, 0.7, 1.0);
	REQUIRE(expected == c1 + c2);
}
