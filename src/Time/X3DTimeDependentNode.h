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

    X3DTimeDependentNode() {}

	/// if true, node will repeat its cycle
    DefaultInOutField<X3DTimeDependentNode, SFBool> loop;

	/// time at which node becomes paused
	class PauseTime : public DefaultInOutField<X3DTimeDependentNode, SFTime> {
        bool filter(double time) {
            if (time == value())
                return false;
            if (node()->isPaused())
                return false; // XXX this is not explicitly stated...
            node()->wake(time);
            return true;
        }
    } pauseTime;

	/// time at which node resumes from pause
	class ResumeTime : public DefaultInOutField<X3DTimeDependentNode, SFTime> {
        bool filter(double time) { // XXX nor is this...
            if (time == value())
                return false;
            if (node()->isPaused() && time <= node()->pauseTime())
                return false;
            node()->wake(time);
            return true;
        }
    } resumeTime;

	/// time at which node begins its cycle
	class StartTime : public DefaultInOutField<X3DTimeDependentNode, SFTime> {
        bool filter(double time) {
            if (time == value())
                return false;
            if (node()->getIsActive())
                return false;
            node()->wake(time);
            return true;
        }
    } startTime;

	/// time at which node ends current cycle
	class StopTime : public DefaultInOutField<X3DTimeDependentNode, SFTime> {
        bool filter(double time) {
            if (time == value())
                return false;
            if (node()->getIsActive() && time <= node()->startTime())
                return false;
            node()->wake(time);
            return true;
        }
    } stopTime;

	/// when paused, node will freeze state
	DefaultOutField<X3DTimeDependentNode, SFBool> isPaused;

	/// time since cycle began
	DefaultOutField<X3DTimeDependentNode, SFTime> elapsedTime;

    /// Setup function called on node instantiation.
    void setup() {
        loop.value = false;
    }
    
    virtual void wake(double time) { throw X3DError("ABSTRACT"); }
    virtual bool getIsActive() const { throw X3DError("ABSTRACT"); }
    virtual bool tick() { throw X3DError("ABSTRACT"); }

private:

    // no copy constructor
    X3DTimeDependentNode(const X3DTimeDependentNode& node) { throw X3DError("COPY CONSTRUCTOR"); }
};

}}

#endif // #ifndef _X3D_X3DTIMEDEPENDENTNODE_H_
