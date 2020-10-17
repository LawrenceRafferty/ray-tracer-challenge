#pragma once

#include <vector>
#include "../../data_structures/four_tuple/four_tuple.h"
#include "../../data_structures/ray/ray.h"
#include "../shape.h"

namespace shapes
{
class plane : public shape
{
public:
	plane();

	data_structures::four_tuple getLocalNormalAtLocalPoint_test(const data_structures::four_tuple & localPoint) const;

	std::vector<float> localIntersect_test(const data_structures::ray & r) const;

private:
	data_structures::four_tuple getLocalNormalAtLocalPoint(const data_structures::four_tuple & localPoint) const;

	std::vector<float> localIntersect(const data_structures::ray & r) const;
};
} // namespace shapes
