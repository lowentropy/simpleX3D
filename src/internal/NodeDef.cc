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

#include "internal/Component.h"
#include "internal/NodeDef.h"
#include "internal/Node.h"

#include <iostream>

using std::cout;
using std::endl;

namespace X3D {

NodeDef::~NodeDef() {
    list<FieldDef*>::iterator it;
    for (it = field_list.begin(); it != field_list.end(); it++)
        delete *it;
}

FieldDef* NodeDef::getFieldDef(const string& name) {
    if (fields.count(name))
        return fields[name];
    if (in_fields.count(name))
        return in_fields[name];
    if (out_fields.count(name))
        return out_fields[name];
    return NULL;
}

void NodeDef::inherits(const string& name) {
	NodeDef* parent = component->profile->getNode(name);
	if (parent == NULL)
		throw X3DError("can't set nonexistent parent: " + name);
    parents.push_back(parent);
    growChain(parent);
}

void NodeDef::finish() {
    chain.push_back(this);
    finished = true;
}

void NodeDef::growChain(NodeDef* def) {
    list<NodeDef*>::iterator c_it = chain.begin();
    for (; c_it != chain.end(); c_it++)
        if (*c_it == def)
            return;
    vector<NodeDef*>::iterator p_it = def->parents.begin();
    for (; p_it != def->parents.end(); p_it++)
        growChain(*p_it);
    chain.push_back(def);
}

void NodeDef::print(bool full) {
	cout << "\t" << name;
	if (parents.size() > 0)
		cout << " : " << parents[0]->name;
    for (int i = 1; i < parents.size(); i++)
        cout << ", " << parents[i]->name;
	cout << " {" << endl;
	print_fields(full);
	cout << "\t}" << endl;
}

void NodeDef::print_fields(bool full) {
    if (full) {
        list<NodeDef*>::iterator c_it;
        for (c_it = chain.begin(); c_it != chain.end(); c_it++) {
            NodeDef* def = *c_it;
            list<FieldDef*>::iterator f_it;
            for (f_it = def->field_list.begin(); f_it != def->field_list.end(); f_it++)
                (*f_it)->print();
        }
    } else {
        list<FieldDef*>::iterator f_it;
        for (f_it = field_list.begin(); f_it != field_list.end(); f_it++)
            (*f_it)->print();
    }
}

void NodeDef::setDefinition(Node* node) {
    node->definition = this;
}

void NodeDef::addField(FieldDef* field) {
    fields[field->name] = field;
    field_list.push_back(field);
    switch (field->access) {
        case SAIField::INPUT_ONLY:
            in_fields[field->name] = field;
            break;
        case SAIField::OUTPUT_ONLY:
            out_fields[field->name] = field;
            break;
        case SAIField::INPUT_OUTPUT:
            in_fields["set_" + field->name] = field;
            out_fields[field->name + "_changed"] = field;
            break;
    }
}

NodeDef* Component::getNode(const string& name) {
	return node_map[name];
}

}
