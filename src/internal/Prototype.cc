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

#include "internal/Prototype.h"
#include "internal/Node.h"
#include "internal/NodeDef.h"
#include "internal/Route.h"

#include <sstream>
using std::ostringstream;

namespace X3D {

string Prototype::createTempName() {
    ostringstream os;
    os << "_tmp_" << tempCounter++;
    return os.str();
}

void Prototype::addNode(Node* node) {
    nodes.push_back(node);
    if (!node->getName().empty())
        defs[node->getName()] = node;
}

void Prototype::addField(ProtoField* field) {
    field_list.push_back(field);
    fields[field->getName()] = field;
    // TODO
    // TODO: Prototype should contain fields of FieldDef
    // TODO: should have a component for a source file, such that
    //       all its prototypes exist together
}

void Prototype::addConnection(Route* route) {
    // TODO
}

void Prototype::addInternalRoute(Route* route) {
    // TODO
}

void Prototype::addRoute(const string& fromNode, const string& fromField,
                         const string& toNode, const string& toField) {
    if (!defs.count(fromNode))
        throw X3DError(string("prototype has no source node: ") + fromNode);
    if (!defs.count(toNode))
        throw X3DError(string("prototype has no target node: ") + toNode);
    Node* from = defs[fromNode];
    Node* to = defs[toNode];
    Route* route = new Route(from, fromField, to, toField);
    routes.push_back(route);
}

Prototype* Prototype::create(const string& name, Node* root) {
  Prototype* proto = root->definition->createPrototype(name);
  proto->setRootNode(root);
  return proto;
}

Prototype::~Prototype() {
    deleteRoutes();
    deleteNodes();
}

void Prototype::deleteRoutes() {
    list<Route*>::iterator it;
    for (it = routes.begin(); it != routes.end(); it++)
        delete *it;
}

void Prototype::deleteNodes() {
    vector<Node*>::iterator it;
    for (it = nodes.begin(); it != nodes.end(); it++)
        delete *it;
}

}
