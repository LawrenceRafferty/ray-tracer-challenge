#pragma once

#include "../../data_structures/color/color.h"
#include "../../data_structures/four_tuple/four_tuple.h"

namespace lights
{
class point_light
{
public:
	point_light(data_structures::four_tuple position, data_structures::color intensity);

	const data_structures::four_tuple & getPosition() const;
	const data_structures::color & getIntensity() const;

private:
	data_structures::four_tuple _position;
	data_structures::color _intensity;
};
} // namespace lights
