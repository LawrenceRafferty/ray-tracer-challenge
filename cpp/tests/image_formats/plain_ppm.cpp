#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/canvas/canvas.h"
#include "../../src/data_structures/color/color.cpp"
#include "../../src/image_formats/ppm/plain_ppm.cpp"

using data_structures::canvas;
using data_structures::color;

TEST_CASE("constructing the PPM header")
{
	auto c = canvas(5, 3);
	auto ppm = image_formats::plain_ppm::write(c);
	auto ppmStream = std::stringstream(ppm);
	std::string lineString;
	std::getline(ppmStream, lineString);
	REQUIRE("P3" == lineString);
	std::getline(ppmStream, lineString);
	REQUIRE("5 3" == lineString);
	std::getline(ppmStream, lineString);
	REQUIRE("255" == lineString);
}

TEST_CASE("constructing the PPM pixel data")
{
	auto c = canvas(5, 3);
	auto c1 = color(1.5, 0, 0);
	auto c2 = color(0, 0.5, 0);
	auto c3 = color(-0.5, 0, 1);
	c.setPixelAt(0, 0, c1);
	c.setPixelAt(2, 1, c2);
	c.setPixelAt(4, 2, c3);
	auto ppm = image_formats::plain_ppm::write(c);
	auto ppmStream = std::stringstream(ppm);
	std::string lineString;
	std::getline(ppmStream, lineString);
	std::getline(ppmStream, lineString);
	std::getline(ppmStream, lineString);
	std::getline(ppmStream, lineString);
	REQUIRE("255 0 0 0 0 0 0 0 0 0 0 0 0 0 0" == lineString);
	std::getline(ppmStream, lineString);
	REQUIRE("0 0 0 0 0 0 0 128 0 0 0 0 0 0 0" == lineString);
	std::getline(ppmStream, lineString);
	REQUIRE("0 0 0 0 0 0 0 0 0 0 0 0 0 0 255" == lineString);
}

TEST_CASE("splitting long lines in PPM files")
{
	int width = 10;
	int height = 2;
	auto c = canvas(width, height);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
			c.setPixelAt(x, y, color(1, 0.8, 0.6));
	}
	auto ppm = image_formats::plain_ppm::write(c);
	auto ppmStream = std::stringstream(ppm);
	std::string lineString;
	std::getline(ppmStream, lineString);
	std::getline(ppmStream, lineString);
	std::getline(ppmStream, lineString);
	std::getline(ppmStream, lineString);
	REQUIRE("255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204" == lineString);
	std::getline(ppmStream, lineString);
	REQUIRE("153 255 204 153 255 204 153 255 204 153 255 204 153" == lineString);
	std::getline(ppmStream, lineString);
	REQUIRE("255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204" == lineString);
	std::getline(ppmStream, lineString);
	REQUIRE("153 255 204 153 255 204 153 255 204 153 255 204 153" == lineString);
}

TEST_CASE("ppm files are terminated by a newline character")
{
	auto c = canvas(5, 3);
	auto ppm = image_formats::plain_ppm::write(c);
	REQUIRE('\n' == ppm[ppm.length() - 1]);
}
