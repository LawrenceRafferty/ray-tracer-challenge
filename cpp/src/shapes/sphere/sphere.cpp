#include "./sphere.h"
#include <cmath>

using data_structures::four_tuple;
using data_structures::ray;

namespace shapes
{
sphere::sphere() : shape() {}

std::vector<float> sphere::localIntersect(const ray & localRay) const
{
	// ASSUME: the sphere is centered at the world origin
	auto vectorFromSphereCenterToRayOrigin = localRay.getOrigin() - four_tuple::point(0, 0, 0);
	auto rayDirection = localRay.getDirection();
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
	return std::vector<float>{t1, t2};
}

four_tuple sphere::getLocalNormalAtLocalPoint(const four_tuple & localPoint) const
{
	// ASSUME: already normalized because this is a unit sphere centered at the origin
	return localPoint - four_tuple::point(0, 0, 0);
}

bool sphere::operator==(const sphere & other) const
{
	return getMaterial() == other.getMaterial() &&
		getTransform() == other.getTransform();
}

bool sphere::operator!=(const sphere & other) const
{
	return !(*this == other);
}

} // namespace shapes
