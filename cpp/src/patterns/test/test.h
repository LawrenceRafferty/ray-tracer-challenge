#pragma once

#include "../../data_structures/color/color.h"
#include "../../data_structures/four_tuple/four_tuple.h"
#include "../pattern.h"

namespace patterns
{
class test : public pattern
{
public:
	test();

	data_structures::color getColorAtPoint(const data_structures::four_tuple & patternSpacePoint) const;
};
} // namespace patterns
