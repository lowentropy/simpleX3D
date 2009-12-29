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

#include "internal/SAIField.h"
#include "internal/FieldDef.h"
#include "internal/Node.h"
#include "internal/Route.h"
#include "internal/SFNode.h"
#include "internal/MF.h"

using std::map;

namespace X3D {

X3DField::Type SAIField::getType() const {
    return definition->type;
}

const string& SAIField::getTypeName() const {
    return X3DField::getTypeName(definition->type);
}

const string& SAIField::getName() const {
    return definition->name;
}

SAIField* SAIField::cloneInto(Node* node, map<Node*,Node*>* mapping, bool shallow) {
    SAIField* target = definition->getField(node);
    if (!shallow && (definition->type == X3DField::SFNODE)) {
        SFAbstractNode& wrapper = static_cast<SFAbstractNode&>(target->get());
        Node* source = SFNode<Node>::unwrap(get());
        wrapper.set(source->clone(mapping, shallow));
    } else if (!shallow && (definition->type == X3DField::MFNODE)) {
        MFAbstractNode& fromList = MFAbstractNode::unwrap(get());
        MFAbstractNode& toList = MFAbstractNode::unwrap(target->get());
        fromList.cloneInto(toList, mapping, shallow);
    } else target->set(get());
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
