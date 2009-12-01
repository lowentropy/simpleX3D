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

namespace X3D {

void Prototype::addNode(Node* node) {
    nodes.push_back(node);
}

void Prototype::addField(ProtoField* field) {
    // TODO
}

void Prototype::addConnection(Route* route) {
    // TODO
}

void Prototype::addInternalRoute(Route* route) {
    // TODO
}

Prototype* Prototype::create(const string& name, Node* root) {
  Prototype* proto = root->definition->createPrototype(name);
  proto->setRootNode(root);
  return proto;
}

}
