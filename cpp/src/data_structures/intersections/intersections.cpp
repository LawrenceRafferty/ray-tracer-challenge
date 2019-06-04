#include "./intersections.h"

namespace data_structures
{
	intersections::intersections(std::initializer_list<intersection> intersections)
		: _intersections { std::vector<intersection>(intersections) }
		{}

	int intersections::size() const { return _intersections.size(); }

	intersection intersections::at(int index) const { return _intersections.at(index); }
}
