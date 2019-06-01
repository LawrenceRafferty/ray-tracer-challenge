#include "./matrix.h"
#include <cmath>
#include <stdexcept>
#include "../float_utility.cpp"

namespace data_structures
{
matrix::matrix(int dimension)
	: _rows { dimension }
	, _columns { dimension }
	, _data { std::vector<float>(dimension * dimension) }
	{}

matrix::matrix(int rows, int columns)
	: _rows { rows }
	, _columns { columns }
	, _data { std::vector<float>(rows * columns) }
	{}

matrix::matrix(std::initializer_list<float> elements)
	:  _data{std::vector<float>(elements) }
	{
		_rows = _columns = static_cast<int>(std::round(sqrt(elements.size())));
		if (_rows * _columns != elements.size())
			throw std::invalid_argument("Must provide exactly enough elements to fill a square matrix.");
	}

matrix::matrix(int rows, int columns, std::initializer_list<float> elements)
	: _rows { rows }
	, _columns { columns }
	, _data{std::vector<float>(elements) }
	{
		if (rows * columns != elements.size())
			throw std::invalid_argument("Must provide exactly enough elements to fill the specified rows and columns.");
	}

bool matrix::operator==(const matrix & other) const
{
	return _rows == other._rows &&
		_columns == other._columns &&
		std::equal(
			_data.begin(), _data.end(),
			other._data.begin(),
			float_utility::are_equivalent);
}

bool matrix::operator!=(const matrix & other) const
{
	return !(*this == other);
}

matrix matrix::operator*(const matrix & other) const
{
	if (_columns != other._rows)
		throw std::invalid_argument("Other matrix must have the same number of rows as this matrix has columns.");

	auto sharedDimension = _columns;
	auto rows = _rows;
	auto columns = other._columns;

	auto m = matrix(rows, columns);

	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			auto element = 0;
			for (int index = 0; index < sharedDimension; index++)
				element += getElementAt(row, index) * other.getElementAt(index, column);

			m.setElementAt(row, column, element);
		}
	}

	return m;
}

float matrix::getElementAt(int row, int column) const
{
	return _data[getElementIndex(row, column)];
}

void matrix::setElementAt(int row, int column, float element)
{
	_data[getElementIndex(row, column)] = element;
}

int matrix::getElementIndex(int row, int column) const
{
	return column + (_columns * row);
}
} // namespace data_structures
