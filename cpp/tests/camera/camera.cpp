#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/camera/camera.cpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"
#include "../../src/data_structures/matrix/matrix.cpp"
#include "../../src/data_structures/ray/ray.cpp"

using data_structures::camera;
using data_structures::four_tuple;
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

TEST_CASE("constructing a ray through the center of the canvas")
{
	auto c = camera(201, 101, M_PI_2);
	auto r = c.getRayForPixel(100, 50);
	REQUIRE(r.getOrigin() == four_tuple::point(0, 0, 0));
	REQUIRE(r.getDirection() == four_tuple::vector(0, 0, -1));
}

TEST_CASE("constructing a ray through a corner of the canvas")
{
	auto c = camera(201, 101, M_PI_2);
	auto r = c.getRayForPixel(0, 0);
	REQUIRE(r.getOrigin() == four_tuple::point(0, 0, 0));
	REQUIRE(r.getDirection() == four_tuple::vector(0.66519, 0.33259, -0.66851));
}

TEST_CASE("constructing a ray when the camera is transformed")
{
	auto c = camera(201, 101, M_PI_2, matrix::translation(0, -2, 5));
	auto r = c.getRayForPixel(100, 50);
	REQUIRE(r.getOrigin() == four_tuple::point(0, 2, -5));
	REQUIRE(r.getDirection() == four_tuple::vector(M_SQRT2 / 2, 0, -M_SQRT2 / 2));
}
