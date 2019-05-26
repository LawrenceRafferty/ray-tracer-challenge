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

four_tuple four_tuple::operator+(const four_tuple & other) const
{
	return four_tuple(
		_x + other._x,
		_y + other._y,
		_z + other._z,
		_w + other._w);
}

four_tuple four_tuple::operator-(const four_tuple & other) const
{
	return four_tuple(
		_x - other._x,
		_y - other._y,
		_z - other._z,
		_w - other._w);
}

four_tuple four_tuple::operator-() const
{
	return four_tuple(
		-_x,
		-_y,
		-_z,
		-_w);
}

four_tuple four_tuple::operator*(float scalar) const
{
	return four_tuple(
		_x * scalar,
		_y * scalar,
		_z * scalar,
		_w * scalar);
}

four_tuple four_tuple::operator/(float scalar) const
{
	return four_tuple(
		_x / scalar,
		_y / scalar,
		_z / scalar,
		_w / scalar);
}
} // namespace data_structures
