#ifndef _X3D_SCALARINTERPOLATOR_H_
#define _X3D_SCALARINTERPOLATOR_H_

#include "Interpolation/X3DInterpolatorNode.h"

namespace X3D {
namespace Interpolation {

class ScalarInterpolator : public X3DInterpolatorNode {
public:
    DefaultInOutField<ScalarInterpolator, MFFloatArray> keyValue;
    DefaultOutField<ScalarInterpolator, SFFloat> value_changed;
    void setup() {}
protected:
    bool outputIsDirty();
    virtual void setFraction(float fraction, int index);
};

}}

#endif // #ifndef _X3D_SCALARINTERPOLATOR_H_
