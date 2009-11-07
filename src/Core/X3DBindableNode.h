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

#include "Core/X3DChildNode.h"
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
class X3DBindableNode : virtual public X3DChildNode {
public:

	/// The time at which the node is bound or unbound.
	DefaultOutField<X3DBindableNode, SFTime> bindTime;

	/// Whether the node is bound or not.
	class IsBound : public OutField<X3DBindableNode, SFBool> {
		void action() {
			node()->onIsBound(value());
		}
	} isBound;

	/// Set whether node is bound
	class SetBind : public InField<X3DBindableNode, SFBool> {
		void action(bool bound) {
			node()->bind(bound);
		}
	} set_bind;

    /// Setup stuff
    void setup() {}

	/// Callback for #isBound output event.
	virtual void onIsBound(bool bound) {} // XXX abstract ?

	/**
	 * Default action to take on set_bind input event.
	 * 
	 * Rearranges the bindable nodes on the appropriate stack,
	 * which may call set_bind(false) on the currently bound
	 * node, or set_bind(true) on the next node in the stack,
	 * depending on the value of bound.
	 * 
	 * There is no callback associated with #set_bind, which
	 * guarantees that no action can be taken if bound == #isBound.
	 * 
	 * @param bound whether the node should be bound or unbound
	 */
	void bind(bool bound) {
		Stack* stack = this->stack();
		if (bound) {
			if (isBound())
				return;
			X3DBindableNode* top = stack->front();
			if (top)
				top->isBound(true);
			stack->remove(this);
			stack->push_front(this);
		} else {
			stack->remove(this);
			X3DBindableNode* top = stack->front();
			if (top)
				top->isBound(true);
		}
	}
	
	/**
	 * Destroying a bindable node has the same effect as
	 * sending false to #set_bind.
	 */
	virtual ~X3DBindableNode() {
		set_bind(false);
	}

	/// The stack for bindable nodes is just an STL list.
	class Stack : public std::list<X3DBindableNode*> {};

	/**
	 * Return the stack associated with this bindable node.
	 * 
	 * @returns bindable stack
     */
	virtual Stack* stack() const {
		throw X3DError("X3DBindableNode subclasses MUST provide stack()");
	}

};

}}

#endif // #ifndef _X3D_X3DBINDABLENODE_H_
