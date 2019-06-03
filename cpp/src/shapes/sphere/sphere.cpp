#include "./sphere.h"
#include <cmath>
#include"../../data_structures/ray/ray.h"

using data_structures::four_tuple;
using data_structures::ray;

namespace shapes
{
	sphere::sphere() {}

	std::vector<float> sphere::intersect(const ray & r) const
	{
		// ASSUME: the sphere is centered at the world origin
		auto vectorFromSphereCenterToRayOrigin = r.getOrigin() - four_tuple::point(0, 0, 0);
		auto rayDirection = r.getDirection();
		float a = rayDirection.dot(rayDirection);
		float b = 2 * rayDirection.dot(vectorFromSphereCenterToRayOrigin);
		float c = vectorFromSphereCenterToRayOrigin.dot(vectorFromSphereCenterToRayOrigin) - 1;
		float discriminant = pow(b, 2) - 4 * a * c;
		if (discriminant < 0)
			return std::vector<float>();
		
		float squareRootOfDiscriminant = sqrt(discriminant);
		float two_a = 2 * a;
		float t1 = (-b - squareRootOfDiscriminant) / two_a;
		float t2 = (-b + squareRootOfDiscriminant) / two_a;
		return std::vector<float> { t1, t2 };
	}
}
