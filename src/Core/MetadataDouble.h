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

#ifndef _X3D_METADATADOUBLE_H_
#define _X3D_METADATADOUBLE_H_

#include "types.h"
#include "Core/X3DMetadataObject.h"

namespace X3D {
namespace Core {

/** Metadata value containing a list of floats (MFFloat). */
class MetadataDouble : public X3DMetadataObject {
public:
	const MFDouble value;

	MetadataDouble(SFString name, const MFDouble& value) :
		X3DMetadataObject(name),
		value(value) {}

	MetadataDouble(const SFString& name, const SFString& ref, const MFDouble& value) :
		X3DMetadataObject(name, ref),
		value(value) {}
};

}}

#endif // #ifndef _X3D_METADATADOUBLE_H_
