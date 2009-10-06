#include "Core/X3DNode.h"
#include "internal/Browser.h"

namespace X3D {
namespace Core {

void X3DNode::assignMetadata(const map<string,string>& meta, bool quiet) {
	if (metadata == NULL)
		set("metadata", browser()->createNode("MetadataSet"), quiet);
	metadata->assignFromMap(meta, quiet);
}

Browser* X3DNode::browser() {
	return Browser::getSingleton();
}

void X3DNode::set(const string& field, const SafePointer& value, bool quiet) {
	definition->set(this, field, value, quiet);
}

SafePointer X3DNode::get(const string& field) const {
	return definition->get(this, field);
}

void X3DNode::changed(const string& field) const {
	return definition->changed(this, field);
}

}}
