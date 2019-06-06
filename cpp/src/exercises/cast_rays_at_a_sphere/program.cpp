#include "../../data_structures/canvas/canvas.h"
#include "../../data_structures/color/color.cpp"
#include "../../data_structures/four_tuple/four_tuple.cpp"
#include "../../data_structures/intersection/intersection.cpp"
#include "../../data_structures/intersections/intersections.cpp"
#include "../../data_structures/matrix/matrix.cpp"
#include "../../data_structures/ray/ray.cpp"
#include "../../image_formats/file_utility.cpp"
#include "../../image_formats/ppm/plain_ppm.cpp"
#include "../../shapes/sphere/sphere.cpp"

using data_structures::canvas;
using data_structures::color;
using data_structures::four_tuple;
using data_structures::intersections;
using data_structures::matrix;
using data_structures::ray;
using shapes::sphere;

int main()
{
	auto width = 100;
	auto height = 100;
	auto c = canvas(width, height);

	auto red = color(1, 0, 0);

	auto s = std::make_shared<sphere>();
	s->setTransform(matrix::scaling(20, 20, 20).getTranslated(width / 2, height / 2, -40));

	auto rayOrigin = four_tuple::point(width / 2, height / 2, -100);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			auto direction = (four_tuple::point(x, y, 0) - rayOrigin).getNormalized();
			auto r = ray(rayOrigin, direction);
			auto xs = intersections::find(s, r);
			auto hit = xs.getHit();
			if (hit != nullptr)
				c.setPixelAt(x, y, red);
		}
	}

	auto ppm = image_formats::plain_ppm::write(c);
	image_formats::file_utility::overwrite("./cpp/src/exercises/cast_rays_at_a_sphere/cast_rays_at_a_sphere.ppm", ppm);

	return 0;
}
