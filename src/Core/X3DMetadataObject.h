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

#ifndef _X3D_X3DMETADATAOBJECT_H_
#define _X3D_X3DMETADATAOBJECT_H_

#include "internal/types.h"
#include "Core/X3DNode.h"
#include <string>

using std::string;

namespace X3D {
namespace Core {

/**
 * This abstract type is the parent for any node
 * which provides a metadata value. The node must
 * provide both a name and value.
 * 
 * XXX According to the spec, X3DMetadaObject itself
 * is abstract, NOT derived from X3DNode. However, the
 * spec also states:
 * 
 *   NOTE  Since a metadata node is derived from X3DNode,
 *         the metadata node may itself have metadata.
 * 
 * The simpleX3D dynamic typing system does not allow
 * X3D fields in classes not derived from X3DNode; since
 * it seems all real metadata nodes DO derive from it,
 * then EITHER X3DMetadataObject must be part of the
 * inheritance hierarchy, OR every node would have to
 * redefine the #name and #reference fields.
 * 
 * Currently, simpleX3D DOES allow X3DMetadataObject to
 * subclass X3DNode, but this may change in the future.
 */
class X3DMetadataObject : public X3DNode {
public:

	/// Key of the metadata object, always a string.
	const SFString name;

	/// Metadata specification for #name (optional).
	const SFString reference;

	/// Default node constructor.
	X3DMetadataObject(NodeDefinition* def) : X3DNode(def) {}

	/**
	 * Assign new metadata entries from a string-to-string map.
	 * 
	 * Concrete metadata classes should only provide this method
	 * if it makes sense to do so.
	 * 
	 * @param meta map of new metadata to add
	 * @param quiet if true, value_changed event is suppressed
	 */
	virtual void assignFromMap(const map<string,string>& meta, bool quiet=false) {
		throw X3DError("not implemented in this metadata class");
	}

	/**
	 * Assign new metadata value from a string.
	 * 
	 * Concrete metadata classes should only provide this method
	 * if it makes sense to do so.
	 * 
	 * @param str new string value to set
	 * @param quiet if true, value_changed event is suppressed
	 */
	virtual void assignFromString(const string& str, bool quiet=false) {
		throw X3DError("not implemented in this metadata class");
	}
};

}}

#endif // #ifndef _X3D_X3DMETADATAOBJECT_H_
