#pragma once

#include "../../data_structures/color/color.h"
#include "../../data_structures/four_tuple/four_tuple.h"
#include "../pattern.h"

namespace patterns
{
class solid : public pattern
{
public:
	solid(data_structures::color color);

	data_structures::color getColorAtPoint(const data_structures::four_tuple & patternSpacePoint) const;

private:
	bool equals(const pattern & other) const;

	data_structures::color _color;
};
} // namespace patterns
