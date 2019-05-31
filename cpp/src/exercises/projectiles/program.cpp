#include "../../data_structures/canvas/canvas.h"
#include "../../data_structures/color/color.cpp"
#include "../../data_structures/four_tuple/four_tuple.cpp"
#include "../../image_formats/file_utility.cpp"
#include "../../image_formats/ppm/plain_ppm.cpp"

using data_structures::canvas;
using data_structures::color;
using data_structures::four_tuple;

struct projectile
{
	projectile(four_tuple p, four_tuple v)
	: position { p }
	, velocity { v }
	{}

	four_tuple position;
	four_tuple velocity;
};

struct environment
{
	environment(four_tuple g, four_tuple w)
	: gravity { g }
	, wind { w }
	{}

	four_tuple gravity;
	four_tuple wind;
};

projectile tick(environment e, projectile p)
{
	auto position = p.position + p.velocity;
	auto velocity = p.velocity + e.gravity + e.wind;
	return projectile(position, velocity);
}

void shootCannon(canvas & c, int multiplier)
{
	auto canvasWidth = c.getWidth();
	auto canvasHeight = c.getHeight();

	auto red = color(1, 0, 0);
	auto green = color (0, 1, 0);
	auto blue = color(0, 0, 1);
	auto yellow = red + green;
	auto orange = color(1, 0.8, 0);
	auto purple = red + blue;
	auto cyan = green + blue;
	auto rainbow = std::vector<color> { red, orange, yellow, green, cyan, blue, purple };
	auto shotColor = rainbow[(multiplier - 1) % rainbow.size()];

	auto p = projectile(four_tuple::point(0, 1, 0), four_tuple::vector(1, 1, 0).getNormalized() * multiplier);
	auto e = environment(four_tuple::vector(0, -0.1, 0), four_tuple::vector(-0.01, 0, 0));

	int ticks = 0;
	while (p.position.getY() > 0)
	{
		p = tick(e, p);
		ticks++;
		auto position = p.position;
		auto x = position.getX();
		auto y = canvasHeight - position.getY();
		if (x <= canvasWidth && y >= 0 && y <= canvasHeight)
			c.setPixelAt(x, y, shotColor);
	}
}

int main()
{
	auto c = canvas(640, 480);

	for (auto multiplier = 1; multiplier <= 7; multiplier++)
		shootCannon(c, multiplier);

	auto ppm = image_formats::plain_ppm::write(c);
	image_formats::file_utility::overwrite("./cpp/src/exercises/projectiles/projectiles.ppm", ppm);

	return 0;
}
