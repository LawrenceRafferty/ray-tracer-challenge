#include "color.h"
#include "../float_utility/float_utility.cpp"

namespace data_structures
{
	bool color::operator==(const color & other) const
	{
		return float_utility::are_equivalent(_red, other._red) &&
			float_utility::are_equivalent(_green, other._green) &&
			float_utility::are_equivalent(_blue, other._blue);
	}

	bool color::operator!=(const color & other) const
	{
		return !(*this == other);
	}
}
