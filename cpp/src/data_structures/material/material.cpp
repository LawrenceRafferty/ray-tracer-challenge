#include "./material.h"

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
float material::getAmbient() const { return _ambient; }
float material::getDiffuse() const { return _diffuse; }
float material::getSpecular() const { return _specular; }
float material::getShininess() const { return _shininess; }
} // namespace data_structures
