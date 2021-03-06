#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/color/color.cpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"
#include "../../src/data_structures/material/material.cpp"
#include "../../src/data_structures/matrix/matrix.cpp"
#include "../../src/lights/point_light/point_light.cpp"
#include "../../src/lights/lighting.cpp"
#include "../../src/patterns/pattern.cpp"
#include "../../src/patterns/solid/solid.cpp"
#include "../../src/patterns/stripe/stripe.cpp"

using data_structures::color;
using data_structures::four_tuple;
using data_structures::material;
using lights::point_light;
using lights::lighting;
using patterns::solid;
using patterns::stripe;

TEST_CASE("the default material")
{
	auto m = material();
	REQUIRE(color(1, 1, 1) == m.getPattern().getColorAtPoint(four_tuple::point(0, 0, 0)));
	REQUIRE(0.1f == m.getAmbient());
	REQUIRE(0.9f == m.getDiffuse());
	REQUIRE(0.9f == m.getSpecular());
	REQUIRE(200.0f == m.getShininess());
}

TEST_CASE("lighting with the eye between the light and the surface")
{
	auto m = material();
	auto position = four_tuple::point(0, 0, 0);
	auto eyev = four_tuple::vector(0, 0, -1);
	auto normalv = four_tuple::vector(0, 0, -1);
	auto light = point_light(four_tuple::point(0, 0, -10), color(1, 1, 1));
	auto isInShadow = false;
	REQUIRE(color(1.9, 1.9, 1.9) == lighting(m, light, position, eyev, normalv, isInShadow));
}

TEST_CASE("lighting with the surface in shadow")
{
	auto m = material();
	auto position = four_tuple::point(0, 0, 0);
	auto eyev = four_tuple::vector(0, 0, -1);
	auto normalv = four_tuple::vector(0, 0, -1);
	auto light = point_light(four_tuple::point(0, 0, -10), color(1, 1, 1));
	auto isInShadow = true;
	REQUIRE(color(0.1, 0.1, 0.1) == lighting(m, light, position, eyev, normalv, isInShadow));
}

TEST_CASE("lighting with the eye between light and surface, eye offset 45°")
{
	auto m = material();
	auto position = four_tuple::point(0, 0, 0);
	auto sqrt2Over2 = sqrt(2) / 2.0;
	auto eyev = four_tuple::vector(0, sqrt2Over2, -sqrt2Over2);
	auto normalv = four_tuple::vector(0, 0, -1);
	auto light = point_light(four_tuple::point(0, 0, -10), color(1, 1, 1));
	auto isInShadow = false;
	REQUIRE(color(1.0, 1.0, 1.0) == lighting(m, light, position, eyev, normalv, isInShadow));
}

TEST_CASE("lighting with the eye opposite surface, light offset 45°")
{
	auto m = material();
	auto position = four_tuple::point(0, 0, 0);
	auto eyev = four_tuple::vector(0, 0, -1);
	auto normalv = four_tuple::vector(0, 0, -1);
	auto light = point_light(four_tuple::point(0, 10, -10), color(1, 1, 1));
	auto isInShadow = false;
	REQUIRE(color(0.7364, 0.7364, 0.7364) == lighting(m, light, position, eyev, normalv, isInShadow));
}

TEST_CASE("lighting with the eye in the path of the reflection vector")
{
	auto m = material();
	auto position = four_tuple::point(0, 0, 0);
	auto sqrt2Over2 = sqrt(2) / 2.0;
	auto eyev = four_tuple::vector(0, -sqrt2Over2, -sqrt2Over2);
	auto normalv = four_tuple::vector(0, 0, -1);
	auto light = point_light(four_tuple::point(0, 10, -10), color(1, 1, 1));
	auto isInShadow = false;
	auto actual = lighting(m, light, position, eyev, normalv, isInShadow);
	REQUIRE(color(1.63638, 1.63638, 1.63638) == actual);
}

TEST_CASE("lighting with the light behind the surface")
{
	auto m = material();
	auto position = four_tuple::point(0, 0, 0);
	auto eyev = four_tuple::vector(0, 0, -1);
	auto normalv = four_tuple::vector(0, 0, -1);
	auto light = point_light(four_tuple::point(0, 0, 10), color(1, 1, 1));
	auto isInShadow = false;
	REQUIRE(color(0.1, 0.1, 0.1) == lighting(m, light, position, eyev, normalv, isInShadow));
}

TEST_CASE("lighting with a pattern applied")
{
	auto m= material();
	m.setPattern(std::make_shared<stripe>(std::initializer_list<std::shared_ptr<pattern>>
	{
		std::make_shared<solid>(color(1, 1, 1)),
		std::make_shared<solid>(color(0, 0, 0))
	}));
	m.setAmbient(1);
	m.setDiffuse(0);
	m.setSpecular(0);
	auto eyeVector = four_tuple::vector(0, 0, -1);
	auto normalVector = four_tuple::vector(0, 0, -1);
	auto light = point_light(four_tuple::point(0, 0, -10), color(1, 1, 1));
	auto c1 = lighting(m, light, four_tuple::point(0.9, 0, 0), eyeVector, normalVector, false);
	auto c2 = lighting(m, light, four_tuple::point(1.1, 0, 0), eyeVector, normalVector, false);
	REQUIRE(color(1, 1, 1) == c1);
	REQUIRE(color(0, 0, 0) == c2);
}
