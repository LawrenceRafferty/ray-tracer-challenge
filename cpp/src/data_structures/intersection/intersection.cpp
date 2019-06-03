#include "./intersection.h"

using shapes::sphere;

namespace data_structures
{
intersection::intersection(float t, std::shared_ptr<shapes::sphere> object)
	: _t { t }
	, _object { object }
	{}

float intersection::getT() const { return _t; }

std::shared_ptr<shapes::sphere> intersection::getObject() const { return _object; }
} // namespace data_structures
