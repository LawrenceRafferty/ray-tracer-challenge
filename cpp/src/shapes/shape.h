#pragma once

#include <vector>
#include "../data_structures/color/color.h"
#include "../data_structures/four_tuple/four_tuple.h"
#include "../data_structures/material/material.h"
#include "../data_structures/matrix/matrix.h"
#include "../data_structures/ray/ray.h"

namespace shapes
{
class shape
{
public:
	shape();

	const data_structures::material & getMaterial() const;
	void setMaterial(const data_structures::material & material);

	const data_structures::matrix & getTransform() const;
	void setTransform(data_structures::matrix && transform);

	data_structures::color getColorAtPoint(const data_structures::four_tuple & worldPoint) const;
	data_structures::four_tuple getNormalAtPoint(const data_structures::four_tuple & worldPoint) const;

	std::vector<float> intersect(const data_structures::ray & r) const;

	// used in private implementations, only exposed for testing
	data_structures::four_tuple getLocalPoint(const data_structures::four_tuple & worldPoint) const;

	// used to implement intersect, only exposed for testing
	data_structures::ray getLocalRay(const data_structures::ray & r) const;

private:
	virtual data_structures::four_tuple getLocalNormalAtLocalPoint(const data_structures::four_tuple & localPoint) const = 0;

	virtual std::vector<float> localIntersect(const data_structures::ray & localRay) const = 0;

	data_structures::material _material;
	data_structures::matrix _transform;
	data_structures::matrix _inverseTransform;
};
} // namespace shapes
