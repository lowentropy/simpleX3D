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

    X3DSensorNode() {}
	
	/// Whether sensor is enabled. Precondition for #isActive.
	class Enabled : public DefaultInOutField<X3DSensorNode, SFBool> {
        bool filter(bool enabled) {
            if (enabled == value())
                return false;
            value = enabled;
            node()->setEnabled(enabled);
            return true;
        }
    } enabled;

	/// Whether sensor is currently active.
	DefaultOutField<X3DSensorNode, SFBool> isActive;

    /// Setup function called on instantiation.
    void setup() {
        enabled.value = true;
    }

    /// Enable or disable the sensor.
    virtual void setEnabled(bool enabled) { throw X3DError("ABSTRACT"); }

    /// Evaluate the sensor.
    virtual void evaluate() { throw X3DError("ABSTRACT"); }
        

private:

    // no copy constructor
    X3DSensorNode(const X3DSensorNode& node) { throw X3DError("COPY CONSTRUCTOR"); }
};

}}

#endif // #ifndef _X3D_X3DSENSORNODE_H_
