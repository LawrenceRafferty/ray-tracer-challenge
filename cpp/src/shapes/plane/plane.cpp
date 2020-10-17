#include "./plane.h"
#include <cmath>
#include <vector>
#include "../../data_structures/four_tuple/four_tuple.h"
#include "../../data_structures/ray/ray.h"
#include "../../float_utility.cpp"
#include "../shape.h"

using data_structures::four_tuple;
using data_structures::ray;

namespace shapes
{
	plane::plane() : shape() {}

	four_tuple plane::getLocalNormalAtLocalPoint_test(const four_tuple & localPoint) const
	{
		return getLocalNormalAtLocalPoint(localPoint);
	}

	four_tuple plane::getLocalNormalAtLocalPoint(const four_tuple & localPoint) const
	{
		// in local space this is an x-z plane, so the normal vector is constant
		return four_tuple::vector(0, 1, 0);
	}

	std::vector<float> plane::localIntersect_test(const ray & r) const
	{
		return localIntersect(r);
	}

	std::vector<float> plane::localIntersect(const ray & r) const
	{
		float rayDirectionY = r.getDirection().getY();
		if (float_utility::are_equivalent(rayDirectionY, 0))
			return std::vector<float>();

		float t = -r.getOrigin().getY() / rayDirectionY;
		return std::vector<float> { t };
	}
} // namespace shapes
