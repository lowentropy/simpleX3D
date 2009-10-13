#include "internal/types.h"


namespace X3D {


std::ostream& operator<<(std::ostream& str, const SFColor& c) {
	str << "(" << ((int) c.r) << ", " << ((int) c.g) << ", " << ((int) c.b) << ")";
	return str;
}


std::ostream& operator<<(std::ostream& str, const SFColorRGBA& c) {
	str << "(" << ((int)c.r) << ", " << ((int)c.g) << ", " << ((int)c.b) << ", " << ((int)c.a) << ")";
	return str;
}


}
