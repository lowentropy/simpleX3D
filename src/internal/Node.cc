#include "internal/Browser.h"
#include "internal/Route.h"

namespace X3D {

Node::~Node() {
}

void Node::dispose() {
    FieldIterator it = fields(FieldIterator::ALL);
    while (it.hasNext())
        it.nextField()->dispose();
}

Browser* Node::browser() {
	return Browser::getSingleton();
}

double Node::now() {
    return Browser::getSingleton()->now();
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
    if (!name.empty())
        target->setName(name);
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

bool Node::isSensor() const {
    return false;
}

bool Node::isTimer() const {
    return false;
}

void Node::evaluate() {
    throw X3DError("ABSTRACT");
}

void Node::predict() {
    throw X3DError("ABSTRACT");
}

}
