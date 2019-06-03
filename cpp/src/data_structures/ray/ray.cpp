#include "./ray.h"

namespace data_structures
{
	ray::ray(four_tuple origin, four_tuple direction)
		: _origin { origin }
		, _direction { direction }
		{}

	four_tuple ray::getOrigin() const { return _origin; }

	four_tuple ray::getDirection() const { return _direction; }
}
