#include "./intersections.h"

namespace data_structures
{
	intersections intersections::find(std::shared_ptr<const sphere> object, const ray & r)
	{
		auto tValues = object->intersect(r);
		auto tValuesWithTheirObject = std::vector<intersection>();
		for (auto tValue : tValues)
			tValuesWithTheirObject.emplace_back(intersection(tValue, object));

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
}
