#include "../../src/data_structures/color/color.h"
#include "../../src/data_structures/four_tuple/four_tuple.h"
#include "../../src/data_structures/world/world.h"
#include "../../src/lights/point_light/point_light.h"
#include "../../src/shapes/sphere/sphere.h"

namespace default_world
{
lights::point_light getDefaultWorldLight()
{
	return std::move(lights::point_light(data_structures::four_tuple::point(-10, 10, -10), data_structures::color(1, 1, 1)));
}

std::shared_ptr<shapes::sphere> getDefaultWorldSphere1()
{
	auto s1 = std::make_shared<shapes::sphere>();
	auto m = data_structures::material();
	m.setColor(data_structures::color(0.8, 1.0, 0.6));
	m.setDiffuse(0.7);
	m.setSpecular(0.2);
	s1->setMaterial(m);
	return s1;
}

std::shared_ptr<shapes::sphere> getDefaultWorldSphere2()
{
	auto s2 = std::make_shared<shapes::sphere>();
	s2->setTransform(data_structures::matrix::scaling(0.5, 0.5, 0.5));
	return s2;
}

data_structures::world getDefaultWorld()
{
	auto defaultWorld = data_structures::world();
	defaultWorld.addLight(getDefaultWorldLight());
	defaultWorld.addObject(getDefaultWorldSphere1());
	defaultWorld.addObject(getDefaultWorldSphere2());
	return std::move(defaultWorld);
}
}
