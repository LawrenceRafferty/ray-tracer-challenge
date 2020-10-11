#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/color/color.cpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"
#include "../../src/data_structures/intersection/intersection.cpp"
#include "../../src/data_structures/intersection_computations/intersection_computations.cpp"
#include "../../src/data_structures/intersections/intersections.cpp"
#include "../../src/data_structures/material/material.cpp"
#include "../../src/data_structures/matrix/matrix.cpp"
#include "../../src/data_structures/ray/ray.cpp"
#include "../../src/data_structures/world/world.cpp"
#include "../../src/lights/lighting.cpp"
#include "../../src/lights/point_light/point_light.cpp"
#include "../../src/shapes/sphere/sphere.cpp"
#include "./default_world.cpp"

using data_structures::color;
using data_structures::four_tuple;
using data_structures::intersection_computations;
using data_structures::intersections;
using data_structures::material;
using data_structures::world;
using lights::point_light;

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
	auto defaultWorld = default_world::getDefaultWorld();
	auto light = default_world::getDefaultWorldLight();
	auto s1 = default_world::getDefaultWorldSphere1();
	auto s2 = default_world::getDefaultWorldSphere2();
	REQUIRE(true == worldContainsLight(defaultWorld, light));
	REQUIRE(true == worldContainsObject(defaultWorld, s1));
	REQUIRE(true == worldContainsObject(defaultWorld, s2));
}

TEST_CASE("intersect a world with a ray")
{
	auto w = default_world::getDefaultWorld();
	auto r = ray(four_tuple::point(0, 0, -5), four_tuple::vector(0, 0, 1));
	auto xs = intersections::find(w, r);
	REQUIRE(4 == xs.size());
	REQUIRE(4 == xs.at(0).getT());
	REQUIRE(4.5 == xs.at(1).getT());
	REQUIRE(5.5 == xs.at(2).getT());
	REQUIRE(6 == xs.at(3).getT());
}

TEST_CASE("shading an intersection")
{
	auto w = default_world::getDefaultWorld();
	auto r = ray(four_tuple::point(0, 0, -5), four_tuple::vector(0, 0, 1));
	auto shape = w.getObjects().at(0);
	auto i = intersection(4, shape);
	auto computations = intersection_computations::prepare(i, r);
	auto c = w.shadeHit(computations);
	REQUIRE(color(0.38066f, 0.47583f, 0.2855f) == c);
}

TEST_CASE("shading an intersection from the inside")
{
	auto w = world();
	w.addLight(point_light(four_tuple::point(0, 0.25, 0), color(1, 1, 1)));
	w.addObject(default_world::getDefaultWorldSphere1());
	w.addObject(default_world::getDefaultWorldSphere2());
	auto r = ray(four_tuple::point(0, 0, 0), four_tuple::vector(0, 0, 1));
	auto shape = w.getObjects().at(1);
	auto i = intersection(0.5, shape);
	auto computations = intersection_computations::prepare(i, r);
	auto c = w.shadeHit(computations);
	REQUIRE(color(0.90498f, 0.90498f, 0.90498f) == c);
}

TEST_CASE("the color when a ray misses")
{
	auto w = default_world::getDefaultWorld();
	auto r = ray(four_tuple::point(0, 0, -5), four_tuple::vector(0, 1, 0));
	auto c = w.getColorAt(r);
	REQUIRE(color() == c);
}

TEST_CASE("the color when a ray hits")
{
	auto w = default_world::getDefaultWorld();
	auto r = ray(four_tuple::point(0, 0, -5), four_tuple::vector(0, 0, 1));
	auto c = w.getColorAt(r);
	REQUIRE(color(0.38066f, 0.47583f, 0.2855f) == c);
}

TEST_CASE("the color with an intersection behind the ray")
{
	auto w = default_world::getDefaultWorld();
	auto outer = w.getObjects().at(0);
	auto outerMaterial = material(outer->getMaterial());
	outerMaterial.setAmbient(1);
	outer->setMaterial(outerMaterial);
	auto inner = w.getObjects().at(1);
	auto innerMaterial = material(inner->getMaterial());
	innerMaterial.setAmbient(1);
	inner->setMaterial(innerMaterial);
	auto r = ray(four_tuple::point(0, 0, 0.75), four_tuple::vector(0, 0, -1));
	auto c = w.getColorAt(r);
	auto expected = innerMaterial.getColor();
	REQUIRE(expected == c);
}
