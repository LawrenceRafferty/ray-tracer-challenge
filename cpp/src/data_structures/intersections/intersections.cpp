#include "./intersections.h"

using data_structures::world;
using shapes::sphere;

namespace data_structures
{
intersections intersections::find(std::shared_ptr<const sphere> object, const ray &r)
{
	auto tValues = object->intersect(r);
	auto tValuesWithTheirObject = std::vector<intersection>();
	for (auto tValue : tValues)
		tValuesWithTheirObject.emplace_back(intersection(tValue, object));

	return intersections { std::move(tValuesWithTheirObject) };
}

intersections intersections::find(const world & w, const ray & r)
{
	auto tValuesWithTheirObject = std::vector<intersection>();
	for (auto object : w.getObjects())
	{
		auto tValues = object->intersect(r);
		for (auto tValue : tValues)
			tValuesWithTheirObject.emplace_back(intersection(tValue, object));
	}

	std::sort(tValuesWithTheirObject.begin(), tValuesWithTheirObject.end());
	return intersections { std::move(tValuesWithTheirObject) };
}

intersections::intersections(std::vector<intersection> intersections)
	: _intersections { std::move(intersections) }
	{}

intersections::intersections(std::initializer_list<intersection> intersections)
	: _intersections { std::vector<intersection>(intersections) }
	{}

int intersections::size() const { return _intersections.size(); }

intersection intersections::at(int index) const { return _intersections.at(index); }

std::unique_ptr<const intersection> intersections::getHit() const
{
	std::unique_ptr<const intersection> hit = nullptr;
	for (const intersection & i : _intersections)
	{
		if (i.isHitCandidate() && (hit == nullptr || i < *hit))
			hit = std::make_unique<intersection>(i);
	}

	return std::move(hit);
}
} // namespace data_structures
