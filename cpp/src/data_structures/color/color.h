#pragma once

namespace data_structures
{
class color
{
public:
	color()
		: _red { 0 }
		, _green { 0 }
		, _blue { 0 }
		{}

	color(float red, float green, float blue)
		: _red { red }
		, _green { green }
		, _blue { blue }
		{}

	float getRed() { return _red; }
	float getGreen() { return _green; }
	float getBlue() { return _blue; }

	bool operator==(const color & other) const;
	bool operator!=(const color & other) const;

	color operator+(const color & other) const;
	color operator-(const color & other) const;

	color operator*(float scalar) const;
	color operator*(const color & other) const;

private:
	float _red;
	float _green;
	float _blue;
};
} // namespace data_structures
