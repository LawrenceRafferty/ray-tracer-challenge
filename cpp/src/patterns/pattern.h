#pragma once

#include "../data_structures/color/color.h"
#include "../data_structures/four_tuple/four_tuple.h"
#include "../data_structures/matrix/matrix.h"

namespace patterns
{
class pattern
{
public:
	pattern();

	const data_structures::matrix & getTransform() const;
	void setTransform(data_structures::matrix && transform);

	virtual data_structures::color getColorOnObjectAtPoint(const data_structures::four_tuple & objectSpacePoint) const = 0;

	bool operator==(const pattern & other) const;
	bool operator!=(const pattern & other) const;

protected:
	data_structures::four_tuple getPatternSpacePoint(const data_structures::four_tuple & objectSpacePoint) const;

	virtual bool equals(const pattern & other) const = 0;

private:
	data_structures::matrix _transform;
	data_structures::matrix _inverseTransform;
};
} // namespace patterns
