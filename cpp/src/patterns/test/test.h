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

	data_structures::color getColorOnObjectAtPoint(const data_structures::four_tuple & objectSpacePoint) const;

private:
	bool equals(const pattern & other) const;
};
} // namespace patterns
