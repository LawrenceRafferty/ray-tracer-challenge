#pragma once

#include <vector>
#include "../color/color.h"

namespace data_structures
{
class canvas
{
public:
	canvas(int width, int height)
		: _width { width }
		, _height { height }
		, _pixels { std::vector<color>(width * height) }
		{}

	int getWidth() const { return _width; }
	int getHeight() const { return _height; }

	color getPixelAt(int x, int y) const { return _pixels[x + (_width * y)]; }
	void setPixelAt(int x, int y, color c) { _pixels[x + (_width * y)] = c; }

private:
	int _width;
	int _height;
	std::vector<color> _pixels;
};
} // namespace data_structures
