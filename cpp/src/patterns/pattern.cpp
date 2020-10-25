#include "./pattern.h"
#include "../data_structures/color/color.h"
#include "../data_structures/four_tuple/four_tuple.h"
#include "../data_structures/matrix/matrix.h"
#include "../shapes/shape.h"

using data_structures::color;
using data_structures::four_tuple;
using data_structures::matrix;
using shapes::shape;

namespace patterns
{
pattern::pattern()
	: _transform { matrix
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	}}
	{}

	const matrix & pattern::getTransform() const { return _transform; }
	void pattern::setTransform(data_structures::matrix && transform) { _transform = std::move(transform); }

	color pattern::getColorOnObjectAtPoint(const shape & object, const four_tuple & worldSpacePoint) const
	{
		auto objectSpacePoint = object.getTransform().getInverse() * worldSpacePoint;
		auto patternSpacePoint = _transform.getInverse() * objectSpacePoint;
		return getColorAtPoint(patternSpacePoint);
	}
}
