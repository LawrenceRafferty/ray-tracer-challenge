#include "./stripe.h"
#include <cmath>
#include "../../data_structures/color/color.h"
#include "../../data_structures/four_tuple/four_tuple.h"
#include "../pattern.h"

using data_structures::color;
using data_structures::four_tuple;

namespace patterns
{
	stripe::stripe(std::vector<std::shared_ptr<pattern>> patterns)
		: _patterns { std::move(patterns) }
	{}

	stripe::stripe(std::initializer_list<std::shared_ptr<pattern>> patterns)
		: _patterns { std::vector(patterns) }
	{}

	color stripe::getColorAtPoint(const four_tuple & point) const
	{
		auto patternIndex = static_cast<int>(floor(point.getX())) % _patterns.size();
		return _patterns.at(patternIndex)->getColorAtPoint(point);
	}
} // namespace patterns
