#pragma once

#include "./lighting.h"
#include <cmath>

using data_structures::color;
using data_structures::four_tuple;
using shapes::shape;

namespace lights
{
color lighting(
	const shape & shape,
	const point_light & light,
	const four_tuple & point,
	const four_tuple & eyev,
	const four_tuple & normalv,
	bool isShadowed)
{
	auto effectiveColor = shape.getColorAtPoint(point) * light.getIntensity();
	auto material = shape.getMaterial();
	color ambient = effectiveColor * material.getAmbient();
	if (isShadowed)
		return ambient;

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
