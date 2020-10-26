#include "./shape.h"
#include <cmath>

using data_structures::color;
using data_structures::four_tuple;
using data_structures::material;
using data_structures::matrix;
using data_structures::ray;

namespace shapes
{
shape::shape()
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
	, _inverseTransform { _transform.getInverse() }
	{}

const material & shape::getMaterial() const { return _material; }
void shape::setMaterial(const material & material) { _material = material; }

const matrix & shape::getTransform() const { return _transform; }
void shape::setTransform(matrix && transform)
{
	 _transform = std::move(transform);
	 _inverseTransform = _transform.getInverse();
}

four_tuple shape::getLocalPoint(const four_tuple & worldPoint) const
{
	return _inverseTransform * worldPoint;
}

color shape::getColorAtPoint(const four_tuple & worldPoint) const
{
	auto localPoint = getLocalPoint(worldPoint);
	return _material.getPattern().getColorOnObjectAtPoint(localPoint);
}

four_tuple shape::getNormalAtPoint(const four_tuple & worldPoint) const
{
	auto localPoint = getLocalPoint(worldPoint);
	auto localNormal = getLocalNormalAtLocalPoint(localPoint);
	auto worldNormalWithWrongW = _inverseTransform.getTransposed() * localNormal;
	auto worldNormal = four_tuple::vector(
		worldNormalWithWrongW.getX(),
		worldNormalWithWrongW.getY(),
		worldNormalWithWrongW.getZ());
	return worldNormal.getNormalized();
}

std::vector<float> shape::intersect(const ray & r) const
{
	auto localRay = getLocalRay(r);
	return localIntersect(localRay);
}

ray shape::getLocalRay(const ray & r) const
{
	return r.getTransformed(_transform.getInverse());
}

} // namespace shapes
