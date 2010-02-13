#ifndef _X3D_POSITIONINTERPOLATOR_H_
#define _X3D_POSITIONINTERPOLATOR_H_

#include "Interpolation/X3DInterpolatorNode.h"

namespace X3D {
namespace Interpolation {

class PositionInterpolator : public X3DInterpolatorNode {
public:
    DefaultInOutField<PositionInterpolator, MFVec3fArray> keyValue;
    DefaultOutField<PositionInterpolator, SFVec3f> value_changed;
    void setup() {}
    virtual void setFraction(float fraction, int index);
};

}}

#endif // #ifndef _X3D_POSITIONINTERPOLATOR_H_
