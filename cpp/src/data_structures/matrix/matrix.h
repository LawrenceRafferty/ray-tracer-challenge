#pragma once

#include <initializer_list>
#include <vector>
#include "../four_tuple/four_tuple.h"

namespace data_structures
{
class matrix
{
public:
	matrix(int dimension);
	matrix(int rows, int columns);
	matrix(std::initializer_list<float> elements);
	matrix(int rows, int columns, std::initializer_list<float> elements);
	matrix(matrix && other);

	static matrix rotation_x(float radians);
	static matrix rotation_y(float radians);
	static matrix rotation_z(float radians);
	static matrix scaling(float x, float y, float z);
	static matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy);
	static matrix translation(float x, float y, float z);

	matrix & operator=(matrix && other);

	bool operator==(const matrix & other) const;
	bool operator!=(const matrix & other) const;

	matrix operator*(const matrix & other) const;
	four_tuple operator*(const four_tuple & t) const;

	float getCofactorOfElementAt(int row, int column) const;
	float getDeterminant() const;
	float getMinorOfElementAt(int row, int column) const;
	matrix getSubmatrix(int removedRow, int removedColumn) const;
	matrix getTransposed() const;

	bool isInvertible() const;
	matrix getInverse() const;

	float getElementAt(int row, int column) const;
	void setElementAt(int row, int column, float element);

private:
	int getElementIndex(int row, int column) const;

	int _rows;
	int _columns;
	std::vector<float> _elements;
};
} // namespace data_structures
