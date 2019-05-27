#include "color.h"
#include "../float_utility/float_utility.cpp"

namespace data_structures
{
bool color::operator==(const color & other) const
{
	return float_utility::are_equivalent(_red, other._red) &&
		float_utility::are_equivalent(_green, other._green) &&
		float_utility::are_equivalent(_blue, other._blue);
}

bool color::operator!=(const color & other) const
{
	return !(*this == other);
}

color color::operator+(const color & other) const
{
	return color(
		_red + other._red,
		_green + other._green,
		_blue + other._blue);
}

color color::operator-(const color & other) const
{
	return color(
		_red - other._red,
		_green - other._green,
		_blue - other._blue);
}

color color::operator*(float scalar) const
{
	return color(
		_red * scalar,
		_green * scalar,
		_blue * scalar);
}

color color::operator*(const color & other) const
{
	return color(
		_red * other._red,
		_green * other._green,
		_blue * other._blue);
}
} // namespace data_structures
