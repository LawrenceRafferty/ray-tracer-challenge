#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/color/color.cpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"
#include "../../src/data_structures/ray/ray.cpp"
#include "../../src/data_structures/material/material.cpp"
#include "../../src/data_structures/matrix/matrix.cpp"
#include "../../src/shapes/shape.cpp"
#include "../../src/shapes/test/test.cpp"

using data_structures::four_tuple;
using data_structures::material;
using data_structures::matrix;
using data_structures::ray;

TEST_CASE("the default material")
{
	auto s = shapes::test();
	auto m = s.getMaterial();
	REQUIRE(material() == m);
}

TEST_CASE("assigning a material")
{
	auto s = shapes::test();
	auto m = material();
	m.setAmbient(1.0f);
	s.setMaterial(m);
	REQUIRE(m == s.getMaterial());
}

TEST_CASE("intersecting a scaled shape with a ray")
{
	auto r = ray(four_tuple::point(0, 0, -5), four_tuple::vector(0, 0, 1));
	auto s = shapes::test();
	s.setTransform(matrix::scaling(2, 2, 2));
	auto xs = s.intersect(r);
	// to keep the intersect member const I chose to expose getLocalRay instead
	auto localRay = s.getLocalRay(r);
	REQUIRE(four_tuple::point(0, 0, -2.5) == localRay.getOrigin());
	REQUIRE(four_tuple::vector(0, 0, 0.5) == localRay.getDirection());
}

TEST_CASE("intersecting a translated shape with a ray")
{
	auto r = ray(four_tuple::point(0, 0, -5), four_tuple::vector(0, 0, 1));
	auto s = shapes::test();
	s.setTransform(matrix::translation(5, 0, 0));
	auto xs = s.intersect(r);
	// to keep the intersect member const I chose to expose getLocalRay instead
	auto localRay = s.getLocalRay(r);
	REQUIRE(four_tuple::point(-5, 0, -5) == localRay.getOrigin());
	REQUIRE(four_tuple::vector(0, 0, 1) == localRay.getDirection());
}

TEST_CASE("computing the normal on a translated shape")
{
	auto s = shapes::test();
	s.setTransform(matrix::translation(0, 1, 0));
	auto n = s.getNormalAtPoint(four_tuple::point(0, 1.70711, -0.70711));
	REQUIRE(four_tuple::vector(0, 0.70711, -0.70711) == n);
}

TEST_CASE("computing the normal on a transformed shape")
{
	auto s = shapes::test();
	auto m = matrix::scaling(1, 0.5, 1) * matrix::rotation_z(M_PI / 5);
	s.setTransform(std::move(m));
	auto n = s.getNormalAtPoint(four_tuple::point(0, M_SQRT2 / 2.0f, -M_SQRT2 / 2));
	REQUIRE(four_tuple::vector(0, 0.97014, -0.24254) == n);
}
