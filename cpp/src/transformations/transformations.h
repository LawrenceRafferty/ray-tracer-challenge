#pragma once

#include "../data_structures/four_tuple/four_tuple.h"
#include "../data_structures/matrix/matrix.h"

namespace transformations
{
	data_structures::matrix getViewTransform(
		const data_structures::four_tuple & fromPoint,
		const data_structures::four_tuple & toPoint,
		const data_structures::four_tuple & upVector
	);
}
