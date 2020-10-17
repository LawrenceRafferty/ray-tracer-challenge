#pragma once

#include <vector>
#include "../../lights/point_light/point_light.h"
#include "../../shapes/shape.h"
#include "../color/color.h"
#include "../intersection_computations/intersection_computations.h"

namespace data_structures
{
class world
{
public:
	world();

	const std::vector<lights::point_light> & getLights() const;
	void addLight(const lights::point_light & light);

	const std::vector<std::shared_ptr<shapes::shape>> & getObjects() const;
	void addObject(std::shared_ptr<shapes::shape> object);

	color shadeHit(const intersection_computations & computations) const;

	color getColorAt(const ray & r) const;

	bool getIsShadowed(const four_tuple & point) const;

private:
	color shadeHitWithSingleLight(const lights::point_light & light, const intersection_computations & computations) const;

	bool getIsShadowed(const lights::point_light & light, const four_tuple & point) const;

	std::vector<lights::point_light> _lights;
	std::vector<std::shared_ptr<shapes::shape>> _objects;
};
} // namespace data_structures
