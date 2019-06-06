#pragma once

#include <vector>
#include "../../data_structures/ray/ray.h"
#include "../../data_structures/matrix/matrix.h"

namespace shapes
{
class sphere
{
public:
	sphere();

	data_structures::matrix getTransform() const;
	void setTransform(const data_structures::matrix & transform);

	data_structures::four_tuple getNormalAtPoint(const data_structures::four_tuple & p) const;

	std::vector<float> intersect(const data_structures::ray & r) const;

private:
	data_structures::matrix _transform;
};
} // namespace shapes
