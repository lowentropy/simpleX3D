#ifndef _X3D_POSITIONINTERPOLATOR_H_
#define _X3D_POSITIONINTERPOLATOR_H_

#include "Interpolation/X3DInterpolatorNode.h"

namespace X3D {
namespace Interpolation {

class PositionInterpolator : public X3DInterpolatorNode {

    DefaultInOutField<PositionInterpolator, MFVec3fArray> keyValue;

    OutField<PositionInterpolator, SFVec3f> value_changed;

    void setup() {}

    void setFraction(float fraction) {
        if (value_changed.isDirty())
            return;
        SFVec3f value;
        vector<float> keys = key().vector();
        vector<SFVec3f> values = keyValue().vector();
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
            value = b * values[low] + a * values[low+1] / (a + b);
        }
        value_changed.send(value);
    }
};

}}

#endif // #ifndef _X3D_POSITIONINTERPOLATOR_H_
