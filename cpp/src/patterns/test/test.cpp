#include "./test.h"
#include "../../data_structures/color/color.h"
#include "../../data_structures/four_tuple/four_tuple.h"

using data_structures::color;
using data_structures::four_tuple;

namespace patterns
{
	test::test() : pattern() {}

	color test::getColorOnObjectAtPoint(const four_tuple & objectSpacePoint) const
	{
		auto patternSpacePoint = getPatternSpacePoint(objectSpacePoint);
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
