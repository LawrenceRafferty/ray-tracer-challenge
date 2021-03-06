#pragma once

#include "../../data_structures/color/color.h"
#include "../../data_structures/four_tuple/four_tuple.h"
#include "../pattern.h"

namespace patterns
{
class stripe : public pattern
{
public:
	stripe(std::vector<std::shared_ptr<pattern>> patterns);
	stripe(std::initializer_list<std::shared_ptr<pattern>> patterns);

	data_structures::color getColorOnObjectAtPoint(const data_structures::four_tuple & objectSpacePoint) const;

private:
	bool equals(const pattern & other) const;

	std::vector<std::shared_ptr<pattern>> _patterns;
};
} // namespace patterns
