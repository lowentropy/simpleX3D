#include "internal/Browser.h"

namespace X3D {

Browser* Browser::_inst;

Browser::Browser() : profile(new Profile()) {
	Builtin::init(profile);
}

Browser::~Browser() {
	list<X3DNode*>::iterator it = nodes.begin();
	for (; it != nodes.end(); it++)
		delete *it;
	delete profile;
}

X3DNode* Browser::createNode(const std::string& name) {
	NodeDefinition* def = profile->getNode(name);
	if (def == NULL)
		return NULL;
	X3DNode* node = def->create();
	if (node == NULL)
		return NULL;
	nodes.push_back(node);
	return node;
}

}
