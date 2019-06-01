#pragma once

#include <initializer_list>
#include <vector>

namespace data_structures
{
class matrix
{
public:
	matrix(int dimension);
	matrix(int rows, int columns);
	matrix(std::initializer_list<float> elements);
	matrix(int rows, int columns, std::initializer_list<float> elements);

	bool operator==(const matrix & other) const;
	bool operator!=(const matrix & other) const;

	matrix operator*(const matrix & other) const;

	float getElementAt(int row, int column) const;
	void setElementAt(int row, int column, float element);

private:
	int getElementIndex(int row, int column) const;

	int _rows;
	int _columns;
	std::vector<float> _data;
};
} // namespace data_structures
