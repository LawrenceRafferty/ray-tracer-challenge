#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/camera/camera.cpp"
#include "../../src/data_structures/matrix/matrix.cpp"

using data_structures::camera;
using data_structures::matrix;

TEST_CASE("constructing a camera")
{
	auto hsize = 160;
	auto vsize = 120;
	auto fieldOfView = M_PI_2;
	auto c = camera(hsize, vsize, fieldOfView);
	REQUIRE(c.getHsize() == 160);
	REQUIRE(c.getVsize() == 120);
	REQUIRE(c.getFieldOfView() == M_PI_2);
	auto identityMatrix = matrix
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	REQUIRE(c.getTransform() == identityMatrix);
}

TEST_CASE("the pixel size for a horizontal canvas")
{
	auto c = camera(200, 125, M_PI_2);
	REQUIRE(c.getPixelSize() == 0.01);
}

TEST_CASE("the pixel size for a vertical canvas")
{
	auto c = camera(125, 200, M_PI_2);
	REQUIRE(c.getPixelSize() == 0.01); 
}
