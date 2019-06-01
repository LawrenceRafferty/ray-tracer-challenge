#pragma once

#include <initializer_list>
#include <vector>

namespace data_structures
{
class matrix
{
public:
	matrix(int dimension);
	matrix(std::initializer_list<float> elements);

	bool operator==(const matrix & other) const;
	bool operator!=(const matrix & other) const;

	float getElementAt(int row, int column) const;

private:
	int _dimension;
	std::vector<float> _data;
};
} // namespace data_structures
