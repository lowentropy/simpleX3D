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

#ifndef _X3D_NODE_H_
#define _X3D_NODE_H_

#include "internal/config.h"
#include "internal/errors.h"
#include "internal/SafePointer.h"
#include <string>

using std::string;

namespace X3D {

// forward declarations
class NodeDefinition;
class Browser;

class Node {
public:

	const NodeDefinition* definition;

	Node() { throw X3DError("illegal empty node constructor call"); }
	Node(NodeDefinition* def) : definition(def) {}

	virtual ~Node() {}

	/**
	 * Return a reference to the browser. This is a helper function
	 * that simply calls Browser::getSingleton.
	 * 
	 * @returns singleton instance of Browser
	 */
	virtual Browser* browser();

	/**
	 * Generic field getter. Will return the value of the last
	 * event fired for fields of type outputOnly and inputOutput.
	 * If no event has been fired, it will return the default
	 * value of this field (for inputOutput fields, this may have
	 * been set explicitly). If the field refers to an inputOutput
	 * field, then it does not matter if the field name includes
	 * "_changed". If the field is an initOnly, then the constant
	 * value is returned. This function will not trigger any events.
	 * 
	 * @param field name of field to get
	 * @returns generic field value
	 */
	virtual SafePointer get(const string& field) const;

	/**
	 * Send a generic value to an input field. The field type may
	 * be inputOnly or inputOutput. The associated action for the
	 * input event is called, if it exists. If there is an associated
	 * output field, then it will be fired unless quiet is set to
	 * true. However, the input event action may trigger output events
	 * of its own, which may not obey the event suppression. If the
	 * field is inputOutput, then the name can optionally prepend
	 * "set_".
	 * 
	 * @param field name of field to set
	 * @param value generic value to send with event
	 */
	virtual void set(const string& field, const SafePointer& value);

	/**
	 * Indicate that a field value has changed and that the associated
	 * output event should fire. The field type may be outputOnly or
	 * inputOutput. It is assumed that at the time of calling #changed,
	 * the value for the output event has been stored in the associated
	 * variable. This value will be sent through any associated routes.
	 * Before the routes are activated, the associated output action is
	 * called if it exists. If the field is inputOutput, then the name
	 * of the field may optionally append "_changed".
	 * 
	 * @param field name of field which has changed
	 */
	virtual void changed(const string& field) const;

	/**
	 * Templatized version of #get. This version will unwrap the return
	 * value of the generic version of #get, and return the dereferenced,
	 * type-specific value (which may still be a pointer).
	 * 
	 * @param field name of field to get
	 * @returns templatized field value
	 */
	template <typename T> T get(const string& field) const {
		return *(this->get(field).cast<T>());
	}

	/**
	 * Templatized version of #set. This version will wrap the input argument
	 * in a SafePointer before calling the generic version of #set.
	 * 
	 * @param field name of field to set
	 * @param value templatized value to send with event
	 */
	template <typename T> void set(const string& field, const T& value) {
		this->set(field, SafePointer(value));
	}

	/**
	 * Safe down-casting through X3DNode heirarchy (const version).
	 * 
	 * If the compiler directive SAFE_CAST is true, then a dynamic
	 * cast is performed that will throw an X3DError if the cast
	 * is illegal. Otherwise, the cast is performed statically and
	 * will produce unsafe results for invalid casts.
	 * 
	 * @returns subclass cast
	 */
	template <class T> const T* cast() const {
#if SAFE_CAST
		const T* node = dynamic_cast<const T*>(this);
		if (node == NULL)
			throw X3DError("illegal node cast");
#else
		const T* node = static_cast<const T*>(this);
#endif
		return node;
	}

	/**
	 * Safe down-casting through X3DNode heirarchy (non-const version).
	 * 
	 * If the compiler directive SAFE_CAST is true, then a dynamic
	 * cast is performed that will throw an X3DError if the cast
	 * is illegal. Otherwise, the cast is performed statically and
	 * will produce unsafe results for invalid casts.
	 * 
	 * @returns subclass cast
	 */
	template <class T> T* cast() {
#if SAFE_CAST
		T* node = dynamic_cast<T*>(this);
		if (node == NULL)
			throw X3DError("illegal node cast");
#else
		T* node = static_cast<T*>(this);
#endif
		return node;
	}
};

}

#endif // #ifndef _X3D_NODE_H_
