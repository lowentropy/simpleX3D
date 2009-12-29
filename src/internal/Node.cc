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

void Node::cloneInto(Node* target, map<Node*,Node*>* mapping, bool shallow) {
    if (mapping != NULL)
        (*mapping)[this] = target;
    FieldIterator it = fields(FieldIterator::CAN_INIT);
    while (it.hasNext())
        it.nextField()->cloneInto(target, mapping, shallow);
}

Node* Node::clone(map<Node*,Node*>* mapping, bool shallow) {
    Node* clone = definition->create();
    cloneInto(clone, mapping, shallow);
    return clone;
}

const string& Node::defaultContainerField() {
    static string empty = "";
    return empty;
}

bool Node::parseSpecial(xmlNode* xml, const string& filename) {
    return false;
}

}
