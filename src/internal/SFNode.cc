#include "internal/SFNode.h"
#include "internal/Browser.h"

namespace X3D {

Node* SFAbstractNode::getNode(const string& name) {
    Browser* browser = Browser::getSingleton();
    return browser->getNode(name);
}

}
