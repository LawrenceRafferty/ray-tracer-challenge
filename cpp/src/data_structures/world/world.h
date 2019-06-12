#pragma once

#include <vector>
#include "../../lights/point_light/point_light.h"
#include "../../shapes/sphere/sphere.h"
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

	const std::vector<std::shared_ptr<shapes::sphere>> & getObjects() const;
	void addObject(std::shared_ptr<shapes::sphere> object);

	color shadeHit(const intersection_computations & computations) const;

	color getColorAt(const ray & r) const;

private:
	std::vector<lights::point_light> _lights;
	std::vector<std::shared_ptr<shapes::sphere>> _objects;
};
} // namespace data_structures
