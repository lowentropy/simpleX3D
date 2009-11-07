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

#ifndef _X3D_METADATASTRING_H_
#define _X3D_METADATASTRING_H_

#include "Core/X3DNode.h"
#include "Core/X3DMetadataObject.h"

namespace X3D {
namespace Core {

/** Metadata value containing a list of strings (MFString). */
class MetadataString : public X3DNode, public X3DMetadataObject {
public:

	/// metadata value (last written to value_changed)
	DefaultInOutField<MetadataString, MFString> value;

    /// Setup stuff
    void setup() {}

	/**
	 * Assign metadata value from string.
	 * 
	 * Simply copies the given string into #value.
	 * 
	 * @param str new value of metadata.
	 * @param quiet if true, value_changed event is suppressed
	 */
	virtual void assignFromString(const string& str);
};

}} // namespace X3D::Core

#endif // #ifndef _X3D_METADATASTRING_H_
