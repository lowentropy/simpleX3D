#include "Core/MetadataString.h"

namespace X3D {
namespace Core {

void MetadataString::assignFromString(const string& str, bool quiet) {
	set("value", str, quiet);
}

}}
