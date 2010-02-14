#ifndef _X3D_POSITIONINTERPOLATOR2D_H_
#define _X3D_POSITIONINTERPOLATOR2D_H_

#include "Interpolation/X3DInterpolatorNode.h"

namespace X3D {
namespace Interpolation {

class PositionInterpolator2D : public X3DInterpolatorNode {
public:
    DefaultInOutField<PositionInterpolator2D, MFVec2fArray> keyValue;
    DefaultOutField<PositionInterpolator2D, SFVec2f> value_changed;
    void setup() {}
protected:
    bool outputIsDirty();
    virtual void setFraction(float fraction, int index);
};

}}

#endif // #ifndef _X3D_POSITIONINTERPOLATOR2D_H_
