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

#ifndef _X3D_X3DINTERPOLATORNODE_H_
#define _X3D_X3DINTERPOLATORNODE_H_

#include "Core/X3DChildNode.h"

namespace X3D {
namespace Interpolation {

class X3DInterpolatorNode : public X3D::Core::X3DChildNode {
private:

    float lastFraction;
    int lastKeyIndex;

public:

    class SetFraction : public InField<X3DInterpolatorNode, SFFloat> {
        void action(float fraction) {
            node()->setFraction(fraction);
        }
    } set_fraction;

    DefaultInOutField<X3DInterpolatorNode, MFFloatArray> key;

    void setup() {
        lastFraction = -1;
        lastKeyIndex = 0;
    }

    void setFraction(float fraction);

protected:

    virtual void setFraction(float fraction, int index) { throw X3DError("ABSTRACT"); }
    virtual bool outputIsDirty() { throw X3DError("ABSTRACT"); }
    virtual int findKeyIndex(float fraction);

};

}
}

#endif // #ifndef _X3D_X3DINTERPOLATORNODE_H_
