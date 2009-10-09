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
	const SFBool enabled;

	/// Whether sensor is currently active.
	const SFBool isActive;

	/// Default node constructor.
	X3DSensorNode() : enabled(true), isActive(false) {}

	/// DO NOT USE
	X3DSensorNode(NodeDefinition* def) :
		enabled(true), isActive(false) {
		throw X3DError("BUG - should not be called");
	}

	/**
	 * Default action to take on input event to #enabled.
	 * May cause #isActive to change along with its associated
	 * actions. This input event has no callback, but it is
	 * virtual; it is likely that some but not all sensors would
	 * wish to use the strategy pattern, but in any case you
	 * can put callback actions into #on_enabled_changed.
	 * 
	 * @param enabled new value of #enabled
	 */
	virtual void set_enabled(const SFBool& enabled) {};

	/**
	 * Default action for #enabled output event is to invoke
	 * callback actions in #on_enabled_changed.
	 */
	virtual void enabled_changed() { on_enabled_changed(); }

	/// Callback for #enabled output event.
	virtual void on_enabled_changed() {};

	/// Callback for #isActive output event.
	virtual void on_isActive() {};
};

}}

#endif // #ifndef _X3D_X3DSENSORNODE_H_
