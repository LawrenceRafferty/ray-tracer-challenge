#include <algorithm>
#include <cmath>
#include <sstream>
#include "../../data_structures/canvas/canvas.h"

using data_structures::canvas;

namespace image_formats
{
namespace plain_ppm
{
void writeHeader(std::stringstream & ppm, const canvas & c)
{
	ppm
		<< "P3\n"
		<< c.getWidth() << " " << c.getHeight() << "\n"
		<< "255\n";
}

int getColorComponent(float rgb)
{
	return std::max(0, std::min(255, static_cast<int>(std::round(255 * rgb))));
}

void writeColorComponent(std::stringstream & ppm, int colorComponent, int & lineLength)
{
	int colorComponentLength = colorComponent <= 9 ? 1 : colorComponent <= 99 ? 2 : 3;
	const int maxLineLength = 70;

	if (lineLength == 0)
	{
		ppm << colorComponent;
		lineLength = colorComponentLength;
	}
	else if (lineLength + 1 + colorComponentLength > maxLineLength)
	{
		ppm << "\n" << colorComponent;
		lineLength = colorComponentLength;
	}
	else
	{
		ppm << " " << colorComponent;
		lineLength += 1 + colorComponentLength;
	}
}

void writePixels(std::stringstream & ppm, const canvas & c)
{
	int lineLength = 0;
	auto width = c.getWidth();
	auto height = c.getHeight();
	for (int y = 0; y < height; y++)
	{
		if (y != 0)
		{
			ppm << "\n";
			lineLength = 0;
		}

		for (int x = 0; x < width; x++)
		{
			auto pixel = c.getPixelAt(x, y);
			auto redComponent = getColorComponent(pixel.getRed());
			writeColorComponent(ppm, redComponent, lineLength);
			auto greenComponent = getColorComponent(pixel.getGreen());
			writeColorComponent(ppm, greenComponent, lineLength);
			auto blueComponent = getColorComponent(pixel.getBlue());
			writeColorComponent(ppm, blueComponent, lineLength);
		}
	}
}

std::string write(const canvas & c)
{
	std::stringstream ppm;
	writeHeader(ppm, c);
	writePixels(ppm, c);
	ppm << "\n";
	return ppm.str();
}
} // namespace plain_ppm
} // namespace image_formats
