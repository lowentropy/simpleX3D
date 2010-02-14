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

#include "internal/MF.h"
#include "internal/InOutField.h"
#include <string>
#include <map>

using std::string;
using std::map;

namespace X3D {
namespace Core {

/**
 * This abstract type is the parent for any node
 * which provides a metadata value. The node must
 * provide both a name and value.
 */
class X3DMetadataObject : public virtual Node {
public:

	/// Key of the metadata object, always a string.
	DefaultInOutField<X3DMetadataObject, SFString> name;

	/// Metadata specification for #name (optional).
	DefaultInOutField<X3DMetadataObject, SFString> reference;

    /// Setup stuff
    void setup() {}

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
