#include "./test.h"

using data_structures::four_tuple;
using data_structures::ray;

namespace shapes
{
test::test() : shape() {}


std::vector<float> test::localIntersect(const ray & localRay) const
{
	return std::vector<float>();
}

four_tuple test::getLocalNormalAtLocalPoint(const four_tuple & localPoint) const
{
	return four_tuple::vector(
		localPoint.getX(),
		localPoint.getY(),
		localPoint.getZ());
}

} // namespace shapes
