#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/color/color.h"

using data_structures::color;

TEST_CASE("colors are (red, green, blue) tuples")
{
	auto c = color(-0.5f, 0.4f, 1.7f);
	REQUIRE(-0.5f == c.getRed());
	REQUIRE(0.4f == c.getGreen());
	REQUIRE(1.7f == c.getBlue());
}
