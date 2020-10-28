#pragma once

#include "../data_structures/color/color.h"
#include "../data_structures/four_tuple/four_tuple.h"
#include "../shapes/shape.h"
#include "./point_light/point_light.h"

namespace lights
{
	data_structures::color lighting(
		const shapes::shape & shape,
		const point_light & light,
		const data_structures::four_tuple & point,
		const data_structures::four_tuple & eyev,
		const data_structures::four_tuple & normalv,
		bool isShadowed);
}
