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

std::string write(const canvas & c)
{
	std::stringstream ppm;
	writeHeader(ppm, c);
	return ppm.str();
}
} // namespace plain_ppm
} // namespace image_formats
