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

	std::vector<float> intersect(const data_structures::ray & r) const;

	data_structures::matrix getTransform() const;
	void setTransform(const data_structures::matrix & transform);

private:
	data_structures::matrix _transform;
};
} // namespace shapes
