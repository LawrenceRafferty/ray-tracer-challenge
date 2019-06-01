#include "./matrix.h"
#include <cmath>

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

float matrix::getElementAt(int row, int column) const
{
	return _data[column + (_dimension * row)];
}
} // namespace data_structures
