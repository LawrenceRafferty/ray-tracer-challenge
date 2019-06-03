#include "../../data_structures/canvas/canvas.h"
#include "../../data_structures/color/color.cpp"
#include "../../data_structures/four_tuple/four_tuple.cpp"
#include "../../data_structures/matrix/matrix.cpp"
#include "../../image_formats/file_utility.cpp"
#include "../../image_formats/ppm/plain_ppm.cpp"

using data_structures::canvas;
using data_structures::color;
using data_structures::four_tuple;
using data_structures::matrix;

int main()
{
	auto width = 800;
	auto height = 800;
	auto c = canvas(width, height);

	auto white = color(1, 1, 1);

	auto p = four_tuple::point(0, 1, 0);
	auto extent = height / 2 * 0.75;

	for (int hourCount = 0; hourCount < 12; hourCount++)
	{
		auto transformation = matrix::scaling(0, -extent, 0)
			.getRotated_z(M_PI * (hourCount / 6.0))
			.getTranslated(width / 2, height / 2, 0);

		auto transformed = transformation * p;
		c.setPixelAt(transformed.getX(), transformed.getY(), white);
	}

	auto ppm = image_formats::plain_ppm::write(c);
	image_formats::file_utility::overwrite("./cpp/src/exercises/clock_face/clock_face.ppm", ppm);

	return 0;
}
