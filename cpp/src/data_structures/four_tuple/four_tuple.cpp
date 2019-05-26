#include "four_tuple.h"
#include <cmath>

namespace data_structures
{
constexpr float EPSILON = 0.00001f;

bool are_equivalent(float left, float right)
{
	return abs(left - right) < EPSILON;
}

bool four_tuple::operator==(const four_tuple & other) const
{
	return are_equivalent(_x, other._x) &&
		are_equivalent(_y, other._y) &&
		are_equivalent(_z, other._z) &&
		_w == other._w;
}

bool four_tuple::operator!=(const four_tuple & other) const
{
	return !(*this == other);
}
} // namespace data_structures
