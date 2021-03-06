#include "./world.h"
#include "../../lights/lighting.h"
#include "../intersections/intersections.h"

using data_structures::intersections;
using lights::lighting;
using lights::point_light;
using shapes::shape;

namespace data_structures
{
world::world()
	: _lights { std::move(std::vector<point_light>()) }
	, _objects { std::move(std::vector<std::shared_ptr<shape>>()) }
	{}

const std::vector<lights::point_light> & world::getLights() const { return _lights; }

void world::addLight(const point_light & light)
{
	_lights.emplace_back(light);
}

const std::vector<std::shared_ptr<shapes::shape>> & world::getObjects() const { return _objects; }

void world::addObject(std::shared_ptr<shape> object)
{
	_objects.emplace_back(object);
}

color world::shadeHitWithSingleLight(const point_light & light, const intersection_computations & computations) const
{
	auto isShadowed = this->getIsShadowed(light, computations.getOverPoint());
	return lighting(
		*computations.getObject(),
		light,
		computations.getOverPoint(),
		computations.getEyeVector(),
		computations.getNormalVector(),
		isShadowed);
}

color world::shadeHit(const intersection_computations & computations) const
{
	if (_lights.size() == 1)
		return shadeHitWithSingleLight(_lights.at(0), computations);

	auto combined = color();
	for (auto light : _lights)
	{
		auto c = shadeHitWithSingleLight(light, computations);
		combined = combined + c;
	}
	return combined;
}

	color world::getColorAt(const ray & r) const
	{
		auto intersections = intersections::find(*this, r);
		auto hit = intersections.getHit();
		if (hit == nullptr)
			return color();

		auto computations = intersection_computations::prepare(*hit, r);
		return shadeHit(computations);
	}

	bool world::getIsShadowed(const four_tuple & point) const
	{
		for (auto light : _lights)
		{
			auto isShadowed = world::getIsShadowed(light, point);
			if (!isShadowed)
				return false;
		}

		return true;
	}

	bool world::getIsShadowed(const point_light & light, const four_tuple & point) const
	{
		auto vectorFromPointToLightSource = light.getPosition() - point;
		auto distanceToLightSource = vectorFromPointToLightSource.getMagnitude();
		auto directionToLightSource = vectorFromPointToLightSource.getNormalized();
		auto rayFromPointToLightSource = ray(point, directionToLightSource);
		auto intersections = intersections::find(*this, rayFromPointToLightSource);
		auto hit = intersections.getHit();
		return hit != nullptr && hit->getT() < distanceToLightSource;
	}

} // namespace data_structures
