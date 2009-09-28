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

#ifndef _X3D_X3DSENSORNODE_H_
#define _X3D_X3DSENSORNODE_H_

#include "types.h"
#include "Core/X3DChildNode.h"

namespace X3D {
namespace Core {

/**
 * Sensor nodes represent interactive or automated triggers
 * which respond dynamically to the user and the scene to
 * change some behavior of the scene.
 */
class X3DSensorNode : public X3DChildNode {
private:
	SFBool _enabled;
	SFBool _active;

public:
	const InOutField<X3DSensorNode, SFBool> enabled;
	const OutField<X3DSensorNode, SFBool> isActive;

	X3DSensorNode() :
		_enabled(true),
		_active(false),
		enabled(this, &_enabled, NULL, &on_enabled),
		isActive(this, &_active, &on_isActive)
		{}
	
	virtual void on_enabled(SFBool enabled) = 0;
	virtual void on_isActive(SFBool active) = 0;
};

}}

#endif // #ifndef _X3D_X3DSENSORNODE_H_
