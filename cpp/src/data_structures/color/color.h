namespace data_structures
{
class color
{
public:
	color(float red, float green, float blue)
		: _red{red}, _green{green}, _blue{blue}
	{
	}

	float getRed() { return _red; }
	float getGreen() { return _green; }
	float getBlue() { return _blue; }

private:
	float _red;
	float _green;
	float _blue;
};
} // namespace data_structures
