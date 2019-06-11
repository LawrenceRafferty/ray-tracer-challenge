#pragma once

#include <vector>
#include "../../data_structures/four_tuple/four_tuple.h"
#include "../../data_structures/material/material.h"
#include "../../data_structures/matrix/matrix.h"
#include "../../data_structures/ray/ray.h"

namespace shapes
{
class sphere
{
public:
	sphere();

	const data_structures::material & getMaterial() const;
	void setMaterial(const data_structures::material & material);

	const data_structures::matrix & getTransform() const;
	void setTransform(const data_structures::matrix & transform);

	data_structures::four_tuple getNormalAtPoint(const data_structures::four_tuple & p) const;

	std::vector<float> intersect(const data_structures::ray & r) const;

	bool operator==(const sphere & other) const;
	bool operator!=(const sphere & other) const;

private:
	data_structures::material _material;
	data_structures::matrix _transform;
};
} // namespace shapes
