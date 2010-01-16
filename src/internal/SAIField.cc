/*
* Copyright 2009 Nathan Matthews <lowentropy@gmail.com>
*
* This file is part of SimpleX3D.
* 
* SimpleX3D is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* SimpleX3D is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with SimpleX3D.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "internal/Route.h"
#include "internal/MF.h"

using std::map;

namespace X3D {

SAIField::Access SAIField::getAccess(const string& name) {
    if (name == "initOnly")
        return SAIField::INIT_ONLY;
    else if (name == "inputOnly")
        return SAIField::INPUT_ONLY;
    else if (name == "outputOnly")
        return SAIField::OUTPUT_ONLY;
    else if (name == "inputOuypuy")
        return SAIField::INPUT_OUTPUT;
    throw X3DError(string("invalid access name: ") + name);
}

X3DField::Type SAIField::getType() const {
    return definition->type;
}

const string& SAIField::getTypeName() const {
    return X3DField::getTypeName(definition->type);
}

const string& SAIField::getName() const {
    return definition->name;
}

void deleteRoutes(const list<Route*>& routes) {
    while (!routes.empty()) {
        Route* route = routes.front();
        route->remove();
        delete route;
    }
}

void SAIField::dispose() {
    if (definition->inputCapable())
        deleteRoutes(getIncomingRoutes());
    if (definition->outputCapable())
        deleteRoutes(getOutgoingRoutes());
}

SAIField* SAIField::cloneInto(Node* node, map<Node*,Node*>* mapping, bool shallow) {
    SAIField* target = definition->getField(node);
    if (!shallow && (definition->type == X3DField::SFNODE)) {
        SFAbstractNode& wrapper = static_cast<SFAbstractNode&>(target->get());
        Node* source = SFNode<Node>::unwrap(getSilently());
        if (source == NULL)
            wrapper.set(NULL);
        else
            wrapper.set(source->clone(mapping, shallow));
    } else if (!shallow && (definition->type == X3DField::MFNODE)) {
        MFAbstractNode& fromList = MFAbstractNode::unwrap(getSilently());
        MFAbstractNode& toList = MFAbstractNode::unwrap(target->getSilently());
        fromList.cloneInto(toList, mapping, shallow);
    } else target->setSilently(getSilently());
    return target;
}

void SAIField::addIncomingRoute(Route* route) {
    throw X3DError("this field does not support incoming routes");
}

void SAIField::removeIncomingRoute(Route* route) {
    throw X3DError("this field does not support incoming routes");
}

const list<Route*>& SAIField::getIncomingRoutes() const {
    throw X3DError("this field does not support incoming routes");
}

void SAIField::addOutgoingRoute(Route* route) {
    throw X3DError("this field does not support outgoing routes");
}

void SAIField::removeOutgoingRoute(Route* route) {
    throw X3DError("this field does not support outgoing routes");
}

const list<Route*>& SAIField::getOutgoingRoutes() const {
    throw X3DError("this field does not support outgoing routes");
}

}
