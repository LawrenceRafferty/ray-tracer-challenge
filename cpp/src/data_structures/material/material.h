#pragma once

#include "../color/color.h"

namespace data_structures
{
class material
{
public:
	material();

	const color & getColor() const;
	void setColor(const color & color);

	float getAmbient() const;
	void setAmbient(float ambient);

	float getDiffuse() const;
	void setDiffuse(float diffuse);

	float getSpecular() const;
	void setSpecular(float specular);

	float getShininess() const;
	void setShininess(float shininess);

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
