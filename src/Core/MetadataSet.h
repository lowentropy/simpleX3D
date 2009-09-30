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

#include <vector>
#include "types.h"
#include "Core/X3DMetadataObject.h"

using std::vector;

namespace X3D {
namespace Core {

/** Metadata value containing a list of metadata nodes (MFNode). */
class MetadataSet : public X3DMetadataObject {
public:

	typedef vector<X3DMetadataObject*> MFMetaNode;
	const MFMetaNode value;

	MetadataSet(const SFString& name, const MFMetaNode& value) :
		X3DMetadataObject(name),
		value(value) {}

	MetadataSet(const SFString& name, const SFString& ref, const MFMetaNode& value) :
		X3DMetadataObject(name, ref),
		value(value) {}
};

}} // namespace X3D::Core

#endif // #ifndef _X3D_METADATASET_H
