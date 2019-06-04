#pragma once

#include <vector>
#include "../intersection/intersection.h"

namespace data_structures
{
class intersections
{
public:
	intersections(std::initializer_list<intersection> intersections);

	int size() const;

	intersection at(int index) const;

private:
	std::vector<intersection> _intersections;
};
} // namespace data_structures
