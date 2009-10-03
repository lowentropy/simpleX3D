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

class NodeDefinition;

namespace Core {

class X3DMetadataObject;
using ::X3D::NodeDefinition;

/**
 * X3DNode is the root of all node types in the X3D
 * scene hierarchy. The only actual field contained
 * by X3DNode is the #metadata field, which contains
 * a single X3DMetadataObject value (if you want to
 * have a mapping of metadata values, use a MetadataSet,
 * which contains multiple metadata children nodes).
 */
class X3DNode {
public:

	const NodeDefinition* definition;
	const X3DMetadataObject* metadata;

	X3DNode(NodeDefinition* def) : definition(def), metadata(NULL) {}
	virtual ~X3DNode() {}

	template <typename T> void signal(const std::string& name, const T& value) {
		// TODO
	}

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

}}

#include "Core/X3DMetadataObject.h"

#endif // #ifndef _X3D_X3DNODE_H_
