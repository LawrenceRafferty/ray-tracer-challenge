#include "./matrix.h"
#include <cmath>
#include "../float_utility.cpp"

namespace data_structures
{
matrix::matrix(int dimension)
	: _dimension { dimension }
	, _data { std::vector<float>(dimension * dimension) }
	{}

matrix::matrix(std::initializer_list<float> elements)
	: _dimension { static_cast<int>(std::round(sqrt(elements.size()))) }
	, _data{std::vector<float>(elements) }
	{}

bool matrix::operator==(const matrix & other) const
{
	return _dimension == other._dimension &&
		std::equal(
			_data.begin(), _data.end(),
			other._data.begin(),
			float_utility::are_equivalent);
}

bool matrix::operator!=(const matrix & other) const
{
	return !(*this == other);
}

float matrix::getElementAt(int row, int column) const
{
	return _data[column + (_dimension * row)];
}
} // namespace data_structures
