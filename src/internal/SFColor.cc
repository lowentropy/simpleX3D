#include "internal/types.h"


namespace X3D {


std::ostream& operator<<(std::ostream& str, const SFColor& c) {
	str << "(" << c.r << ", " << c.g << ", " << c.b << ")";
	return str;
}


std::ostream& operator<<(std::ostream& str, const SFColorRGBA& c) {
	str << "(" << c.r << ", " << c.g << ", " << c.b << ", " << c.a << ")";
	return str;
}


}
