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
using std::vector;

namespace X3D {
namespace Interpolation {

void PositionInterpolator::setFraction(float fraction) {
    if (value_changed.isDirty())
        return;
    SFVec3f value;
    vector<float> keys = key().array();
    vector<SFVec3f> values = keyValue().array();
    int size = keys.size();

    if (fraction <= keys[0]) {
        value = values[0];
    } else if (fraction >= keys[size-1]) {
        value = values[size-1];
    } else {
        int low = 0;
        int high = size - 1;
        while (low < high - 1) {
            int mid = low + ((high - low) / 2);
            if (keys[mid] > fraction)
                high = mid;
            else if (keys[mid+1] < fraction)
                low = mid + 1;
        }
        float a = fraction - keys[low];
        float b = keys[low+1] - fraction;
        SFVec3f &lo = values[low], &hi = values[low+1];
        value = (hi - lo) * a / (a + b) + lo;
    }
    value_changed.send(value);
}

}}
