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

namespace X3D {
namespace Core {

class X3DBindableNode : public X3DChildNode {
public:

	/// last known bind time? TODO find out
	X3D_OUT(SFTime, bindTime) 

	/// signals [un]binding of node
	X3D_OUT(SFBool, isBound) 

	/// binds or removes/detaches node
	X3D_IN(SFBool, set_bind) {
		if (value) {
			if (isBound)
				return;
			X3DBindableNode* top = stack->top();
			if (top)
				top->isBound(false);
			stack.remove(this);
			stack.push(this);
			isBound(true);
		} else {
			if (isBound)
				isBound(false);
			stack->remove(this);
			X3DBindableNode* top = stack->top();
			if (top)
				top->isBound(true);
		}
		_set_bind(value);
	}

public:

	virtual ~X3DBindableNode() {
		set_bind(false);
	}

	X3DBindableNode() {
		ROUTE_IN(set_bind);
	}
};

}}

#endif // #ifndef _X3D_X3DBINDABLENODE_H_
