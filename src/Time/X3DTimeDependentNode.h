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

#ifndef _X3D_X3DTIMEDEPENDENTNODE_H_
#define _X3D_X3DTIMEDEPENDENTNODE_H_

#include "internal/types.h"
#include "Core/X3DChildNode.h"

using X3D::Core::X3DChildNode;

namespace X3D {
namespace Time {

/**
 * Base class for any node which is time-sensitive, such
 * as TimeSensor, MovieTexture, etc.
 */
class X3DTimeDependentNode : virtual public X3DChildNode {
public:

	/// if true, node will repeat its cycle
	SFBool loop;

	/// when paused, node will freeze state
	SFBool paused;

	/// time at which node becomes paused
	SFTime pauseTime;

	/// time at which node resumes from pause
	SFTime resumeTime;

	/// time at which node begins its cycle
	SFTime startTime;

	/// time at which node ends current cycle
	SFTime stopTime;

	/// time since cycle began
	SFTime elapsedTime;

	/// Default node constructor.
	X3DTimeDependentNode() :
		loop(false), paused(false),
		pauseTime(0), resumeTime(0),
		startTime(0), stopTime(0) {}
	
	/// DO NOT USE
	X3DTimeDependentNode(NodeDefinition* def) {
		throw X3DError("BUG - should not be called");
	}

	virtual SFBool& getIsPaused() {
		return paused;
	}

	virtual void setIsPaused(const SFBool& paused) {
		this->paused = paused;
	}

	virtual SFBool& getIsActive() { throw X3DError("ABSTRACT"); }
	virtual void setIsActive(const SFBool& active) { throw X3DError("ABSTRACT"); }
};

}}

#endif // #ifndef _X3D_X3DTIMEDEPENDENTNODE_H_
