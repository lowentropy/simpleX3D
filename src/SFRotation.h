#ifndef _X3D_ROTATION_H_
#define _X3D_ROTATION_H_

#include "types.h"
#include <math.h>

class SFRotation {
public:
	float x;
	float y;
	float z;
	float a;
	SFRotation() : x(0), y(0), z(1), a(0) {}
	SFRotation(const SFRotation& r) : x(r.x), y(r.y), z(r.z), a(r.a) {}
	SFRotation(float x, float y, float z, float a) : x(x), y(y), z(z), a(a) {}
	SFMatrix3<float> matrix() const {
		float c = cos(a), s = sin(a), t = 1-c;
		float tx = t * x, ty = t * y, tz = t * z;
		float txy = tx * y, tyz = ty * z, txz = tx * z;
		float sx = s * x, sy = s * y, sz = s * z;
		float m[9] = {
			tx * x + c, txy + sz, txz - sy,
			txy - sz, ty * y + c, tyz + sx,
			txz + sy, tyz - sx, tz * z + c
		};
		return SFMatrix3<float>(m);
	}
	float* array() { return &x; }
};

#endif // #ifndef _X3D_ROTATION_H_
