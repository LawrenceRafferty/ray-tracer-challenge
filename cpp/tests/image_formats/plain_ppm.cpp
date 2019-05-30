#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/canvas/canvas.h"
#include "../../src/image_formats/ppm/plain_ppm.cpp"

using data_structures::canvas;

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
