#include "./material.h"
#include "../../float_utility.cpp"

namespace data_structures
{
material::material()
	: _color { color(1, 1, 1) }
	, _ambient { 0.1f }
	, _diffuse { 0.9f }
	, _specular { 0.9f }
	, _shininess { 200.0f }
	{}

const color & material::getColor() const { return _color; }
void material::setColor(const color & color) { _color = color; }

float material::getAmbient() const { return _ambient; }
void material::setAmbient(float ambient) { _ambient = ambient; }

float material::getDiffuse() const { return _diffuse; }
void material::setDiffuse(float diffuse) { _diffuse = diffuse; }

float material::getSpecular() const { return _specular; }
void material::setSpecular(float specular) { _specular = specular; }

float material::getShininess() const { return _shininess; }
void material::setShininess(float shininess) { _shininess = shininess; } 

bool material::operator==(const material & other) const
{
	return _color == other._color &&
		float_utility::are_equivalent(_ambient, other._ambient) &&
		float_utility::are_equivalent(_diffuse, other._diffuse) &&
		float_utility::are_equivalent(_specular, other._specular) &&
		float_utility::are_equivalent(_shininess, other._shininess);
}

bool material::operator!=(const material & other) const
{
	return !(*this == other);
}
} // namespace data_structures
