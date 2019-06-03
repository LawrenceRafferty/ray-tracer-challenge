#define CATCH_CONFIG_MAIN
#include "../framework/catch.hpp"
#include "../../src/data_structures/four_tuple/four_tuple.cpp"
#include "../../src/data_structures/ray/ray.cpp"

using data_structures::four_tuple;
using data_structures::ray;

TEST_CASE("creating and querying a ray")
{
	auto origin = four_tuple::point(1, 2, 3);
	auto direction = four_tuple::vector(4, 5, 6);
	auto r = ray(origin, direction);
	REQUIRE(origin == r.getOrigin());
	REQUIRE(direction == r.getDirection());
}
