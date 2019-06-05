#pragma once

#include <vector>
#include "../../shapes/sphere/sphere.h"
#include "../intersection/intersection.h"

namespace data_structures
{
class intersections
{
public:
	static intersections find(std::shared_ptr<const sphere> object, const ray & r);

	intersections(std::vector<intersection> intersections);
	intersections(std::initializer_list<intersection> intersections);

	int size() const;

	intersection at(int index) const;

private:
	std::vector<intersection> _intersections;
};
} // namespace data_structures
