#pragma once

#include "../color/color.h"

namespace data_structures
{
class material
{
public:
	material();

	const color & getColor() const;
	float getAmbient() const;
	float getDiffuse() const;
	float getSpecular() const;
	float getShininess() const;

	bool operator==(const material & other) const;
	bool operator!=(const material & other) const;

private:
	color _color;
	float _ambient;
	float _diffuse;
	float _specular;
	float _shininess;
};
} // namespace data_structures
