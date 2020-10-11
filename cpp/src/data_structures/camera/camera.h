#pragma once

#include "../canvas/canvas.h"
#include "../matrix/matrix.h"
#include "../ray/ray.h"
#include "../world/world.h"

namespace data_structures
{
class camera
{
public:
	camera(int hsize, int vsize, double fieldOfView, matrix transform);

int getHsize() { return _hsize; }
int getVsize() { return _vsize; }
double getFieldOfView() { return _fieldOfView; }
double getHalfWidth() { return _halfWidth; }
double getHalfHeight() { return _halfHeight; }
double getPixelSize() { return _pixelSize; }
matrix getTransform() { return _transform; }

ray getRayForPixel(int x, int y) const;
canvas render(world world) const;

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
