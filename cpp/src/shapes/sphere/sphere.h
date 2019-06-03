#pragma once

#include <vector>
#include "../../data_structures/ray/ray.h"

namespace shapes
{
class sphere
{
public:
	sphere();

	std::vector<float> intersect(const data_structures::ray & r) const;
};
} // namespace shapes
