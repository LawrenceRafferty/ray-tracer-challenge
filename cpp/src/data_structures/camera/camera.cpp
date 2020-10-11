#include "./camera.h"
#include <cmath>

namespace data_structures
{
	camera::camera(int hsize, int vsize, double fieldOfView)
		: _hsize { hsize },
		_vsize { vsize },
		_fieldOfView { fieldOfView },
		_transform
		{
			matrix
			{
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
			}
		}
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
} // namespace camera
