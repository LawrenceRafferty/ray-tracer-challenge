#include "./transformations.h"

using data_structures::matrix;
using data_structures::four_tuple;

namespace transformations
{
	matrix getViewTransform(
		const four_tuple & fromPoint,
		const four_tuple & toPoint,
		const four_tuple & upVector
	)
	{
		auto forwardVector = (toPoint - fromPoint).getNormalized();
		auto leftVector = forwardVector.cross(upVector.getNormalized());
		auto trueUpVector = leftVector.cross(forwardVector);
		auto orientationMatrix = matrix
		{
			leftVector.getX(), leftVector.getY(), leftVector.getZ(), 0,
			trueUpVector.getX(), trueUpVector.getY(), trueUpVector.getZ(), 0,
			-forwardVector.getX(), -forwardVector.getY(), -forwardVector.getZ(), 0,
			0, 0, 0, 1
		};
		return orientationMatrix * matrix::translation(-fromPoint.getX(), -fromPoint.getY(), -fromPoint.getZ());
	}
}
