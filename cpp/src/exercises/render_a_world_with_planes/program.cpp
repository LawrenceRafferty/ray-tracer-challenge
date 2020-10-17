#include "../../data_structures/camera/camera.cpp"
#include "../../data_structures/canvas/canvas.h"
#include "../../data_structures/color/color.cpp"
#include "../../data_structures/four_tuple/four_tuple.cpp"
#include "../../data_structures/intersection/intersection.cpp"
#include "../../data_structures/intersections/intersections.cpp"
#include "../../data_structures/intersection_computations/intersection_computations.cpp"
#include "../../data_structures/material/material.cpp"
#include "../../data_structures/matrix/matrix.cpp"
#include "../../data_structures/ray/ray.cpp"
#include "../../data_structures/world/world.cpp"
#include "../../image_formats/file_utility.cpp"
#include "../../image_formats/ppm/plain_ppm.cpp"
#include "../../lights/lighting.cpp"
#include "../../lights/point_light/point_light.cpp"
#include "../../shapes/plane/plane.cpp"
#include "../../shapes/shape.cpp"
#include "../../shapes/sphere/sphere.cpp"
#include "../../transformations/transformations.cpp"

using data_structures::camera;
using data_structures::color;
using data_structures::four_tuple;
using data_structures::intersections;
using data_structures::material;
using data_structures::matrix;
using data_structures::ray;
using data_structures::world;
using lights::lighting;
using lights::point_light;
using shapes::plane;
using shapes::sphere;

int main()
{
	auto floor = std::make_shared<plane>();
	auto floorAndWallMaterial = material();
	floorAndWallMaterial.setColor(color(1, 0.9, 0.9));
	floorAndWallMaterial.setSpecular(0);
	floor->setMaterial(floorAndWallMaterial);

	auto leftWall = std::make_shared<plane>();
	leftWall->setTransform(
		matrix::rotation_x(M_PI_2)
		.getRotated_y(-M_PI_4)
		.getTranslated(0, 0, 5));
	leftWall->setMaterial(floorAndWallMaterial);

	auto rightWall = std::make_shared<plane>();
	rightWall->setTransform(
		matrix::rotation_x(M_PI_2)
		.getRotated_y(M_PI_4)
		.getTranslated(0, 0, 5));
	rightWall->setMaterial(floorAndWallMaterial);
	
	auto middleSphere = std::make_shared<sphere>();
	middleSphere->setTransform(matrix::translation(-0.5, 1, 0.5));
	auto middleSphereMaterial = material();
	middleSphereMaterial.setColor(color(0.1, 1, 0.5));
	middleSphereMaterial.setDiffuse(0.7);
	middleSphereMaterial.setSpecular(0.3);
	middleSphere->setMaterial(middleSphereMaterial);

	auto rightSphere = std::make_shared<sphere>();
	rightSphere->setTransform(matrix::scaling(0.5, 0.5, 0.5).getTranslated(1.5, 0.5, -0.5));
	auto rightSphereMaterial = material();
	rightSphereMaterial.setColor(color(0.5, 1, 0.1));
	rightSphereMaterial.setDiffuse(0.7);
	rightSphereMaterial.setSpecular(0.3);
	rightSphere->setMaterial(rightSphereMaterial);

	auto leftSphere = std::make_shared<sphere>();
	leftSphere->setTransform(matrix::scaling(0.33, 0.33, 0.33).getTranslated(-1.5, 0.33, -0.75));
	auto leftSphereMaterial = material();
	leftSphereMaterial.setColor(color(1, 0.8, 0.1));
	leftSphereMaterial.setDiffuse(0.7);
	leftSphereMaterial.setSpecular(0.3);
	leftSphere->setMaterial(leftSphereMaterial);

	auto w = world();
	w.addLight(point_light(four_tuple::point(-10, 10, -10), color(1, 1, 1)));
	w.addObject(floor);
	w.addObject(leftWall);
	w.addObject(rightWall);
	w.addObject(leftSphere);
	w.addObject(middleSphere);
	w.addObject(rightSphere);

	auto c = camera(200, 150, M_PI / 3, transformations::getViewTransform(
		four_tuple::point(0, 1.5, -5),
		four_tuple::point(0, 1, 0),
		four_tuple::vector(0, 1, 0)));

	auto canvas = c.render(w);

	auto ppm = image_formats::plain_ppm::write(canvas);
	image_formats::file_utility::overwrite("./cpp/src/exercises/render_a_world_with_planes/render_a_world_with_planes.ppm", ppm);

	return 0;
}
