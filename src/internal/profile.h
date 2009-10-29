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

#ifndef _X3D_PROFILE_H_
#define _X3D_PROFILE_H_

#include <map>
#include <vector>
#include "internal/fields.h"

using std::map;
using std::vector;
using std::string;

namespace X3D {

class Profile;
class Component;
class NodeDefinition;


class Profile {
private:
	map<string, Component*> comp_map;
	vector<Component*> comp_list;

public:
	Profile() {}
	virtual ~Profile();

	Component* createComponent(const string& name);
	NodeDefinition* getNode(const string& name);
	virtual void print();
};

class FieldDef {
public:
	NodeDef* const nodeDef;
	const string name;
	const X3DField::Type type;
	const X3DField::Access access;

	FieldDef(
		NodeDef* nodeDef,
		const string& name,
		X3DField::Type type,
		X3DField::Access access) :
		nodeDef(nodeDef),
		name(name),
		type(type),
		access(access) {}
	
};

template <class N>
class FieldDefImpl : public FieldDef {
public:
	Field(N::*const field);

	FieldDefImpl(
		NodeDef* nodeDef,
		const string& name,
		X3DField::Type type,
		X3DField::Access access,
		Field (N::*field)) :
		FieldDef(nodeDef, name, type, access),
		field(field) {}
};

class NodeDef {
private:
	map<string, FieldDef*> fields;
	NodeDef* parent;

	friend class Browser;

public:
	Component* const component;
	const string name;
	const bool abstract;

	NodeDefinition(Component* component, const string& name, bool abstract) :
		component(component), name(name), parent(NULL), abstract(abstract) {}
	virtual ~NodeDefinition();

	void inherits(const string& name);
	virtual void print(bool full = true);

protected:

	virtual Node* create() = 0;
	template <class N> N* create() {
		if (abstract)
			throw X3DError("can't instantiate abstract nodes");
		return new N(this);
	}

	void addField(FieldDef* field);
	void print_fields(bool full);
};


template <class N>
class NodeDefImpl : public NodeDef {
public:
	friend class Browser;

	NodeDefImpl(Component* comp, const string& name, bool abstract) :
		NodeDefinition(comp, name, abstract) {}

protected:

	N* create() {
		return NodeDefinition::create<N>();
	}

public:

	FieldDef* createField(const string& name, X3DField::Type type, X3DField::Access access, Field (N::*ptr)) {
		FieldDef* def = new FieldDefImpl<N>(this, name, type, access, ptr);
		addField(def);
		return def;
	}
};

class Component {
private:
	map<string, NodeDefinition*> node_map;
	vector<NodeDefinition*> node_list;

public:
	const string name;

	Component(const string& name) : name(name) {}
	virtual ~Component();

	NodeDefinition* getNode(const string& name);
	virtual void print();

	template <class T> NodeDefImpl<T>* createNode(const string& name, bool abstract=false) {
		NodeDefinitionImpl<T>* def = new NodeDefinitionImpl<T>(this, name, abstract);
		node_map[name] = def;
		node_list.push_back(def);
		return def;
	}

};

}

#endif // #ifndef _X3D_PROFILE_H_
