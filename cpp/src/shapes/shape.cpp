#include "./shape.h"
#include <cmath>

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
	{}

const material & shape::getMaterial() const { return _material; }
void shape::setMaterial(const material & material) { _material = material; }

const matrix & shape::getTransform() const { return _transform; }
void shape::setTransform(matrix && transform) { _transform = std::move(transform); }

data_structures::four_tuple shape::getNormalAtPoint(const data_structures::four_tuple & p) const
{
	auto inverseTranform = _transform.getInverse();
	auto localPoint = inverseTranform * p;

	auto localNormal = getLocalNormalAtLocalPoint(localPoint);
	auto worldNormalWithWrongW = inverseTranform.getTransposed() * localNormal;
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
