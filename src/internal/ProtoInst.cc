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
    list<Route*>::iterator names;
    for (names = proto->routeNames.begin(); names != proto->routeNames.end(); names) {
        Node* from = defs[names->fromNode];
        Node* to = defs[names->toNode];
        Route* route = new Route(from, names->fromField, to, names->toField);
        routes.push_back(route);
    }
    // TODO: delete nodes and routes on proto and protoinst destructors
}

}
