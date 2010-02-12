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

#include "Core/X3DInfoNode.h"

namespace X3D {
namespace Core {

/**
 * This node contains basic information about the X3D world.
 * It consists of the world's "title", followed by any number
 * of strings, such as author name, copyright, and usage
 * instructions.
 */
class WorldInfo : public X3DInfoNode {
public:

	/// Title of the world. Default is empty string.
	InitField<WorldInfo, SFString> title;

	/// Arbitrary strings providing global metadata
	InitField<WorldInfo, MFStringList> info;

    /// Setup stuff
    void setup() {}
};

}} // namespace X3D::Core

#endif // #ifndef _X3D_WORLDINFO_H_
