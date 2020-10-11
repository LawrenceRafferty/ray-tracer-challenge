#include "./camera.h"
#include <cmath>

namespace data_structures
{
	camera::camera(
		int hsize,
		int vsize,
		double fieldOfView,
		matrix transform = matrix
		{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		})
		: _hsize { hsize },
		_vsize { vsize },
		_fieldOfView { fieldOfView },
		_transform { transform }
	{
		auto halfView = tan(fieldOfView / 2);
		auto aspect = hsize / vsize;
		if (aspect >= 1.0)
		{
			_halfWidth = halfView;
			_halfHeight = halfView / aspect;
		}
		else
		{
			_halfWidth = halfView * aspect;
			_halfHeight = halfView;
		}

		// ASSUME: pixels are square, so we only need to consider one dimension
		_pixelSize = (_halfWidth * 2) / hsize;
	}

	ray camera::getRayForPixel(int x, int y) const {
		// the offset from the edge of the canvas to the pixel's center
		auto xOffset = (x + 0.5) * _pixelSize;
		auto yOffset = (y + 0.5) * _pixelSize;

		// the untransformed coordinates of the pixel in world space
		// (remember that the camera looks toward -z, so +x is to the *left*)
		auto worldX = _halfWidth - xOffset;
		auto worldY = _halfHeight - yOffset;

		// using the camera matrix, transform the canvas point and the origin,
		// and then compute the ray's direction vector
		// (remember that hte canvas is at z=-1)
		auto inverseTransform = _transform.getInverse();
		auto pixel = inverseTransform * four_tuple::point(worldX, worldY, -1);
		auto origin = inverseTransform * four_tuple::point(0, 0, 0);
		auto direction = (pixel - origin).getNormalized();
		return ray(origin, direction);
	}
} // namespace camera
