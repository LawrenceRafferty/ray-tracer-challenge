#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/color/color.cpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"
#include "../../src/data_structures/intersection/intersection.cpp"
#include "../../src/data_structures/intersections/intersections.cpp"
#include "../../src/data_structures/material/material.cpp"
#include "../../src/data_structures/matrix/matrix.cpp"
#include "../../src/data_structures/ray/ray.cpp"
#include "../../src/data_structures/world/world.cpp"
#include "../../src/lights/point_light/point_light.cpp"
#include "../../src/shapes/sphere/sphere.cpp"

using data_structures::color;
using data_structures::four_tuple;
using data_structures::intersections;
using data_structures::material;
using data_structures::world;
using lights::point_light;

point_light getDefaultWorldLight()
{
	return std::move(point_light(four_tuple::point(-10, 10, -10), color(1, 1, 1)));
}

std::shared_ptr<sphere> getDefaultWorldSphere1()
{
	auto s1 = std::make_shared<sphere>();
	auto m = material();
	m.setColor(color(0.8, 1.0, 0.6));
	m.setDiffuse(0.7);
	m.setSpecular(0.2);
	s1->setMaterial(m);
	return s1;
}

std::shared_ptr<sphere> getDefaultWorldSphere2()
{
	auto s2 = std::make_shared<sphere>();
	s2->setTransform(matrix::scaling(0.5, 0.5, 0.5));
	return s2;
}

world getDefaultWorld()
{
	auto defaultWorld = world();
	defaultWorld.addLight(getDefaultWorldLight());
	defaultWorld.addObject(getDefaultWorldSphere1());
	defaultWorld.addObject(getDefaultWorldSphere2());
	return std::move(defaultWorld);
}

bool worldContainsLight(const world & w, const point_light & l)
{
	auto lights = w.getLights();
	return std::any_of(lights.begin(), lights.end(), [l](const point_light & candidate) { return candidate == l; });
}

bool worldContainsObject(const world & w, std::shared_ptr<sphere> o)
{
	auto objects = w.getObjects();
	return std::any_of(objects.begin(), objects.end(), [o](std::shared_ptr<sphere> candidate) { return *candidate == *o; });
}

TEST_CASE("creating a world")
{
	auto w = world();
	REQUIRE(0 == w.getObjects().size());
	REQUIRE(0 == w.getLights().size());
}

TEST_CASE("the default world")
{
	auto defaultWorld = getDefaultWorld();
	auto light = getDefaultWorldLight();
	auto s1 = getDefaultWorldSphere1();
	auto s2 = getDefaultWorldSphere2();
	REQUIRE(true == worldContainsLight(defaultWorld, light));
	REQUIRE(true == worldContainsObject(defaultWorld, s1));
	REQUIRE(true == worldContainsObject(defaultWorld, s2));
}

TEST_CASE("intersect a world with a ray")
{
	auto w = getDefaultWorld();
	auto r = ray(four_tuple::point(0, 0, -5), four_tuple::vector(0, 0, 1));
	auto xs = intersections::find(w, r);
	REQUIRE(4 == xs.size());
	REQUIRE(4 == xs.at(0).getT());
	REQUIRE(4.5 == xs.at(1).getT());
	REQUIRE(5.5 == xs.at(2).getT());
	REQUIRE(6 == xs.at(3).getT());
}
