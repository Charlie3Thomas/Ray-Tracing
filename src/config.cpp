#include "config.h"
#include "utils.h"

std::ostream& operator << (std::ostream& os, const image_t& image)
{
	os << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n" << (int)unstd::unsigned_max<colour_t::value_type>() << "\n";
	for (const colour_t& i : image) { os << i; }
	os << "\n";

	return os;
}