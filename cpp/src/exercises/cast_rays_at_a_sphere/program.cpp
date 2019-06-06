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

void castRays(canvas & c, std::shared_ptr<sphere> s, float sphereZ, int multiplier)
{
	auto red = color(1, 0, 0);
	auto green = color (0, 1, 0);
	auto blue = color(0, 0, 1);
	auto yellow = red + green;
	auto orange = color(1, 0.8, 0);
	auto purple = red + blue;
	auto cyan = green + blue;
	auto rainbow = std::vector<color> { red, orange, yellow, green, cyan, blue, purple };
	auto pixelColor = rainbow[(multiplier - 1) % rainbow.size()];

	int canvasWidth = c.getWidth();
	int canvasHeight = c.getHeight();
	auto rayOrigin = four_tuple::point(canvasWidth / 2, canvasHeight / 2, sphereZ - 30 * multiplier);
	for (int y = 0; y < canvasHeight; y++)
	{
		for (int x = 0; x < canvasWidth; x++)
		{
			auto direction = (four_tuple::point(x, y, 0) - rayOrigin).getNormalized();
			auto r = ray(rayOrigin, direction);
			auto xs = intersections::find(s, r);
			auto hit = xs.getHit();
			if (hit != nullptr)
				c.setPixelAt(x, y, pixelColor);
		}
	}
}

int main()
{
	int width = 100;
	int height = 100;
	auto c = canvas(width, height);

	float sphereZ = -20;
	auto s = std::make_shared<sphere>();
	s->setTransform(matrix::scaling(20, 20, 20).getTranslated(width / 2, height / 2, sphereZ));

	for (int multiplier = 1; multiplier <= 7; multiplier++)
		castRays(c, s, sphereZ, multiplier);

	auto ppm = image_formats::plain_ppm::write(c);
	image_formats::file_utility::overwrite("./cpp/src/exercises/cast_rays_at_a_sphere/cast_rays_at_a_sphere.ppm", ppm);

	return 0;
}
