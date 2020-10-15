#include "./ray.h"

using data_structures::matrix;

namespace data_structures
{
	ray::ray(four_tuple origin, four_tuple direction)
		: _origin { std::move(origin) }
		, _direction { std::move(direction) }
		{}

	const four_tuple & ray::getOrigin() const { return _origin; }

	const four_tuple & ray::getDirection() const { return _direction; }

	four_tuple ray::getPositionAt(float t) const {
		return std::move(_origin + _direction * t);
	}

	ray ray::getTransformed(const matrix & transformation) const
	{
		auto transformedOrigin = transformation * _origin;
		auto transformedDirection = transformation * _direction;
		return std::move(ray(transformedOrigin, transformedDirection));
	}
}
