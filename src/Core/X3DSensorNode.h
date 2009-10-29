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

#include "Core/X3DChildNode.h"

namespace X3D {
namespace Core {

/**
 * Sensor nodes represent interactive or automated triggers
 * which respond dynamically to the user and the scene to
 * change some behavior of the scene.
 */
class X3DSensorNode : virtual public X3DChildNode {
public:
	
	/// Whether sensor is enabled. Precondition for #isActive.
	class : public InOutField<X3DSensorNode, SFBool> {
		bool filter(const bool& enabled) {
			return (value() != enabled);
		}
		void action() {
			node()->onEnabled(value());
		}
	} enabled;

	/// Whether sensor is currently active.
	class : public OutField<X3DSensorNode, SFBool> {
		void action() {
			node()->onIsActive(value());
		}
	} isActive;

	/// Default node constructor.
	X3DSensorNode() : enabled(true), active(false) {}

	/// Callback for #enabled output event.
	virtual void onEnabled(bool enabled) {};

	/// Callback for #isActive output event.
	virtual void onIsActive(bool active) {};
};

}}

#endif // #ifndef _X3D_X3DSENSORNODE_H_
