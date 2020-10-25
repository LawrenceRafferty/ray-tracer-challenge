#include "./solid.h"
#include "../../data_structures/color/color.h"
#include "../../data_structures/four_tuple/four_tuple.h"

using data_structures::color;
using data_structures::four_tuple;

namespace patterns
{
	solid::solid(color color) : pattern()
		, _color { color }
		{}

	color solid::getColorAtPoint(const four_tuple &patternSpacePoint) const
	{
		return _color;
	}
} // namespace patterns
