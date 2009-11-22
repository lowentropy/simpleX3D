#include "internal/SFNode.h"
#include "internal/Browser.h"

namespace X3D {

Node* SFAbstractNode::getNodeByName(const string& name) {
    Browser* browser = Browser::getSingleton();
    return browser->getNodeByName(name);
}

}
