#pragma once

#include <cmath>

namespace float_utility
{
constexpr float EPSILON = 0.00001f;

bool are_equivalent(float left, float right)
{
	return abs(left - right) < EPSILON;
}
} // namespace float_utility
