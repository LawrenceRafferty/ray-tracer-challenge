#include "./matrix.h"
#include <cmath>
#include <stdexcept>
#include "../float_utility.cpp"

namespace data_structures
{
matrix::matrix(int dimension)
	: _rows { dimension }
	, _columns { dimension }
	, _elements { std::vector<float>(dimension * dimension) }
	{}

matrix::matrix(int rows, int columns)
	: _rows { rows }
	, _columns { columns }
	, _elements { std::vector<float>(rows * columns) }
	{}

matrix::matrix(std::initializer_list<float> elements)
	:  _elements{std::vector<float>(elements) }
	{
		_rows = _columns = static_cast<int>(std::round(sqrt(elements.size())));
		if (_rows * _columns != elements.size())
			throw std::invalid_argument("Must provide exactly enough elements to fill a square matrix.");
	}

matrix::matrix(int rows, int columns, std::initializer_list<float> elements)
	: _rows { rows }
	, _columns { columns }
	, _elements{std::vector<float>(elements) }
	{
		if (rows * columns != elements.size())
			throw std::invalid_argument("Must provide exactly enough elements to fill the specified rows and columns.");
	}

matrix::matrix(matrix && other)
	: _rows { other._rows }
	, _columns { other._columns }
	, _elements { std::move(other._elements) }
	{}

matrix& matrix::operator=(matrix && other)
{
	if (this != &other)
	{
		_rows = other._rows;
		_columns = other._columns;
		_elements = std::move(other._elements);
	}

	return *this;
}

bool matrix::operator==(const matrix & other) const
{
	return _rows == other._rows &&
		_columns == other._columns &&
		std::equal(
			_elements.begin(), _elements.end(),
			other._elements.begin(),
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

	return std::move(m);
}

four_tuple matrix::operator*(const four_tuple & t) const
{
	if (_columns != 4)
		throw std::invalid_argument("This matrix must have four columns to multiply it with a four tuple.");

	auto m = matrix(4, 1,
	{
		t.getX(),
		t.getY(),
		t.getZ(),
		t.getW()
	});

	auto product = *this * m;
	return four_tuple(
		product.getElementAt(0,0),
		product.getElementAt(1,0),
		product.getElementAt(2,0),
		product.getElementAt(3,0));
}

float get2x2Determinant(float a, float b, float c, float d)
{
	return a * d - b * c;
}

float matrix::getDeterminant() const
{
	if (_rows == 2 && _columns == 2)
		return get2x2Determinant(_elements.at(0), _elements.at(1), _elements.at(2), _elements.at(3));

	throw std::out_of_range("Must be a 2x2 matrix.");
}

float matrix::getMinorOfElementAt(int row, int column) const
{
	if (_rows == 3 && _columns == 3)
		return getSubmatrix(row, column).getDeterminant();

	throw std::out_of_range("Must be a 3x3 matrix.");
}

matrix matrix::getSubmatrix(int removedRow, int removedColumn) const
{
	auto s = matrix(_rows - 1, _columns - 1);

	int newRow = 0;
	for (int row = 0; row < _rows; row++)
	{
		if (row == removedRow)
			continue;

		int newColumn = 0;
		for (int column = 0; column < _columns; column++)
		{
			if (column == removedColumn)
				continue;

			s.setElementAt(newRow, newColumn, getElementAt(row, column));

			newColumn++;
		}

		newRow++;
	}

	return std::move(s);
}

matrix matrix::getTransposed() const
{
	auto m = matrix(_columns, _rows);
	for (int row = 0; row < _rows; row++)
	{
		for (int column = 0; column < _columns; column++)
			m.setElementAt(column, row, getElementAt(row, column));
	}
	return std::move(m);
}

float matrix::getElementAt(int row, int column) const
{
	return _elements[getElementIndex(row, column)];
}

void matrix::setElementAt(int row, int column, float element)
{
	_elements[getElementIndex(row, column)] = element;
}

int matrix::getElementIndex(int row, int column) const
{
	return column + (_columns * row);
}
} // namespace data_structures
