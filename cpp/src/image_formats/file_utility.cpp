#include <fstream>

namespace image_formats
{
	namespace file_utility
	{
		void overwrite(const std::string & filename, const std::string & data)
		{
			// TODO: use <filesystem> in the C++17 standard library for better path support
			std::ofstream outfile (filename, std::ofstream::trunc);
			outfile << data;
			outfile.flush();
		}
	}
}
