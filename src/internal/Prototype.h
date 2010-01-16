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

#include "internal/ProtoFieldDef.h"
#include "internal/ProtoField.h"
#include "internal/ProtoInst.h"
#include "internal/Connect.h"

#include <list>
#include <vector>
#include <string>
#include <map>

using std::list;
using std::vector;
using std::string;
using std::map;

namespace X3D {

class Node;
class Route;

class Prototype {
    friend class ProtoInst;
protected:

    vector<Node*> nodes;
    list<Route*> routes;
    map<string, Node*> defs;
    map<string, ProtoField*> fields;
    map<string, ProtoField*> in_fields;
    map<string, ProtoField*> out_fields;
    vector<ProtoField*> field_list;

private:
    
    int tempCounter;
    void deleteRoutes();
    void deleteNodes();

protected:

    virtual void setRootNode(Node* node) = 0;
    virtual Node* getRootNode() const = 0;
    string createTempName();

public:
    
    const string name;

    Prototype(const string& name) : name(name), tempCounter(0) {}
    virtual ~Prototype();

    void addNode(Node* node);
    void addField(ProtoField* field);
    void addConnection(Route* route);
    void addInternalRoute(Route* route);
    void addRoute(const string& fromNode, const string& fromField,
                  const string& toNode, const string& toField);
    virtual ProtoInst* createInstance() = 0;

public:

    static Prototype* create(
            const string& name,
            vector<Node*>& body,
            vector<Connect>& connects,
            vector<ProtoFieldDef*>& fields);
};

template <class N>
class PrototypeImpl : public Prototype {
private:
    
    N* root;

public:

    PrototypeImpl(const string& name) : Prototype(name) {}
    ~PrototypeImpl() { delete root; }

    virtual void setRootNode(Node* node) {
        N* n = dynamic_cast<N*>(node);
        if (n == NULL)
            throw X3DError("wrong root node for prototype", node);
        root = n;
    }

    virtual Node* getRootNode() const {
        return root;
    }

    virtual ProtoInstImpl<N>* createInstance() {
        return new ProtoInstImpl<N>(root, this);
    }
};

}

#endif // #ifndef _X3D_PROTOTYPE_H_
