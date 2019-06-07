#pragma once

#include <cmath>
#include "../data_structures/color/color.h"
#include "../data_structures/four_tuple/four_tuple.h"
#include "../data_structures/material/material.h"
#include "./point_light/point_light.h"

using data_structures::color;
using data_structures::four_tuple;
using data_structures::material;

namespace lights
{
color lighting(const material & material, const point_light & light, const four_tuple & point, const four_tuple & eyev, const four_tuple & normalv)
{
	auto effectiveColor = material.getColor() * light.getIntensity();
	color ambient = effectiveColor * material.getAmbient();
	color diffuse;
	color specular;

	auto lightv = (light.getPosition() - point).getNormalized();
	auto lightDotNormal = lightv.dot(normalv);
	if (lightDotNormal < 0)
	{
		diffuse = color(0, 0, 0);
		specular = color(0, 0, 0);
	}
	else
	{
		diffuse = effectiveColor * material.getDiffuse() * lightDotNormal;
		auto reflectv = (-lightv).getReflected(normalv);
		auto reflectDotEye = reflectv.dot(eyev);

		if (reflectDotEye <= 0)
		{
			specular = color(0, 0, 0);
		}
		else
		{
			float factor = pow(reflectDotEye, material.getShininess());
			specular = light.getIntensity() * material.getSpecular() * factor;
		}
	}

	return ambient + diffuse + specular;
}
} // namespace lights
