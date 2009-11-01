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

#include "Core/X3DChildNode.h"

using X3D::Core::X3DChildNode;

namespace X3D {
namespace Time {

/**
 * Base class for any node which is time-sensitive, such
 * as TimeSensor, MovieTexture, etc.
 * 
 * NOTE: due to the multiple inheritance in TimeSensor,
 * this abstract node does not include the field 'isActive'.
 * Instead, this field is defined ONLY by X3DSensorNode.
 * If you must get the isActive value from an abstract
 * X3DTimeDependentNode, use the function getIsActive().
 */
class X3DTimeDependentNode : virtual public X3DChildNode {
public:

	/// if true, node will repeat its cycle
	class Loop : public InOutField<X3DTimeDependentNode, SFBool> {
		void action() { node()->onLoopChanged(value()); }
	} loop;

	/// when paused, node will freeze state
	class IsPaused : public OutField<X3DTimeDependentNode, SFBool> {
        void action() { node()->onIsPaused(value()); }
    } isPaused;

	/// time at which node becomes paused
	DefaultInOutField<X3DTimeDependentNode, SFTime> pauseTime;

	/// time at which node resumes from pause
	DefaultInOutField<X3DTimeDependentNode, SFTime> resumeTime;

	/// time at which node begins its cycle
	DefaultInOutField<X3DTimeDependentNode, SFTime> startTime;

	/// time at which node ends current cycle
	DefaultInOutField<X3DTimeDependentNode, SFTime> stopTime;

	/// time since cycle began
	DefaultOutField<X3DTimeDependentNode, SFTime> elapsedTime;

	/// Default node constructor.
	X3DTimeDependentNode() :
		pauseTime(0), resumeTime(0),
		startTime(0), stopTime(0) {
        loop(false);
    }

    virtual void onLoopChanged(bool loop) {} // XXX abstract
    virtual void onIsPaused(bool paused) {} // XXX abstract
    virtual bool getIsActive() { return false; } // XXX abstract
};

}}

#endif // #ifndef _X3D_X3DTIMEDEPENDENTNODE_H_
