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

	float getX() { return _x; }
	float getY() { return _y; }
	float getZ() { return _z; }
	int getW() { return _w; }

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
	four_tuple(float x, float y, float z, int w)
		: _x{x}
		, _y{y}
		, _z{z}
		, _w{w}
		{};

	float _x;
	float _y;
	float _z;
	int _w;
};
} // namespace data_structures
