#include "internal/Node.h"
#include "internal/Browser.h"

// XXX
#include <iostream>
using std::cout;
using std::endl;

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

void Node::queue(SAIField* field) {
    browser()->addDirtyField(field);
}

const string& Node::defaultContainerField() {
    throw X3DError("no default container field defined");
}

bool Node::parseSpecial(xmlNode* xml, const string& filename) {
    return false;
}

}
