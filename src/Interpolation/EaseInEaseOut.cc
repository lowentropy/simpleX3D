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

#include "Interpolation/EaseInEaseOut.h"
#include <vector>
using std::vector;

namespace X3D {
namespace Interpolation {

bool EaseInEaseOut::outputIsDirty() {
    return modifiedFraction_changed.isDirty();
}

void EaseInEaseOut::setFraction(float fraction, int index) {
    vector<float>& keys = key().array();
    vector<SFVec2f>& ease = easeInEaseOut().array();
    float lo = keys[index], hi = keys[index+1];
    float u = (fraction - lo) / (hi - lo);
    float e_out = ease[index].y;
    float e_in = ease[index+1].x;
    float sum = e_in + e_out;
    float value;
    if (sum < 0) {
        value = u;
    } else {
        float t = 1.0 / (2.0 - sum);
        if (u < e_out) {
            value = (t / e_out) * u * u;
        } else if (u < 1.0 - e_in) {
            value = t * (2.0 * u - e_out);
        } else {
            float u1 = 1.0 - u;
            value = 1.0 - (t * u1 * u1) / e_in;
        }
    }
    modifiedFraction_changed.send(value);
}

}}
