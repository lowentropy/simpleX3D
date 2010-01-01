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
#include "internal/Browser.h"
#include "internal/Route.h"

namespace X3D {

void ProtoInst::instantiateFromProto(Node* root) {
    map<Node*,Node*> mapping;
    // copy root
    root->cloneInto(this, &mapping);
    vector<Node*>::const_iterator n_it;
    // copy siblings
    for (n_it = proto->nodes.begin(); n_it != proto->nodes.end(); n_it++)
        nodes.push_back((*n_it)->clone(&mapping));
    // copy routes
    list<Route*>::const_iterator r_it;
    for (r_it = proto->routes.begin(); r_it != proto->routes.end(); r_it++) {
        const Route* route = *r_it;
        Node* fromNode = mapping[route->fromField->getNode()];
        Node* toNode   = mapping[route->toField->getNode()];
        SAIField* fromField = route->fromField->definition->getField(fromNode);
        SAIField* toField   = route->toField->definition->getField(toNode);
        routes.push_back(new Route(fromField, toField));
    }
}

ProtoInst::~ProtoInst() {
    deleteRoutes();
    deleteNodes();
}

void ProtoInst::deleteRoutes() {
    vector<Route*>::iterator it;
    for (it = routes.begin(); it != routes.end(); it++)
        delete *it;
}

void ProtoInst::deleteNodes() {
    vector<Node*>::iterator it;
    for (it = nodes.begin(); it != nodes.end(); it++)
        delete *it;
}

}
