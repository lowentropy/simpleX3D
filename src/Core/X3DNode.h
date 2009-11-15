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

#include "Core/X3DMetadataObject.h"
#include <string>
#include <map>

using std::string;
using std::map;

namespace X3D {
namespace Core {

/**
 * The root of all node types in the X3D
 * scene hierarchy. The only actual field contained
 * by X3DNode is the #metadata field, which contains
 * a single X3DMetadataObject value (if you want to
 * have a mapping of metadata values, use a MetadataSet,
 * which contains multiple metadata children nodes).
 */
class X3DNode : virtual public Node {
public:

	/// Metadata information, which all nodes have.
	DefaultInOutField<X3DNode, SFNode<X3DMetadataObject> > metadata;

    /// Setup stuff
    void setup() {}

	/**
	 * Assign metadata from a string-to-string map. Calls the
	 * assignFromMap method on #metadata.
	 * 
	 * @param meta map of new metadata entries
	 * @param quiet if true, suppresses metadata_changed and other output events
	 */
	virtual void assignMetadata(const map<string,string>& meta, bool quiet=false);

};

}}

#include "Core/X3DMetadataObject.h"

#endif // #ifndef _X3D_X3DNODE_H_
