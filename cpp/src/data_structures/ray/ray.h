#pragma once

#include "../four_tuple/four_tuple.h"
#include "../matrix/matrix.h"

namespace data_structures
{
class ray
{
public:
	ray(four_tuple origin, four_tuple direction);

	four_tuple getOrigin() const;
	four_tuple getDirection() const;
	four_tuple getPositionAt(float t) const;

	ray getTransformed(const matrix & transformation) const;

private:
	four_tuple _origin;
	four_tuple _direction;
};
} // namespace data_structures
