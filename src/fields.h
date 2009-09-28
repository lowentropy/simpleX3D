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

namespace X3D {

namespace Core {
	class X3DNode;
}

class Field {
public:
	Core::X3DNode* const node;
public:
	Field(Core::X3DNode* node) : node(node) {}
};

class InitFieldBase : public Field {
public:
	InitFieldBase(Core::X3DNode* node) : Field(node) {}
};

template <class N, class T>
class InitField : public InitFieldBase {
private:
	T* const last;
public:
	InitField(N* node, T* ptr) :
		InitFieldBase(node),
		last(last)
		{}
	const T& operator*() const {
		return *last;
	}
};

class InFieldBase : public Field {
public:
	InFieldBase(Core::X3DNode* node) : Field(node) {}
	virtual void operator()(const SafePointer& ptr) const = 0;
};

template <class N, class T>
class InField : public InFieldBase {
private:
	void (N::*const set_fp)(const T&);
public:
	InField(N* node, void (N::*fp)(const T&)) :
		InFieldBase(node),
		set_fp(fp)
		{}
	void operator()(const T& value) const {
		N* node = static_cast<N*>(this->node);
		(node->*set_fp)(value);
	}
	void operator()(const SafePointer& ptr) const {
		N* node = static_cast<N*>(this->node);
		(node->*set_fp)(*ptr.cast<T>());
	}
};

class OutFieldBase : public Field {
public:
	OutFieldBase(Core::X3DNode* node) : Field(node) {}
	virtual const SafePointer& operator=(const SafePointer& ptr) const = 0;
};

template <class N, class T>
class OutField : public OutFieldBase {
private:
	void (N::*const changed_fp)(const T&);
public:
	T* const last;
	OutField(N* node, T* ptr, void (N::*fp)(const T&)=NULL) :
		OutFieldBase(node),
		last(ptr),
		changed_fp(fp)
		{}
	const T& operator=(const T& value) const {
		N* node = static_cast<N*>(this->node);
		if (changed_fp != NULL)
			(node->*changed_fp)(value);
		*last = value;
		return value;
	}
	const SafePointer& operator=(const SafePointer& ptr) const {
		N* node = static_cast<N*>(this->node);
		const T& value = *ptr.cast<T>();
		if (changed_fp != NULL)
			(node->*changed_fp)(value);
		*last = value;
		return ptr;
	}
	const T& operator*() const {
		return *last;
	}
};

class InOutFieldBase : public Field {
public:
	InOutFieldBase(Core::X3DNode* node) : Field(node) {}
	virtual const SafePointer& operator=(const SafePointer& ptr) const = 0;
	virtual void operator()(const SafePointer& ptr) const = 0;
};

template <class N, class T>
class InOutField : public InOutFieldBase {
private:
	void (N::*const set_fp)(const T&);
	void (N::*const changed_fp)(const T&);
public:
	T* const last;
	InOutField(N* node, T* ptr, void (N::*fp1)(const T&)=NULL, void (N::*fp2)(const T&)=NULL) :
		InOutFieldBase(node),
		last(ptr),
		set_fp(fp1),
		changed_fp(fp2)
		{}
	void operator()(const T& value) const {
		N* node = static_cast<N*>(this->node);
		if (set_fp != NULL)
			(node->*set_fp)(value);
		*this = value;
	}
	void operator()(const SafePointer& ptr) const {
		N* node = static_cast<N*>(this->node);
		const T& value = *ptr.cast<T>();
		if (set_fp != NULL)
			(node->*set_fp)(value);
		*this = value;
	}
	const T& operator=(const T& value) const {
		N* node = static_cast<N*>(this->node);
		if (changed_fp != NULL)
			(node->*changed_fp)(value);
		*last = value;
		return value;
	}
	const SafePointer& operator=(const SafePointer& ptr) const {
		N* node = static_cast<N*>(this->node);
		const T& value = *ptr.cast<T>();
		if (changed_fp != NULL)
			(node->*changed_fp)(value);
		*last = value;
		return ptr;
	}
	const T& operator*() const {
		return *last;
	}
};

}

#endif // #ifndef _X3D_FIELDS_H_
