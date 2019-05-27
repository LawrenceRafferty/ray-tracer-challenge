#include "four_tuple.h"
#include <cmath>
#include "../float_utility/float_utility.cpp"

namespace data_structures
{
float four_tuple::dot(const four_tuple & other) const
{
	return _x * other._x +
		_y * other._y +
		_z * other._z +
		_w * other._w;
}

four_tuple four_tuple::cross(const four_tuple & other) const
{
	// ASSUME: operating on vectors (w == 0)
	return vector(
		_y * other._z - _z * other._y,
		_z * other._x - _x * other._z,
		_x * other._y - _y * other._x);
}

bool four_tuple::operator==(const four_tuple & other) const
{
	return float_utility::are_equivalent(_x, other._x) &&
		float_utility::are_equivalent(_y, other._y) &&
		float_utility::are_equivalent(_z, other._z) &&
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

float four_tuple::getMagnitude() const
{
	return sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2) + pow(_w, 2));
}

four_tuple four_tuple::getNormalized() const
{
	auto magnitude = getMagnitude();
	return *this / magnitude;
}
} // namespace data_structures
