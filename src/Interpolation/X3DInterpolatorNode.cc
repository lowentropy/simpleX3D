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

#include "Interpolation/X3DInterpolatorNode.h"

#include <vector>
using std::vector;

namespace X3D {
namespace Interpolation {

int X3DInterpolatorNode::findKeyIndex(float fraction) {
    vector<float> keys = key().array();
    int size = keys.size();
    int low = 0, high = size - 1;
    if (fraction >= keys[lastKeyIndex]) {
        if (fraction <= keys[lastKeyIndex+1])
            return lastKeyIndex;
        if (lastKeyIndex + 2 < size)
            return lastKeyIndex + 1;
        low = lastKeyIndex;
    }
    if (fraction <= keys[0]) {
        return -1;
    } else if (fraction >= keys[size - 1]) {
        return size - 1;
    } else {
        while (low < high - 1) {
            int mid = low + ((high - low) / 2);
            if (keys[mid] >= fraction) {
                high = mid;
            } else if (keys[mid+1] < fraction) {
                low = mid + 1;
            } else {
                low = mid;
                break;
            }
        }
        return low;
    }
}

void X3DInterpolatorNode::setFraction(float fraction) {
    if (fraction == lastFraction)
        return;
    if (getField("value_changed")->isDirty())
        return;
    lastFraction = fraction;
    int index = findKeyIndex(fraction);
    vector<float> keys = key().array();
    int size = keys.size();
    setFraction(fraction, findKeyIndex(fraction));
}

}}
