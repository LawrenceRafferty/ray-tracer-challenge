#pragma once

namespace data_structures
{
class four_tuple
{
public:
	static four_tuple point(float x, float y, float z)
	{
		return four_tuple(x, y, z, 1);
	}

	static four_tuple vector(float x, float y, float z)
	{
		return four_tuple(x, y, z, 0);
	}

	four_tuple(float x, float y, float z, float w)
		: _x{x}
		, _y{y}
		, _z{z}
		, _w{w}
		{};

	float getX() const { return _x; }
	float getY() const { return _y; }
	float getZ() const { return _z; }
	float getW() const { return _w; }

	float getMagnitude() const;
	four_tuple getNormalized() const;

	float dot(const four_tuple & other) const;
	four_tuple cross(const four_tuple & other) const;

	bool operator==(const four_tuple & other) const;
	bool operator!=(const four_tuple & other) const;

	four_tuple operator+(const four_tuple & other) const;
	four_tuple operator-(const four_tuple & other) const;

	four_tuple operator-() const;

	four_tuple operator*(float scalar) const;
	four_tuple operator/(float scalar) const;

private:
	float _x;
	float _y;
	float _z;
	float _w;
};
} // namespace data_structures
