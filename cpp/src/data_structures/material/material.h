#pragma once

#include "../../patterns/pattern.h"

namespace data_structures
{
class material
{
public:
	material();

	const patterns::pattern & getPattern() const;
	void setPattern(std::shared_ptr<patterns::pattern> pattern);

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
	std::shared_ptr<patterns::pattern> _pattern;
	float _ambient;
	float _diffuse;
	float _specular;
	float _shininess;
};
} // namespace data_structures
