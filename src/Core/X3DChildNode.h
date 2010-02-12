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

#ifndef _X3D_X3DCHILDNODE_H_
#define _X3D_X3DCHILDNODE_H_

#include "Core/X3DNode.h"

namespace X3D {
namespace Core {

/**
 * The base class for any node which
 * can be the child of another node. Note that X3D nodes
 * do not form strict trees, but are actually directed
 * acyclic graphs.
 */
class X3DChildNode : virtual public X3DNode {
protected:
	/// list of parent nodes
	MFNodeSet<X3DNode> parents;

public:
    /// Setup stuff
    void setup() {}

    virtual const string& defaultContainerField() {
        static string x("children");
        return x;
    }
};

}}

#endif // #ifndef _X3D_X3DCHILDNODE_H_
