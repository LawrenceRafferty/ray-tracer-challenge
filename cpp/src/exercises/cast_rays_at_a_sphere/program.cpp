#include "../../data_structures/canvas/canvas.h"
#include "../../data_structures/color/color.cpp"
#include "../../data_structures/four_tuple/four_tuple.cpp"
#include "../../data_structures/intersection/intersection.cpp"
#include "../../data_structures/intersections/intersections.cpp"
#include "../../data_structures/material/material.cpp"
#include "../../data_structures/matrix/matrix.cpp"
#include "../../data_structures/ray/ray.cpp"
#include "../../image_formats/file_utility.cpp"
#include "../../image_formats/ppm/plain_ppm.cpp"
#include "../../lights/lighting.cpp"
#include "../../lights/point_light/point_light.cpp"
#include "../../shapes/sphere/sphere.cpp"

using data_structures::canvas;
using data_structures::color;
using data_structures::four_tuple;
using data_structures::intersections;
using data_structures::material;
using data_structures::matrix;
using data_structures::ray;
using lights::lighting;
using lights::point_light;
using shapes::sphere;

void castRays(canvas & c, std::shared_ptr<sphere> s)
{
	int canvasWidth = c.getWidth();
	int canvasHeight = c.getHeight();

	auto lightPosition = four_tuple::point(canvasWidth / 2.5, canvasHeight/ 2.5, -45);
	auto lightColor = color(1, 1, 1);
	auto light = point_light(lightPosition, lightColor);

	auto rayOrigin = four_tuple::point(canvasWidth / 2, canvasHeight / 2, -42);
	for (int y = 0; y < canvasHeight; y++)
	{
		for (int x = 0; x < canvasWidth; x++)
		{
			auto direction = (four_tuple::point(x, y, 0) - rayOrigin).getNormalized();
			auto r = ray(rayOrigin, direction);
			auto xs = intersections::find(s, r);
			auto hit = xs.getHit();
			if (hit != nullptr)
			{
				auto point = r.getPositionAt(hit->getT());
				auto normal = hit->getObject()->getNormalAtPoint(point);
				auto eye = -r.getDirection();
				auto pixelColor = lighting(hit->getObject()->getMaterial(), light, point, eye, normal);
				c.setPixelAt(x, y, pixelColor);
			}
		}
	}
}

int main()
{
	int width = 200;
	int height = 200;
	auto c = canvas(width, height);

	auto s = std::make_shared<sphere>();
	auto m = material();
	m.setColor(color(1, 0.2, 1));
	s->setMaterial(m);
	s->setTransform(matrix::scaling(20, 20, 20).getTranslated(width / 2, height / 2, -20));

	castRays(c, s);

	auto ppm = image_formats::plain_ppm::write(c);
	image_formats::file_utility::overwrite("./cpp/src/exercises/cast_rays_at_a_sphere/cast_rays_at_a_sphere.ppm", ppm);

	return 0;
}
