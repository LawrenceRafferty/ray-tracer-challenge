#pragma once

#include <vector>

namespace shapes
{
class sphere
{
public:
	sphere();

	std::vector<float> intersect(const data_structures::ray & r) const;
};
} // namespace shapes
