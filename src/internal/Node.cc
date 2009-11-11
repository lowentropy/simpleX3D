#include "internal/Node.h"
#include "internal/Browser.h"

namespace X3D {

Browser* Node::browser() {
	return Browser::getSingleton();
}

SAIField* Node::getField(const string& name) {
    return definition->getField(name, this);
}

FieldIterator Node::fields(FieldIterator::IterMode mode) {
    return FieldIterator(this, mode);
}

bool Node::eventSource() {
    return false;
}

}
