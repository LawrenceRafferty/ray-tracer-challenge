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
		double halfView = tan(fieldOfView / 2);
		double aspect = hsize / static_cast<double>(vsize);
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
		double xOffset = (x + 0.5) * _pixelSize;
		double yOffset = (y + 0.5) * _pixelSize;

		// the untransformed coordinates of the pixel in world space
		// (remember that the camera looks toward -z, so +x is to the *left*)
		double worldX = _halfWidth - xOffset;
		double worldY = _halfHeight - yOffset;

		// using the camera matrix, transform the canvas point and the origin,
		// and then compute the ray's direction vector
		// (remember that the canvas is at z=-1)
		auto inverseTransform = _transform.getInverse();
		auto pixel = inverseTransform * four_tuple::point(worldX, worldY, -1);
		auto origin = inverseTransform * four_tuple::point(0, 0, 0);
		auto direction = (pixel - origin).getNormalized();
		return ray(origin, direction);
	}

	canvas camera::render(world world) const {
		auto image = canvas(_hsize, _vsize);
		for (int y = 0; y <= _vsize - 1; y++)
		{
			for (int x = 0; x <= _hsize - 1; x++)
			{
				auto ray = getRayForPixel(x, y);
				auto color = world.getColorAt(ray);
				image.setPixelAt(x, y, color);
			}
		}

		return image;
	}
} // namespace camera
