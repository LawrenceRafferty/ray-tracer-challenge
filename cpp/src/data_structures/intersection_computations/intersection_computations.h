#pragma once

#include "../../shapes/sphere/sphere.h"
#include "../four_tuple/four_tuple.h"
#include "../intersection/intersection.h"
#include "../ray/ray.h"

namespace data_structures
{
class intersection_computations
{
public:
	static const intersection_computations & prepare(const intersection & i, const ray & r);

	float getT() const;
	std::shared_ptr<const shapes::sphere> getObject() const;
	const four_tuple & getPoint() const;
	const four_tuple & getEyeVector() const;
	const four_tuple & getNormalVector() const;;

private:
	intersection_computations(
		float t,
		std::shared_ptr<const shapes::sphere> object,
		const four_tuple & point,
		const four_tuple & eyeVector,
		const four_tuple & normalVector);

	float _t;
	std::shared_ptr<const shapes::sphere> _object;
	four_tuple _point;
	four_tuple _eyeVector;
	four_tuple _normalVector;
};
} // namespace data_structures
