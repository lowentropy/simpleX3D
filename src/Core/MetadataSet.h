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

#ifndef _X3D_METADATASET_H
#define _X3D_METADATASET_H

#include "Core/X3DNode.h"
#include "Core/X3DMetadataObject.h"
#include <vector>

using std::vector;

namespace X3D {
namespace Core {

/** Metadata value containing a list of metadata nodes (MFNode). */
class MetadataSet : public X3DNode, public X3DMetadataObject {
public:

	/// metadata value, a list of other metadata (last written to value_changed)
	vector<X3DMetadataObject*> value;

	/// Default node constructor.
	MetadataSet(NodeDefinition* def) : Node(def) {}

	/**
	 * Add entries to #value from the entries in the given map.
	 * 
	 * The map contains strings for keys and values, so the
	 * new metadata entries will be of type MetadataString.
	 * 
	 * @param meta map of metadata keys to values
	 * @param quiet if true, value_changed event is suppressed
	 */ 
	virtual void assignFromMap(const map<string,string>& meta, bool quiet=false);

	/**
	 * Add a single new metadata entry to the set.
	 * 
	 * @param entry metadata entry to add
	 * @param quiet if true, value_changed event is suppressed
	 */
	void addMetadata(X3DMetadataObject* entry, bool quiet=false);
};

}} // namespace X3D::Core

#endif // #ifndef _X3D_METADATASET_H
