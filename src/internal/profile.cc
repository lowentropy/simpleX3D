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

#include "internal/types.h"
#include "internal/profile.h"
#include "internal/Node.h"
#include <iostream>

using std::cout;
using std::endl;

namespace X3D {

NodeDef::~NodeDef() {
	map<string, FieldDef*>::iterator it = fields.begin();
	for (; it != fields.end(); it++)
		delete it->second;
}

void NodeDef::inherits(const string& name) {
	NodeDef* parent = component->profile->getNode(name);
	if (parent == NULL)
		throw X3DError("can't set nonexistent parent: " + name);
    parents.push_back(parent);
    growChain(parent);
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
        vector<NodeDef*>::iterator it = parents.begin();
        for (; it != parents.end(); it++)
            (*it)->print_fields(full);
    }
	map<string, FieldDef*>::iterator it = fields.begin();
	for (; it != fields.end(); it++)
		it->second->print();
}

void NodeDef::setDefinition(Node* node) {
    node->definition = this;
}

void NodeDef::addField(FieldDef* field) {
    fields[field->name] = field;
}

void FieldDef::print() {
    switch (access) {
        case X3DField::INIT_ONLY:
            cout << "[]";
            break;
        case X3DField::INPUT_ONLY:
            cout << "[in]";
            break;
        case X3DField::OUTPUT_ONLY:
            cout << "[out]";
            break;
        case X3DField::INPUT_OUTPUT:
            cout << "[in,out]";
            break;
    }
}

Component::~Component() {
	vector<NodeDef*>::iterator it = node_list.begin();
	for (; it != node_list.end(); it++)
		delete *it;
}

NodeDef* Component::getNode(const string& name) {
	return node_map[name];
}

void Component::print() {
	cout << "COMPONENT " << name << " {" << endl;
	vector<NodeDef*>::iterator it = node_list.begin();
	for (; it != node_list.end(); it++)
		(*it)->print();
	cout << "}" << endl;
}

Profile::~Profile() {
	vector<Component*>::iterator it = comp_list.begin();
	for (; it != comp_list.end(); it++)
		delete *it;
}

NodeDef* Profile::getNode(const string& name) {
	vector<Component*>::iterator it = comp_list.begin();
	for (; it != comp_list.end(); it++) {
		NodeDef* def = (*it)->getNode(name);
		if (def != NULL)
			return def;
	}
	return NULL;
}

Component* Profile::createComponent(const string& name) {
	Component* comp = new Component(this, name);
	comp_map[name] = comp;
	comp_list.push_back(comp);
	return comp;
}

void Profile::print() {
	cout << "PROFILE" << endl;
	vector<Component*>::iterator it = comp_list.begin();
	for (; it != comp_list.end(); it++)
		(*it)->print();
}

}
