#include "./intersection.h"

using shapes::sphere;

namespace data_structures
{
intersection::intersection(float t, std::shared_ptr<const shapes::sphere> object)
	: _t { t }
	, _object { object }
	{}

float intersection::getT() const { return _t; }

std::shared_ptr<const shapes::sphere> intersection::getObject() const { return _object; }

bool intersection::operator==(const intersection & other) const
{
	return _t == other._t &&
		_object == other._object;
}

bool intersection::operator!=(const intersection & other) const
{
	return !(*this == other);
}

bool intersection::operator<(const intersection & other) const
{
	return _t < other._t;
}

bool intersection::operator>(const intersection & other) const
{
	return _t > other._t;
}

bool intersection::isHitCandidate() const
{
	return _t >= 0;
}
} // namespace data_structures
