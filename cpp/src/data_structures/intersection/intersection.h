#pragma once

#include "../../shapes/shape.h"

namespace data_structures
{
class intersection
{
public:
	intersection(float t, std::shared_ptr<const shapes::shape> object);

	float getT() const;
	std::shared_ptr<const shapes::shape> getObject() const;

	bool operator==(const intersection & other) const;
	bool operator!=(const intersection & other) const;

	bool operator<(const intersection & other) const;
	bool operator>(const intersection & other) const;

	bool isHitCandidate() const;

private:
	float _t;
	std::shared_ptr<const shapes::shape> _object;
};
} // namespace data_structures
