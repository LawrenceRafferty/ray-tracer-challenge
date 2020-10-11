#pragma once

#include "../matrix/matrix.h"

namespace data_structures
{
class camera
{
public: camera(int hsize, int vsize, double fieldOfView);

int getHsize() { return _hsize; }
int getVsize() { return _vsize; }
double getFieldOfView() { return _fieldOfView; }
double getHalfWidth() { return _halfWidth; }
double getHalfHeight() { return _halfHeight; }
double getPixelSize() { return _pixelSize; }
matrix getTransform() { return _transform; }

private:
	int _hsize;
	int _vsize;
	double _fieldOfView;
	double _halfWidth;
	double _halfHeight;
	double _pixelSize;
	matrix _transform;
};
}
