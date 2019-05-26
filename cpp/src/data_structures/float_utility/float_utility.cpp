#include "float_utility.h"
#include <cmath>

namespace data_structures
{
constexpr float EPSILON = 0.00001f;

bool float_utility::are_equivalent(float left, float right)
{
	return abs(left - right) < EPSILON;
}
} // namespace data_structures
