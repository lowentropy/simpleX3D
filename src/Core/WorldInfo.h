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

#ifndef _X3D_WORLDINFO_H_
#define _X3D_WORLDINFO_H_

#include "types.h"
#include "Core/X3DInfoNode.h"

namespace X3D {
namespace Core {

class WorldInfo : public X3DInfoNode {
	/// world information metadata
	X3D_INIT(MFString, info) 
	/// world title
	X3D_INIT(SFString, title) 
};

}} // namespace X3D::Core

#endif // #ifndef _X3D_WORLDINFO_H_
