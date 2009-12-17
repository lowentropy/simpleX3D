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

#include "internal/ProtoInst.h"

namespace X3D {

void ProtoInst::instantiateFromProto() {
    vector<Node*>::iterator n_it;
    for (n_it = proto->nodes.begin(); n_it != proto->nodes.end(); n_it++) {
        Node* node = (*n_it)->definition->create();
        browser()->copyNode(*n_it, node, defs);
    }
    list<Route*>::iterator r_it;
    for (r_it = proto->routes.begin(); r_it != proto->routes.end(); r_it++) {
        Route* route = *r_it;
        Node* fromNode = defs[route->from->getNode()->getName()];
        Node* toNode = defs[route->to->getNode()->getName()];
        SAIField* fromField = fromNode->getField(route->from->getName());
        SAIField* toField = toNode->getField(route->to->getName());
        routes.push_back(new Route(fromField, toField));
    }
    // TODO: delete nodes and routes on proto and protoinst destructors
}

}
