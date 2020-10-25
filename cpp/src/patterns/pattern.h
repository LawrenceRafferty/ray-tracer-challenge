#pragma once

#include "../data_structures/color/color.h"
#include "../data_structures/four_tuple/four_tuple.h"
#include "../data_structures/matrix/matrix.h"
#include "../shapes/shape.h"

namespace patterns
{
class pattern
{
public:
	pattern();

	const data_structures::matrix & getTransform() const;
	void setTransform(data_structures::matrix && transform);

	data_structures::color getColorOnObjectAtPoint(const shapes::shape & object, const data_structures::four_tuple & worldSpacePoint) const;

	// exposed for testing
	virtual data_structures::color getColorAtPoint(const data_structures::four_tuple & patternSpacePoint) const = 0;

private:
	data_structures::matrix _transform;
};
} // namespace patterns
