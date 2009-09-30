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
#include "fields.h"

using std::map;
using std::string;

namespace X3D {

class NodeDefinition {
protected:

	map<string, InitField*> init_fields;
	map<string, InField*> in_fields;
	map<string, OutField*> out_fields;
	map<string, InOutField*> inout_fields;

public:

	const string name;
	NodeDefinition(const string& name) : name(name) {}
	void inherits(const string& name) {
		// TODO
	}
};


template <class N>
class NodeDefinitionImpl : public NodeDefinition {
public:

	NodeDefinitionImpl(const string& name) : NodeDefinition(name) {}

	template <typename T> InitFieldImpl<N,T>* createInitField(
			const string& name, 
			FieldType type,
			const T (N::*var)) {
		InitFieldImpl<N,T>* field = new InitFieldImpl<N,T>(
			this, name, type, var);
		init_fields[name] = field;
		return field;
	}

	template <typename T> InitFieldImpl<N,T>* createInitField(
			const string& name,
			FieldType type,
			T (N::*var)) {
		InitFieldImpl<N,T>* field = new InitFieldImpl<N,T>(
			this, name, type, var);
		init_fields[name] = field;
		return field;
	}

	template <typename T> InitFieldImpl<N,T>* createInitField(
			const string& name,
			FieldType type,
			void (N::*set_var)(const T&)) {
		InitFieldImpl<N,T>* field = new InitFieldImpl<N,T>(
			this, name, type, set_var);
		init_fields[name] = field;
		return field;
	}

	template <typename T> InFieldImpl<N,T>* createInputField(
			const string& name,
			FieldType type,
			void (N::*set_fp)(const T&)) {
		InFieldImpl<N,T>* field = new InFieldImpl<N,T>(
			this, name, type, set_fp);
		in_fields[name] = field;
		return field;
	}

	template <typename T> OutFieldImpl<N,T>* createOutputField(
			const string& name,
			FieldType type,
			const T (N::*var),
			void (N::*changed_fp)(const T&)=NULL) {
		OutFieldImpl<N,T>* field = new OutFieldImpl<N,T>(
			this, name, type, const_cast<T (N::*)>(var), changed_fp);
		out_fields[name] = field;
		return field;
	}

	template <typename T> OutFieldImpl<N,T>* createOutputField(
			const string& name,
			FieldType type,
			T (N::*var),
			void (N::*changed_fp)(const T&)=NULL) {
		OutFieldImpl<N,T>* field = new OutFieldImpl<N,T>(
			this, name, type, var, changed_fp);
		out_fields[name] = field;
		return field;
	}

	template <typename T> OutFieldImpl<N,T>* createOutputField(
			const string& name,
			FieldType type,
			T& (N::*get_var)() const,
			void (N::*set_var)(const T&),
			void (N::*changed_fp)(const T&)=NULL) {
		OutFieldImpl<N,T>* field = new OutFieldImpl<N,T>(
			this, name, type, get_var, set_var, changed_fp);
		out_fields[name] = field;
		return field;
	}

	template <typename T> InOutFieldImpl<N,T>* createInputOutputField(
			const string& name,
			FieldType type,
			const T (N::*var),
			void (N::*set_fp)(const T&)=NULL,
			void (N::*changed_fp)(const T&)=NULL) {
		InOutFieldImpl<N,T>* field = new InOutFieldImpl<N,T>(
			this, name, type, const_cast<T (N::*)>(var), set_fp, changed_fp);
		inout_fields[name] = field;
		return field;
	}

	template <typename T> InOutFieldImpl<N,T>* createInputOutputField(
			const string& name,
			FieldType type,
			T (N::*var),
			void (N::*set_fp)(const T&)=NULL,
			void (N::*changed_fp)(const T&)=NULL) {
		InOutFieldImpl<N,T>* field = new InOutFieldImpl<N,T>(
			this, name, type, var, set_fp, changed_fp);
		inout_fields[name] = field;
		return field;
	}

	template <typename T> InOutFieldImpl<N,T>* createInputOutputField(
			const string& name,
			FieldType type,
			T& (N::*get_var)() const,
			void (N::*set_var)(const T&),
			void (N::*set_fp)(const T&)=NULL,
			void (N::*changed_fp)(const T&)=NULL) {
		InOutFieldImpl<N,T>* field = new InOutFieldImpl<N,T>(
			name, type, get_var, set_var, set_fp, changed_fp);
		inout_fields[name] = field;
		return field;
	}
};


class Component {
private:

	map<string, NodeDefinition*> nodes;

public:

	const string name;

	Component(const string& name) : name(name) {}

	template <class T> NodeDefinitionImpl<T>* createNode(const string& name) {
		NodeDefinitionImpl<T>* def = new NodeDefinitionImpl<T>(name);
		nodes[name] = def;
		return def;
	}
};


class Profile {
private:

	map<string, Component*> components;

public:

	Component* createComponent(const string& name) {
		return components[name] = new Component(name);
	}
};


}

#endif // #ifndef _X3D_PROFILE_H_
