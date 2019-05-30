#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/canvas/canvas.h"
#include "../../src/data_structures/color/color.cpp"

using data_structures::canvas;
using data_structures::color;

TEST_CASE("creating a canvas")
{
	int width = 10;
	int height = 20;
	auto c = canvas(width, height);
	REQUIRE(width == c.getWidth());
	REQUIRE(height == c.getHeight());
}

TEST_CASE("every pixel in a new canvas is black")
{
	int width = 2;
	int height = 2;
	auto c = canvas(width, height);
	auto black = color(0, 0, 0);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
			REQUIRE(black == c.getPixelAt(x, y));
	}
}
