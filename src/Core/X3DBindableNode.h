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

#ifndef _X3D_X3DBINDABLENODE_H_
#define _X3D_X3DBINDABLENODE_H_

#include "types.h"
#include "Core/X3DChildNode.h"
#include <sstream>
#include <list>

namespace X3D {
namespace Core {

/**
 * This node is the parent of any nodes which can be
 * bound to the scene. They include Background, TextureBackground,
 * Fog, NavigationInfo, and Viewpoint nodes. For each of these
 * types, only one node of that type can be bound to a particular
 * layer at any given time.
 *
 * \see ISO-IEC-19775-1.2 Part 5, 7.2.2 "Bindable children nodes"
 */
class X3DBindableNode : public X3DChildNode {
public:
	const SFTime bindTime;
	const SFBool isBound;

	X3DBindableNode() : isBound(false), bindTime(0) {}

	void set_bind(const SFBool& bound) {
		Stack* stack = this->stack();
		if (bound) {
			if (isBound)
				return;
			X3DBindableNode* top = stack->front();
			if (top)
				top->signal("isBound", false);
			stack->remove(this);
			stack->push_front(this);
		} else {
			stack->remove(this);
			X3DBindableNode* top = stack->front();
			if (top)
				top->signal("isBound", true);
		}
	}
	
	/**
	 * Destroying a bindable node has the same effect as
	 * sending false to #set_bind.
	 */
	virtual ~X3DBindableNode() {
		set_bind(false);
	}

	class Stack : public std::list<X3DBindableNode*> {};

	/**
	 * Return the stack associated with this bindable node.
	 * 
	 * @returns bindable stack
     */
	Stack* stack() const {
		// TODO
		return NULL;
	}

	virtual void on_isBound(const SFBool& value) {}

};

}}

#endif // #ifndef _X3D_X3DBINDABLENODE_H_
