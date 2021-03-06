#include "./point_light.h"

using data_structures::color;
using data_structures::four_tuple;

namespace lights
{
point_light::point_light(four_tuple position, color intensity)
	: _position { position }
	, _intensity { intensity }
	{}

const four_tuple & point_light::getPosition() const { return _position; }
const color & point_light::getIntensity() const { return _intensity; }

bool point_light::operator==(const point_light & other) const
{
	return _position == other._position &&
		_intensity == other._intensity;
}
} // namespace lights
