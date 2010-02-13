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

#include "Interpolation/PositionInterpolator.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

namespace X3D {
namespace Interpolation {

void PositionInterpolator::setFraction(float fraction, int index) {
    vector<float>& keys = key().array();
    vector<SFVec3f>& values = keyValue().array();
    int size = keys.size();
    SFVec3f value;
    if (index < 0) {
        value = values[0];
    } else if (index == size-1) {
        value = values[size-1];
    } else {
        float a = keys[index], b = keys[index+1];
        SFVec3f &lo = values[index], &hi = values[index+1];
        SFVec3f diff = hi - lo;
        value = lo + (diff / (b - a)) * (fraction - a);
    }
    value_changed.send(value);
}

}}
