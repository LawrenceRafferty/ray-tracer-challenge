#include <iostream>
#include "../../data_structures/four_tuple/four_tuple.cpp"

struct projectile
{
	projectile(data_structures::four_tuple p, data_structures::four_tuple v)
	: position { p }
	, velocity { v }
	{}

	data_structures::four_tuple position;
	data_structures::four_tuple velocity;
};

struct environment
{
	environment(data_structures::four_tuple g, data_structures::four_tuple w)
	: gravity { g }
	, wind { w }
	{}

	data_structures::four_tuple gravity;
	data_structures::four_tuple wind;
};

projectile tick(environment e, projectile p)
{
	auto position = p.position + p.velocity;
	auto velocity = p.velocity + e.gravity + e.wind;
	return projectile(position, velocity);
}

int main()
{
	auto multiplier = 7;
	auto p = projectile(data_structures::four_tuple::point(0, 1, 0), data_structures::four_tuple::vector(1, 1, 0).getNormalized() * multiplier);
	auto e = environment(data_structures::four_tuple::vector(0, -0.1, 0), data_structures::four_tuple::vector(-0.01, 0, 0));

	int ticks = 0;
	while (p.position.getY() > 0)
	{
		p = tick(e, p);
		ticks++;
		auto position = p.position;
		std::cout << "(" << position.getX() << "," << position.getY() << "," << position.getZ() << ")\n";
	}

	std::cout << "ticks: " << ticks;

	return 0;
}
