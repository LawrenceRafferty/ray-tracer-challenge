#include "./world.h"

using lights::point_light;
using shapes::sphere;

namespace data_structures
{
world::world()
	: _lights { std::move(std::vector<point_light>()) }
	, _objects { std::move(std::vector<sphere>()) }
	{}

const std::vector<lights::point_light> & world::getLights() const { return _lights; }

const std::vector<shapes::sphere> & world::getObjects() const { return _objects; }

} // namespace data_structures
