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

matrix::matrix(const matrix & other)
	: _rows { other._rows }
	, _columns { other._columns }
	, _elements { other._elements }
	{}

matrix::matrix(matrix && other)
	: _rows { other._rows }
	, _columns { other._columns }
	, _elements { std::move(other._elements) }
	{}

matrix matrix::rotation_x(float radians)
{
	auto c = cos(radians);
	auto s = sin(radians);
	return matrix
	{
		1, 0, 0, 0,
		0, c, -s, 0,
		0, s, c, 0,
		0, 0, 0, 1
	};
}

matrix matrix::rotation_y(float radians)
{
	auto c = cos(radians);
	auto s = sin(radians);
	return matrix
	{
		c, 0, s, 0,
		0, 1, 0, 0,
		-s, 0, c, 0,
		0, 0, 0, 1
	};
}

matrix matrix::rotation_z(float radians)
{
	auto c = cos(radians);
	auto s = sin(radians);
	return matrix
	{
		c, -s, 0, 0,
		s, c, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
}

matrix matrix::scaling(float x, float y, float z)
{
	return matrix
	{
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	};
}

matrix matrix::shearing(float xy, float xz, float yx, float yz, float zx, float zy)
{
	return matrix
	{
		1, xy, xz, 0,
		yx, 1, yz, 0,
		zx, zy, 1, 0,
		0, 0, 0, 1
	};
}

matrix matrix::translation(float x, float y, float z)
{
	return matrix
	{
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};
}

matrix matrix::getRotated_x(float radians) const
{
	auto transform = matrix::rotation_x(radians);
	return transform * *this;
}

matrix matrix::getRotated_y(float radians) const
{
	auto transform = matrix::rotation_y(radians);
	return transform * *this;
}

matrix matrix::getRotated_z(float radians) const
{
	auto transform = matrix::rotation_z(radians);
	return transform * *this;
}

matrix matrix::getScaled(float x, float y, float z) const {
	auto transform = matrix::scaling(x, y, z);
	return transform * *this;
}

matrix matrix::getSheared(float xy, float xz, float yx, float yz, float zx, float zy) const
{
	auto transform = matrix::shearing(xy, xz, yx, yz, zx, zy);
	return transform * *this;
}

matrix matrix::getTranslated(float x, float y, float z) const
{
	auto transform = matrix::translation(x, y, z);
	return transform * *this;
}

matrix& matrix::operator=(const matrix & other)
{
	_rows = other._rows;
	_columns = other._columns;
	_elements = other._elements;
	return *this;
}

matrix& matrix::operator=(matrix && other)
{
	_rows = other._rows;
	_columns = other._columns;
	_elements = std::move(other._elements);
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
			float element = 0;
			for (int index = 0; index < sharedDimension; index++)
				element += getElementAt(row, index) * other.getElementAt(index, column);

			m.setElementAt(row, column, element);
		}
	}

	return m;
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

float matrix::getCofactorOfElementAt(int row, int column) const
{
	if (_rows != _columns)
		throw std::invalid_argument("Must be a square matrix.");
	if (_rows <= 2)
		throw std::out_of_range("Must be 3x3 or larger.");

	auto minor = getMinorOfElementAt(row, column);
	return (row + column) % 2 == 0 ? minor : -minor;
}

float matrix::getDeterminant() const
{
	if (_rows == 2 && _columns == 2)
		return _elements.at(0) * _elements.at(3) - _elements.at(1) * _elements.at(2);

	if (_rows != _columns)
		throw std::invalid_argument("Must be a square matrix.");
	
	float determinant = 0;
	for (int column = 0; column < _columns; column++)
		determinant += _elements.at(column) * getCofactorOfElementAt(0, column);

	return determinant;
}

float matrix::getMinorOfElementAt(int row, int column) const
{
	if (_rows != _columns)
		throw std::invalid_argument("Must be a square matrix.");
	if (_rows <= 2)
		throw std::out_of_range("Must be 3x3 or larger.");

	return getSubmatrix(row, column).getDeterminant();
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

	return s;
}

matrix matrix::getTransposed() const
{
	auto m = matrix(_columns, _rows);
	for (int row = 0; row < _rows; row++)
	{
		for (int column = 0; column < _columns; column++)
			m.setElementAt(column, row, getElementAt(row, column));
	}
	return m;
}

bool matrix::isInvertible() const
{
	// ASSUME: equality is sufficient
	return getDeterminant() != 0;
}

matrix matrix::getInverse() const
{
	if (_rows != _columns)
		throw std::invalid_argument("Must be a square matrix.");

	auto determinant = getDeterminant();
	if (determinant == 0)
		throw std::logic_error("Must be an invterible matrix.");

	auto inverse = matrix(_rows);
	for (int row = 0; row < _rows; row++)
	{
		for (int column = 0; column < _columns; column++)
		{
			auto cofactor = getCofactorOfElementAt(row, column);
			// reverse row and column to accomplish transposition
			inverse.setElementAt(column, row, cofactor / determinant);
		}
	}

	return inverse;
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
