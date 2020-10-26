#include "./test.h"
#include "../../data_structures/color/color.h"
#include "../../data_structures/four_tuple/four_tuple.h"

using data_structures::color;
using data_structures::four_tuple;

namespace patterns
{
	test::test() : pattern() {}

	color test::getColorAtPoint(const four_tuple & patternSpacePoint) const
	{
		return color(
			patternSpacePoint.getX(),
			patternSpacePoint.getY(),
			patternSpacePoint.getZ());
	}

	bool test::equals(const pattern & other) const
	{
		return true;
	}
}
