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

#ifndef _X3D_PROTOINST_H_
#define _X3D_PROTOINST_H_

#include "Core/X3DPrototypeInstance.h"

#include <map>
#include <string>
#include <vector>
using std::map;
using std::string;
using std::vector;

namespace X3D {

class Prototype;
class Node;
class Route;

class ProtoInst : virtual public Core::X3DPrototypeInstance {
protected:

    map<string, Node*> defs;
    vector<Node*> nodes;
    vector<Route*> routes;

public:

    const Prototype* const proto;
    ProtoInst(const Prototype* proto) : proto(proto) {}

protected:

    void instantiateFromProto(Node* root);

private:

    void copyNode(const Node* from, Node* to);
};

template <class N>
class ProtoInstImpl : public ProtoInst, virtual public N {
public:

    ProtoInstImpl(N* root, const Prototype* proto) : ProtoInst(proto) {
        instantiateFromProto(root);
    }
};

}
#endif // #ifndef _X3D_PROTOINST_H_
