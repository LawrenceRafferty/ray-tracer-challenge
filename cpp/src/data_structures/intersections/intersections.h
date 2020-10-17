#pragma once

#include <vector>
#include "../../shapes/shape.h"
#include "../intersection/intersection.h"
#include "../world/world.h"

namespace data_structures
{
class intersections
{
public:
	static intersections find(std::shared_ptr<const shapes::shape> object, const ray & r);
	static intersections find(const data_structures::world & w, const ray & r);

	intersections(std::vector<intersection> intersections);
	intersections(std::initializer_list<intersection> intersections);

	int size() const;

	intersection at(int index) const;

	std::unique_ptr<const intersection> getHit() const;

private:
	std::vector<intersection> _intersections;
};
} // namespace data_structures
