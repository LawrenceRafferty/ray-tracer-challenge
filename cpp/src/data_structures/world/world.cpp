#include "./world.h"

using lights::point_light;
using shapes::sphere;

namespace data_structures
{
world::world()
	: _lights { std::move(std::vector<point_light>()) }
	, _objects { std::move(std::vector<std::shared_ptr<sphere>>()) }
	{}

const std::vector<lights::point_light> & world::getLights() const { return _lights; }

void world::addLight(const point_light & light)
{
	_lights.emplace_back(light);
}

const std::vector<std::shared_ptr<shapes::sphere>> & world::getObjects() const { return _objects; }

void world::addObject(std::shared_ptr<sphere> object)
{
	_objects.emplace_back(object);
}

} // namespace data_structures
