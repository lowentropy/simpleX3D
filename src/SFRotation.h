#ifndef _X3D_ROTATION_H_
#define _X3D_ROTATION_H_

#include "types.h"
#include <math.h>

/**
 * Rotation around an arbitrary axis.
 * 
 * The #x, #y, and #z members define an axis and should always be
 * normalized. The #a member defines a right-handed rotation about this
 * axis. The default rotation value is (0,0,1,0).
 */
class SFRotation {
public:
	float x; ///< rotation axis X value
	float y; ///< rotation axis Y value
	float z; ///< rotation axis Z value
	float a; ///< angle of rotation

	/**
	 * Default constructor.
	 * 
	 * Default rotation is (0,0,1,0).
	 */
	SFRotation() : x(0), y(0), z(1), a(0) {}

	/**
	 * Copy constructor.
	 * 
	 * @param r rotation to copy from.
	 */
	SFRotation(const SFRotation& r) : x(r.x), y(r.y), z(r.z), a(r.a) {}

	/**
	 * Full constructor.
	 * 
	 * @param x rotation axis X value
	 * @param y rotation axis Y value
	 * @param z rotation axis Z value
	 * @param a angle of rotation
	 */
	SFRotation(float x, float y, float z, float a) : x(x), y(y), z(z), a(a) {}

	/**
	 * Convert into rotation matrix.
	 * 
	 * The matrix will be of the form
	 * \f$ \left[
	 *   \begin{array}{ccc}
	 *     t x^2 + c   & t x y + s z & t x z - s y \\
	 *     t x y - s z & t y^2 + c   & t y z + s x \\
	 *     t x z + s y & t y z - s x & t z^2 + c
	 *   \end{array}
	 * \right] \f$
	 * 
	 * where \f$ s = sin(\alpha) \f$,
	 * \f$ c = cos(\alpha) \f$, and \f$ t = 1 - c \f$.
	 */
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