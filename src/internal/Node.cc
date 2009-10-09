#include "internal/Node.h"
#include "internal/Browser.h"

namespace X3D {

Browser* Node::browser() {
	return Browser::getSingleton();
}

void Node::set(const string& field, const SafePointer& value, bool quiet) {
	definition->set(this, field, value, quiet);
}

SafePointer Node::get(const string& field) const {
	return definition->get(this, field);
}

void Node::changed(const string& field) const {
	return definition->changed(this, field);
}

}
