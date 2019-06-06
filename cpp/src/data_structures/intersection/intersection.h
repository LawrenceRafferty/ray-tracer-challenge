#pragma once

#include "../../shapes/sphere/sphere.h"

namespace data_structures
{
class intersection
{
public:
	intersection(float t, std::shared_ptr<const shapes::sphere> object);

	float getT() const;
	std::shared_ptr<const shapes::sphere> getObject() const;

	bool operator==(const intersection & other) const;
	bool operator!=(const intersection & other) const;

	bool operator<(const intersection & other) const;
	bool operator>(const intersection & other) const;

	bool isHitCandidate() const;

private:
	float _t;
	std::shared_ptr<const shapes::sphere> _object;
};
} // namespace data_structures
