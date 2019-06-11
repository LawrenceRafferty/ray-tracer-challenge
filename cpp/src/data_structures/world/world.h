#pragma once

#include <vector>
#include "../../lights/point_light/point_light.h"
#include "../../shapes/sphere/sphere.h"

namespace data_structures
{
class world
{
public:
	world();

	const std::vector<lights::point_light> & getLights() const;
	const std::vector<shapes::sphere> & getObjects() const;

private:
	std::vector<lights::point_light> _lights;
	std::vector<shapes::sphere> _objects;
};
} // namespace data_structures
