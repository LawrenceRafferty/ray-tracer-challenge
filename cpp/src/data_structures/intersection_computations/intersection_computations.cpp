#include "./intersection_computations.h"

using data_structures::intersection;
using data_structures::ray;
using shapes::sphere;

namespace data_structures
{
	intersection_computations::intersection_computations(
		float t,
		std::shared_ptr<const sphere> object,
		const four_tuple & point,
		const four_tuple & eyeVector,
		const four_tuple & normalVector)
		: _t { t }
		, _object { object }
		, _point { point }
		, _eyeVector { eyeVector }
		, _normalVector { normalVector }
		{}

	const intersection_computations & intersection_computations::prepare(const intersection & i, const ray & r)
	{
		float t = i.getT();
		auto object = i.getObject();
		auto point = r.getPositionAt(t);
		auto eyeVector = -r.getDirection();
		auto normalVector = object->getNormalAtPoint(point);
		return std::move(intersection_computations(
			t,
			object,
			point,
			eyeVector,
			normalVector
		));
	}

	float intersection_computations::getT() const { return _t; }

	std::shared_ptr<const shapes::sphere> intersection_computations::getObject() const { return _object; }

	const four_tuple & intersection_computations::getPoint() const { return _point; }

	const four_tuple & intersection_computations::getEyeVector() const { return _eyeVector; }

	const four_tuple & intersection_computations::getNormalVector() const { return _normalVector; }
}
