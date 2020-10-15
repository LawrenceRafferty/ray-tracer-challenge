#include "./intersection_computations.h"

using data_structures::intersection;
using data_structures::ray;
using shapes::sphere;

namespace data_structures
{
	intersection_computations::intersection_computations(
		float t,
		std::shared_ptr<const sphere> object,
		four_tuple point,
		four_tuple eyeVector,
		four_tuple normalVector,
		bool isInside)
		: _t { t }
		, _object { object }
		, _point { std::move(point) }
		, _eyeVector { std::move(eyeVector) }
		, _normalVector { std::move(normalVector) }
		, _isInside { isInside }
		{}

	intersection_computations intersection_computations::prepare(const intersection & i, const ray & r)
	{
		float t = i.getT();
		auto object = i.getObject();
		auto point = r.getPositionAt(t);
		auto eyeVector = -r.getDirection();
		auto normalVector = object->getNormalAtPoint(point);
		auto isInside = normalVector.dot(eyeVector) < 0;
		return std::move(intersection_computations(
			t,
			object,
			point,
			eyeVector,
			isInside ? -normalVector : normalVector,
			isInside
		));
	}

	float intersection_computations::getT() const { return _t; }

	std::shared_ptr<const shapes::sphere> intersection_computations::getObject() const { return _object; }

	const four_tuple & intersection_computations::getPoint() const { return _point; }

	const four_tuple & intersection_computations::getEyeVector() const { return _eyeVector; }

	const four_tuple & intersection_computations::getNormalVector() const { return _normalVector; }

	bool intersection_computations::getIsInside() const { return _isInside; }
}
