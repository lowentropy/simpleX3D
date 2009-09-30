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

#ifndef _X3D_FIELDS_H_
#define _X3D_FIELDS_H_

#include "types.h"

namespace X3D {

class NodeDefinition;

class Field {
public:

	const NodeDefinition* node;
	const std::string name;
	const FieldType type;

	Field(
			NodeDefinition* node,
			const std::string& name,
			FieldType type) : 
		node(node), name(name), type(type) {
	}
};


class InitField : public Field {
public:

	InitField(
			NodeDefinition* node,
			const std::string& name,
			FieldType type) : 
		Field(node, name, type) {
	}

	virtual SafePointer get(const Core::X3DNode* node) const = 0;
};


template <class N, typename T>
class InitFieldImpl : public InitField {
private:

	typedef const T (N::*Variable);
	typedef T& (N::*Getter)() const;

	Variable var;
	Getter getter;

public:

	InitFieldImpl(
			NodeDefinition* node,
			const std::string& name,
			FieldType type,
			Variable var) :
		InitField(node, name, type),
		var(var), getter(NULL) {
	}

	InitFieldImpl(
			NodeDefinition* node,
			const std::string& name,
			FieldType type,
			Getter getter) :
		InitField(node, name, type),
		var(NULL), getter(getter) {
	}

	SafePointer get(const Core::X3DNode* node) const {
		return SafePointer(get_native(node->cast<N>()));
	}

	const T& get_native(const N* node) const {
		if (getter == NULL)
			return (node->*var);
		else
			return (node->*getter)();
	}
};


class InField : public Field {
public:

	InField(
			NodeDefinition* node,
			const std::string& name,
			FieldType type) :
		Field(node, name, type) {
	}

	virtual void set(Core::X3DNode* node, const SafePointer& ptr) const = 0;
};


template <class N, class T>
class InFieldImpl : public InField {
private:
	
	typedef void (N::*Receiver)(const T&);
	Receiver receive;

public:

	InFieldImpl(
			NodeDefinition* node,
			const std::string& name,
			FieldType type,
			Receiver receive) :
		InField(node, name, type),
		receive(receive) {
	}

	void set(Core::X3DNode* node, const SafePointer& ptr) const {
		set_native(node->cast<N>(), *ptr.cast<T>());
	}

	void set_native(N* node, const T& value) const {
		(node->*receive)(value);
	}
};


class OutField : public Field {
public:

	OutField(
			NodeDefinition* node,
			const std::string& name,
			FieldType type) :
		Field(node, name, type) {}
	
	virtual SafePointer get(const Core::X3DNode* node) const = 0;

protected:

	virtual void signal(Core::X3DNode* node, const SafePointer& ptr) const = 0;
};


template <class N, class T>
class OutFieldImpl : public OutField {
private:
	
	typedef T (N::*Variable);
	typedef T& (N::*Getter)() const;
	typedef void (N::*Setter)(const T&);

	Variable var;
	Getter getter;
	Setter setter;
	Setter changed;

public:

	OutFieldImpl(
			NodeDefinition* node,
			const std::string& name,
			FieldType type,
			Variable var,
			Setter changed=NULL) :
		OutField(node, name, type),
		var(var), getter(NULL), setter(NULL), changed(changed) {
	}
	
	OutFieldImpl(
			NodeDefinition* node,
			const std::string& name,
			FieldType type,
			Getter getter,
			Setter setter,
			Setter changed=NULL) :
		OutField(node, name, type),
		var(NULL), getter(getter), setter(setter), changed(changed) {
	}

	SafePointer get(const Core::X3DNode* node) const {
		return SafePointer(get_native(node->cast<N>()));
	}

	const T& get_native(const N* node) const {
		if (getter == NULL)
			return (node->*var);
		else
			return (node->*getter)();
	}

	void signal(Core::X3DNode* node, const SafePointer& ptr) const {
		signal_native(node->cast<N>(), *ptr.cast<T>());
	}

	void signal_native(N* node, const T& value) const {
		// signal action, if any
		if (changed != NULL)
			(node->*changed)(value);
		// set last known value
		if (setter == NULL)
			(node->*var) = value;
		else
			(node->*setter)(value);
	}
};


class InOutField : public Field {
public:

	InOutField(
			NodeDefinition* node,
			const std::string& name,
			FieldType type) :
		Field(node, name, type) {
	}

	virtual SafePointer get(const Core::X3DNode* node) const = 0;
	virtual void set(Core::X3DNode* node, const SafePointer& ptr) const = 0;
	virtual void signal(Core::X3DNode* node, const SafePointer& ptr) const = 0;
};

template <class N, class T>
class InOutFieldImpl : public InOutField {
private:

	typedef T (N::*Variable);
	typedef T& (N::*Getter)() const;
	typedef void (N::*Setter)(const T&);
	typedef void (N::*Receiver)(const T&);

	Variable var;
	Getter getter;
	Setter setter;
	Receiver receive;
	Setter changed;

public:

	InOutFieldImpl(
			NodeDefinition* node,
			const std::string& name,
			FieldType type,
			Variable var,
			Receiver receive,
			Setter changed) :
		InOutField(node, name, type),
		var(var), getter(NULL), setter(NULL),
		receive(receive), changed(changed) {
	}

	InOutFieldImpl(
			NodeDefinition* node,
			const std::string& name,
			FieldType type,
			Getter getter,
			Setter setter,
			Receiver receive,
			Setter changed) :
		InOutField(node, name, type),
		var(NULL), getter(getter), setter(setter),
		receive(receive), changed(changed) {
	}

	void set(Core::X3DNode* node, const SafePointer& ptr) const {
		set_native(node->cast<N>(), *ptr.cast<T>());
	}

	void set_native(N* node, const T& value) const {
		(node->*receive)(value);
	}

	SafePointer get(const Core::X3DNode* node) const {
		return SafePointer(get_native(node->cast<N>()));
	}

	const T& get_native(const N* node) const {
		if (getter == NULL)
			return (node->*var);
		else
			return (node->*getter)();
	}

	void signal(Core::X3DNode* node, const SafePointer& ptr) const {
		signal_native(node->cast<N>(), *ptr.cast<T>());
	}

	void signal_native(N* node, const T& value) const {
		// signal action, if any
		if (changed != NULL)
			(node->*changed)(value);
		// set last known value
		if (setter == NULL)
			(node->*var) = value;
		else
			(node->*setter)(value);
	}
};

}

#endif // #ifndef _X3D_FIELDS_H_
