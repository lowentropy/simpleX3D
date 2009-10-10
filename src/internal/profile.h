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


class NodeDefinition {
private:
	map<string, InitField*> init_fields;
	map<string, InField*> in_fields;
	map<string, OutField*> out_fields;
	map<string, InOutField*> inout_fields;
	vector<Field*> fields;
	NodeDefinition* parent;

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

	virtual SafePointer get(Node* node, const string& field) const;
	virtual void set(Node* node, const string& field, const SafePointer& value) const;
	virtual void changed(const Node* node, const string& field) const;

protected:

	virtual Node* create() = 0;
	template <class N> N* create() {
		if (abstract)
			throw X3DError("can't instantiate abstract nodes");
		return new N(this);
	}

	void addInitField(InitField* field);
	void addInField(InField* field);
	void addOutField(OutField* field);
	void addInOutField(InOutField* field);
	void print_fields(bool full);
};


template <class N>
class NodeDefinitionImpl : public NodeDefinition {
public:

	friend class Browser;

	NodeDefinitionImpl(Component* comp, const string& name, bool abstract) :
		NodeDefinition(comp, name, abstract) {}

protected:

	N* create() {
		return NodeDefinition::create<N>();
	}

public:

	template <typename T> InitFieldImpl<N,T>* createInitField(
			const string& name, 
			FieldType type,
			const T (N::*var)) {
		InitFieldImpl<N,T>* field = new InitFieldImpl<N,T>(
			this, name, type, var);
		addInitField(field);
		return field;
	}

	template <typename T> InitFieldImpl<N,T>* createInitField(
			const string& name,
			FieldType type,
			T (N::*var)) {
		InitFieldImpl<N,T>* field = new InitFieldImpl<N,T>(
			this, name, type, var);
		addInitField(field);
		return field;
	}

	template <typename T> InitFieldImpl<N,T>* createInitField(
			const string& name,
			FieldType type,
			T& (N::*get_var)() const) {
		InitFieldImpl<N,T>* field = new InitFieldImpl<N,T>(
			this, name, type, get_var);
		addInitField(field);
		return field;
	}

	template <typename T> InFieldImpl<N,T>* createInputField(
			const string& name,
			FieldType type,
			void (N::*set_fp)(const T&)) {
		InFieldImpl<N,T>* field = new InFieldImpl<N,T>(
			this, name, type, set_fp);
		addInField(field);
		return field;
	}

	template <typename T> OutFieldImpl<N,T>* createOutputField(
			const string& name,
			FieldType type,
			const T (N::*var),
			void (N::*changed_fp)()=NULL) {
		OutFieldImpl<N,T>* field = new OutFieldImpl<N,T>(
			this, name, type, const_cast<T (N::*)>(var), changed_fp);
		addOutField(field);
		return field;
	}

	template <typename T> OutFieldImpl<N,T>* createOutputField(
			const string& name,
			FieldType type,
			T (N::*var),
			void (N::*changed_fp)()=NULL) {
		OutFieldImpl<N,T>* field = new OutFieldImpl<N,T>(
			this, name, type, var, changed_fp);
		addOutField(field);
		return field;
	}

	template <typename T> OutFieldImpl<N,T>* createOutputField(
			const string& name,
			FieldType type,
			T& (N::*get_var)(),
			void (N::*set_var)(const T&),
			void (N::*changed_fp)()=NULL) {
		OutFieldImpl<N,T>* field = new OutFieldImpl<N,T>(
			this, name, type, get_var, set_var, changed_fp);
		addOutField(field);
		return field;
	}

	template <typename T> InOutFieldImpl<N,T>* createInputOutputField(
			const string& name,
			FieldType type,
			const T (N::*var),
			void (N::*set_fp)(const T&)=NULL,
			void (N::*changed_fp)()=NULL) {
		InOutFieldImpl<N,T>* field = new InOutFieldImpl<N,T>(
			this, name, type, const_cast<T (N::*)>(var), set_fp, changed_fp);
		addInOutField(field);
		return field;
	}

	template <typename T> InOutFieldImpl<N,T>* createInputOutputField(
			const string& name,
			FieldType type,
			T (N::*var),
			void (N::*set_fp)(const T&)=NULL,
			void (N::*changed_fp)()=NULL) {
		InOutFieldImpl<N,T>* field = new InOutFieldImpl<N,T>(
			this, name, type, var, set_fp, changed_fp);
		addInOutField(field);
		return field;
	}

	template <typename T> InOutFieldImpl<N,T>* createInputOutputField(
			const string& name,
			FieldType type,
			T& (N::*get_var)(),
			void (N::*set_var)(const T&),
			void (N::*set_fp)(const T&)=NULL,
			void (N::*changed_fp)()=NULL) {
		InOutFieldImpl<N,T>* field = new InOutFieldImpl<N,T>(
			name, type, get_var, set_var, set_fp, changed_fp);
		addInOutField(field);
		return field;
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

	template <class T> NodeDefinitionImpl<T>* createNode(const string& name, bool abstract=false) {
		NodeDefinitionImpl<T>* def = new NodeDefinitionImpl<T>(this, name, abstract);
		node_map[name] = def;
		node_list.push_back(def);
		return def;
	}

};

}

#endif // #ifndef _X3D_PROFILE_H_
