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

#include "Interpolation/CoordinateInterpolator2D.h"
#include <vector>
using std::vector;

namespace X3D {
namespace Interpolation {

bool CoordinateInterpolator2D::outputIsDirty() {
    return value_changed.isDirty();
}

void CoordinateInterpolator2D::setFraction(float fraction, int index) {
    vector<float>& keys = key().array();
    vector<SFVec2f>& values = keyValue().array();
    vector<SFVec2f>& output = value_changed().array();
    int size = keys.size();
    // TODO: check that values.size() is multiple of keys.size()
    int multiple = values.size() / size;
    if (index < 0) {
        fraction = 0.0;
        index = 0;
    } else if (index == size-1) {
        fraction = 1.0;
        index = size-1;
    }
    float a = keys[index], b = keys[index+1];
    output.clear();
    int start = index * multiple;
    for (int i = start; i < start + multiple; i++) {
        SFVec2f lo = values[i], hi = values[i+1];
        SFVec2f diff = hi - lo;
        output.push_back(lo + (diff / (b - a)) * (fraction - a));
    }
    value_changed.changed();
}

}}
