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

#ifndef _X3D_PROTOTYPE_H_
#define _X3D_PROTOTYPE_H_

#include "internal/errors.h"
#include "internal/ProtoField.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

namespace X3D {

class Node;
class Route;

class Prototype {
    friend class ProtoInst;
protected:

    virtual void setRootNode(Node* node) = 0;
    virtual Node* getRootNode() const = 0;
    vector<Node*> nodes;

public:
    
    const string name;

    Prototype(const string& name) : name(name) {}

    void addNode(Node* node);
    void addField(ProtoField* field);
    void addConnection(Route* route);
    void addInternalRoute(Route* route);
    virtual ProtoInst* createInstance() const = 0;

public:

    static Prototype* create(const string& name, Node* root);
};

template <class N>
class PrototypeImpl : public Prototype {
private:
    
    N* root;

public:

    PrototypeImpl(const string& name) : Prototype(name), N() {}

    virtual void setRootNode(Node* node) {
        N* n = dynamic_cast<N*>(node);
        if (n == NULL)
            throw X3DError("wrong root node for prototype", node);
        root = n;
    }

    virtual Node* getRootNode() const {
        return root;
    }

    virtual ProtoInstImpl<N>* createInstance() const {
        return new ProtoInstImpl<N>(root, this);
    }
};

}

#endif // #ifndef _X3D_PROTOTYPE_H_
