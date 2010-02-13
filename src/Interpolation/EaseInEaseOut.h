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

#ifndef _X3D_EASEINEASEOUT_H_
#define _X3D_EASEINEASEOUT_H_

#include "Interpolation/X3DInterpolatorNode.h"

namespace X3D {
namespace Interpolation {

class EaseInEaseOut : public X3DInterpolatorNode {
public:
    DefaultInOutField<EaseInEaseOut, MFVec2fArray> easeInEaseOut;
    DefaultOutField<EaseInEaseOut, SFFloat> modifiedFraction_changed;
    void setup() {}
protected:
    bool outputIsDirty();
    virtual void setFraction(float fraction, int index);
};

}}

#endif // #ifndef _X3D_EASEINEASEOUT_H_
