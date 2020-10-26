#include "./pattern.h"
#include "../data_structures/color/color.h"
#include "../data_structures/four_tuple/four_tuple.h"
#include "../data_structures/matrix/matrix.h"

using data_structures::color;
using data_structures::four_tuple;
using data_structures::matrix;

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
	, _inverseTransform { _transform.getInverse() }
	{}

	const matrix & pattern::getTransform() const { return _transform; }
	void pattern::setTransform(data_structures::matrix && transform)
	{
		_transform = std::move(transform);
		_inverseTransform = _transform.getInverse();
	}

	color pattern::getColorOnObjectAtPoint(const four_tuple & objectSpacePoint) const
	{
		auto patternSpacePoint = _inverseTransform * objectSpacePoint;
		return getColorAtPoint(patternSpacePoint);
	}

	bool pattern::operator==(const pattern & other) const
	{
		return typeid(*this) == typeid(other) &&
			_transform == other._transform &&
			equals(other);
	}

	bool pattern::operator!=(const pattern & other) const
	{
		return !(*this == other);
	}
}
