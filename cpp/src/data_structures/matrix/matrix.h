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

	bool operator==(const matrix & other) const;
	bool operator!=(const matrix & other) const;

	matrix operator*(const matrix & other) const;
	four_tuple operator*(const four_tuple & t) const;

	matrix transpose() const;

	float getElementAt(int row, int column) const;
	void setElementAt(int row, int column, float element);

private:
	int getElementIndex(int row, int column) const;

	int _rows;
	int _columns;
	std::vector<float> _data;
};
} // namespace data_structures
