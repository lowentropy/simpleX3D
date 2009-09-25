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

#ifndef _X3D_X3DNODE_H_
#define _X3D_X3DNODE_H_

#include "types.h"

namespace X3D {
namespace Core {

class X3DMetadataObject;

/**
 * X3DNode is the root of all node types in the X3D
 * scene hierarchy. The only actual field contained
 * by X3DNode is the #_metadata field, which contains
 * a single X3DMetadataObject value (if you want to
 * have a mapping of metadata values, use a MetadataSet,
 * which contains multiple metadata children nodes).
 */
class X3DNode {
	/** Arbitrary etadata information. */
	X3D_INOUT(X3DMetadataObject*, metadata)
protected:
	template <typename T> void output(const std::string name, T value) {
		// TODO
	}
};

}}

#include "Core/X3DMetadataObject.h"

#endif // #ifndef _X3D_X3DNODE_H_
