#include "./sphere.h"
#include <cmath>

using data_structures::four_tuple;
using data_structures::material;
using data_structures::matrix;
using data_structures::ray;

namespace shapes
{
sphere::sphere()
	: _material { material() }
	, _transform
	{
		matrix
		{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		}
	}
	{}

const material & sphere::getMaterial() const { return _material; }

const matrix & sphere::getTransform() const { return _transform; }

void sphere::setTransform(const matrix & transform)
{
	_transform = transform;
}

std::vector<float> doIntersect(const ray & r)
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
	return std::vector<float>{t1, t2};
}

data_structures::four_tuple sphere::getNormalAtPoint(const data_structures::four_tuple & p) const
{
	auto inverseTranform = _transform.getInverse();
	auto objectPoint = inverseTranform * p;

	// ASSUME: objectNormal is already normalized because this is a unit sphere centered at the origin
	auto objectNormal = (objectPoint - four_tuple::point(0, 0, 0));
	auto worldNormalWithWrongW = inverseTranform.getTransposed() * objectNormal;
	auto worldNormal = four_tuple::vector(
		worldNormalWithWrongW.getX(),
		worldNormalWithWrongW.getY(),
		worldNormalWithWrongW.getZ());
	return worldNormal.getNormalized();
}

std::vector<float> sphere::intersect(const ray & r) const
{
	auto transformed = r.getTransformed(_transform.getInverse());
	return std::move(doIntersect(transformed));
}

} // namespace shapes
