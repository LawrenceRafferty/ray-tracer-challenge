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

	data_structures::color getColorAtPoint(const data_structures::four_tuple &point) const;

private:
	std::vector<std::shared_ptr<pattern>> _patterns;
};
} // namespace patterns
