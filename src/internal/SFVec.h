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

#ifndef _X3D_SFVEC_H_
#define _X3D_SFVEC_H_

#include <string.h>
#include <math.h>

using std::string;

namespace X3D {

template <typename T> class SFMatrix3;
template <typename T> class SFMatrix4;

/**
 * 2-Dimensional vector.
 * 
 * This is the base class for SFVec2f and SFVec2d, having template parameters
 * SFFloat and SFDouble, respectively. In either instance, the vector can generally
 * accept both types as arguments, and generally returns values and
 * vectors of its own type.
 * 
 * 2D vectors do not have matrix operations, as there are no 2x2 matrices in
 * the X3D spec.
 */
template <typename T>
class SFVec2 : public X3DField {
public:
	T x; ///< X coordinate
	T y; ///< Y coordinate

	/**
	 * Default constructor.
	 * 
	 * Default value is (0,0).
	 */
	SFVec2() : x(0), y(0) {}

	/**
	 * Copy constructor.
	 * 
	 * @param v SFVec2 to copy from
	 */
	template <typename U> SFVec2(const SFVec2<U>& v) : x(v.x), y(v.y) {}

	/**
	 * Full constructor.
	 * 
	 * @param x X coordinate
	 * @param y Y coordinate
	 */
	template <typename U> SFVec2(U x, U y) : x(x), y(y) {}

	/**
	 * Array accessor (mutable version).
	 * 
	 * Returns a pointer into the coordinate array. This pointer
	 * is mutable, so you can write new values into the vector.
	 * 
	 * @returns mutable pointer to coordinate array
	 */
	T* array() { return &x; }

	/**
	 * Array accessor (const version).
	 *
	 * Returns a pointer into the coordinate array. Thsi pointer
	 * is not mutable, so it is safe to use for vectors declared const.
	 * 
	 * @returns const pointer to coordinate array
	 */
	const T* array() const { return &x; }

	/**
	 * Vector length (magnitude).
	 * 
	 * Calculates magnitude as \f$ \sqrt{x^2 + y^2)} \f$.
	 * 
	 * @returns vector length
	 */
	T mag() const { return sqrt(x*x + y*y); }

	/**
	 * Calculate normalized vector.
	 * 
	 * Returns a vector in the same direction as this one having
	 * unit length. If the vector's magnitude is zero, then the
	 * zero vector is returned.
	 * 
	 * @returns normalized vector
	 */
	SFVec2<T> normal() const {
		T m = mag();
		if (m != 0.0)
			return *this / m;
		else
			return SFVec2<T>();
	}

	/** 
	 * Normalize this vector.
	 * 
	 * After calling, this vector will either have unit length, or,
	 * if it had zero length, it will be unchanged.
	 * 
	 * @returns reference to this
	 */
	SFVec2<T>& normalize() {
		T m = mag();
		if (m != 0.0)
			*this /= m;
		return *this;
	}

	/**
	 * Vector addition.
	 * 
	 * @param v vector to add to
	 * @returns vector sum
	 */
	template <typename U> SFVec2<T> operator+(const SFVec2<U>& v) const {
		return SFVec2<T>(x + v.x, y + v.y);
	}

	/**
	 * Vector subtraction.
	 * 
	 * @param v vector to subtract
	 * @returns vector difference
	 */
	template <typename U> SFVec2<T> operator-(const SFVec2<U>& v) const {
		return SFVec2<T>(x - v.x, y - v.y);
	}

	/**
	 * Vector-scalar multiplication.
	 * 
	 * @param s scalar to multiply by
	 * @returns scaled vector
	 */
	template <typename U> SFVec2<T> operator*(U s) const {
		return SFVec2<T>(x * s, y * s);
	}

	/**
	 * Vector-scalar division.
	 * 
	 * @param s scalar to divide by
	 * @returns scaled vector
	 */
	template <typename U> SFVec2<T> operator/(U s) const {
		return SFVec2<T>(x / s, y / s);
	}

	/**
	 * Vector dot-product.
	 * 
	 * Returns the value \f$ v_1 \cdot v_2 \f$.
	 * 
	 * @returns vector dot product.
	 */
	template <typename U> T operator*(SFVec2<U>& v) const {
		return (x * v.x) + (y * v.y);
	}

	/**
	 * Vector assignment.
	 * 
	 * @param v vector to assign from
	 * @returns reference to this
	 */
	template <typename U> SFVec2<T>& operator=(const SFVec2<U>& v) {
		x = v.x;
		y = v.y;
		return *this;
	}

	/**
	 * Vector in-place addition.
	 * 
	 * @param v vector to add
	 * @returns reference to this
	 */
	template <typename U> SFVec2<T>& operator+=(const SFVec2<U>& v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	/**
	 * Vector in-place subtraction.
	 * 
	 * @param v vector to subtract
	 * @returns reference to this
	 */
	template <typename U> SFVec2<T>& operator-=(const SFVec2<U>& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	/**
	 * Vector in-place scalar multiplication.
	 * 
	 * @param s scalar to multiply by
	 * @returns reference to this
	 */
	template <typename U> SFVec2<T>& operator*=(U s) {
		x *= s;
		y *= s;
		return *this;
	}

	/**
	 * Vector in-place scalar division.
	 * 
	 * @param s scalar to divide by
	 * @returns reference to this
	 */
	template <typename U> SFVec2<T>& operator/=(U s) {
		x /= s;
		y /= s;
		return *this;
	}
};

/**
 * 3-Dimensional vector.
 * 
 * This is the base class for SFVec3f and SFVec3d, having template parameters
 * SFFloat and SFDouble, respectively. In either instance, the vector can generally
 * accept both types as arguments, and generally returns values and
 * vectors of its own type.
 * 
 * 3D vectors define matrix operations and a cross-product operator.
 */
template <typename T>
class SFVec3 : public X3DField {
public:
	T x; ///< X coordinate
	T y; ///< Y coordinate
	T z; ///< Z coordinate

	/**
	 * Default constructor.
	 * 
	 * Default value is (0,0,0).
	 */
	SFVec3() : x(0), y(0), z(0) {}

	/**
	 * Copy constructor.
	 * 
	 * @param v SFVec3 to copy from
	 */
	template <typename U> SFVec3(const SFVec3<U> v) : x(v.x), y(v.y), z(v.z) {}

	/**
	 * Full constructor.
	 * 
	 * @param x X coordinate
	 * @param y Y coordinate
	 * @param z Z coordinate
	 */
	template <typename U> SFVec3(U x, U y, U z) : x(x), y(y), z(z) {}

	/**
	 * Array accessor (mutable version).
	 * 
	 * Returns a pointer into the coordinate array. This pointer
	 * is mutable, so you can write new values into the vector.
	 * 
	 * @returns mutable pointer to coordinate array
	 */
	T* array() { return &x; }

	/**
	 * Array accessor (const version).
	 *
	 * Returns a pointer into the coordinate array. Thsi pointer
	 * is not mutable, so it is safe to use for vectors declared const.
	 * 
	 * @returns const pointer to coordinate array
	 */
	const T* array() const { return &x; }

	/**
	 * Vector length (magnitude).
	 * 
	 * Calculates magnitude as \f$ \sqrt{x^2 + y^2 + z^2} \f$.
	 * 
	 * @returns vector length
	 */
	T mag() const { return sqrt(x*x + y*y + z*z); }

	/**
	 * Calculate normalized vector.
	 * 
	 * Returns a vector in the same direction as this one having
	 * unit length. If the vector's magnitude is zero, then the
	 * zero vector is returned.
	 * 
	 * @returns normalized vector
	 */
	SFVec3<T> norm() const {
		T m = mag();
		if (m != 0.0)
			return *this / m;
		else
			return SFVec3<T>();
	}

	/** 
	 * Normalize this vector.
	 * 
	 * After calling, this vector will either have unit length, or,
	 * if it had zero length, it will be unchanged.
	 * 
	 * @returns reference to this
	 */
	SFVec3<T>& normalize() {
		T m = mag();
		if (m != 0.0)
			*this /= m;
		return *this;
	}

	/**
	 * Vector addition.
	 * 
	 * @param v vector to add to
	 * @returns vector sum
	 */
	template <typename U> SFVec3<T> operator+(const SFVec3<U>& v) const {
		return SFVec3<T>(x + v.x, y + v.y, z + v.z);
	}

	/**
	 * Vector subtraction.
	 * 
	 * @param v vector to subtract
	 * @returns vector difference
	 */
	template <typename U> SFVec3<T> operator-(const SFVec3<U>& v) const {
		return SFVec3<T>(x - v.x, y - v.y, z - v.z);
	}

	/**
	 * Vector-scalar multiplication.
	 * 
	 * @param s scalar to multiply by
	 * @returns scaled vector
	 */
	template <typename U> SFVec3<T> operator*(U s) const {
		return SFVec3<T>(x * s, y * s, z * s);
	}

	/**
	 * Vector-scalar division.
	 * 
	 * @param s scalar to divide by
	 * @returns scaled vector
	 */
	template <typename U> SFVec3<T> operator/(U s) const {
		return SFVec3<T>(x / s, y / s, z / s);
	}

	/**
	 * Vector-matrix multiplication.
	 * 
	 * Right-multiplies this vector by the given matrix. The result has the equation
	 * \f$ v_2 = v_1^T \cdot M \f$.
	 * 
	 * @param m SFMatrix3 to multiply by
	 * @returns result of matrix multiplication
	 */
	template <typename U> SFVec3<T> operator*(const SFMatrix3<U>& m) const {
		SFVec3<T> v;
		const T* p1 = &x;
		const U* p2 = m.array();
		for (int i = 0; i < 3; i++, p1++) {
			v.x += *p1 * *p2++;
			v.y += *p1 * *p2++;
			v.z += *p1 * *p2++;
		}
		return v;
	}

	/**
	 * Vector dot-product.
	 * 
	 * Returns the value \f$ v_1 \cdot v_2 \f$.
	 * 
	 * @returns vector dot product.
	 */
	template <typename U> T operator*(SFVec3<U>& v) const {
		return (x * v.x) + (y * v.y) + (z * v.z);
	}

	/**
	 * Vector assignment.
	 * 
	 * @param v vector to assign from
	 * @returns reference to this
	 */
	template <typename U> SFVec3<T>& operator=(const SFVec3<U>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	/**
	 * Vector in-place addition.
	 * 
	 * @param v vector to add
	 * @returns reference to this
	 */
	template <typename U> SFVec3<T>& operator+=(const SFVec3<U>& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	/**
	 * Vector in-place subtraction.
	 * 
	 * @param v vector to subtract
	 * @returns reference to this
	 */
	template <typename U> SFVec3<T>& operator-=(const SFVec3<U>& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	/**
	 * Vector in-place scalar multiplication.
	 * 
	 * @param s scalar to multiply by
	 * @returns reference to this
	 */
	template <typename U> SFVec3<T>& operator*=(U s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	/**
	 * Vector-matrix in-place multiplication.
	 * 
	 * Right-multiplies the current vector by the given matrix.
	 * The resulting vector has the equation \f$ v' = v^T \cdot M \f$.
	 * 
	 * @param m SFMatrix3 to multiply by
	 * @returns reference to this
	 */
	template <typename U> SFVec3<T>& operator*=(const SFMatrix3<U>& m) {
		return this->operator=(*this * m);
	}

	/**
	 * Vector in-place scalar division.
	 * 
	 * @param s scalar to divide by
	 * @returns reference to this
	 */
	template <typename U> SFVec3<T>& operator/=(U s) {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	/**
	 * Vector cross-product.
	 * 
	 * Let a vector \f$ v \f$ be defined by its components \f$ i, j, k \f$
	 * such that
	 * 
	 * \f$ v = \left< x, y, z \right> = x i + y j + z k \f$.
	 * 
	 * Then the cross product of two vectors
	 * 
	 * \f$ v_1 = \left< a, b, c \right> \f$ and
	 * \f$ v_2 = \left< d, e, f \right> \f$
	 * 
	 * is given by taking the determinant
	 * 
	 * \f$ v_1 \times v_2 = \left| \begin{array}{ccc}
	 * i & j & k \\ a & b & c \\ d & e & f
	 * \end{array} \right| \f$.
	 * 
	 * @param v other vector in cross-product
	 * @returns result of cross-product
	 */
	template <typename U> SFVec3<T> operator^(const SFVec3<U>& v) const {
		return SFVec3<T>(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		);
	}
};

/**
 * 4-Dimensional (homogeneous) vector.
 * 
 * This is the base class for SFVec4f and SFVec4d, having template parameters
 * SFFloat and SFDouble, respectively. In either instance, the vector can generally
 * accept both types as arguments, and generally returns values and
 * vectors of its own type.
 * 
 * This class represents a homogeneous coordinate in three dimensions (so it has
 * four parameters). It does not support vector-length normalization or the dot
 * product. When scaling, the homogeneous coordinate is not changed.
 * 
 * SFVec4 defines matrix operations with SFMatrix4.
 */
template <typename T>
class SFVec4 : public X3DField {
public:
	T x; ///< X coordinate
	T y; ///< Y coordinate
	T z; ///< Z coordinate
	T w; ///< W coordinate (homogeneous)

	/**
	 * Default constructor.
	 * 
	 * Default value is (0,0,0,1).
	 */
	SFVec4() : x(0), y(0), z(0), w(1) {}

	/**
	 * Copy constructor.
	 * 
	 * @param v SFVec4 to copy from
	 */
	template <typename U> SFVec4(const SFVec4<U> v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

	/**
	 * Full constructor.
	 * 
	 * @param x X coordinate
	 * @param y Y coordinate
	 * @param z Z coordinate
	 * @param w W coordinate
	 */
	template <typename U> SFVec4(U x, U y, U z, U w) : x(x), y(y), z(z), w(w) {}

	/**
	 * Array accessor (mutable version).
	 * 
	 * Returns a pointer into the coordinate array. This pointer
	 * is mutable, so you can write new values into the vector.
	 * 
	 * @returns mutable pointer to coordinate array
	 */
	T* array() { return &x; }

	/**
	 * Array accessor (const version).
	 *
	 * Returns a pointer into the coordinate array. Thsi pointer
	 * is not mutable, so it is safe to use for vectors declared const.
	 * 
	 * @returns const pointer to coordinate array
	 */
	const T* array() const { return &x; }

	/**
	 * Vector addition.
	 * 
	 * @param v vector to add to
	 * @returns vector sum
	 */
	template <typename U> SFVec4<T> operator+(const SFVec4<U>& v) const {
		return SFVec4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	/**
	 * Vector subtraction.
	 * 
	 * @param v vector to subtract
	 * @returns vector difference
	 */
	template <typename U> SFVec4<T> operator-(const SFVec4<U>& v) const {
		return SFVec4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	/**
	 * Vector-scalar multiplication.
	 * 
	 * Note that the homogeneous coordinate #w is not scaled.
	 * 
	 * @param s scalar to multiply by
	 * @returns scaled vector
	 */
	template <typename U> SFVec4<T> operator*(U s) const {
		return SFVec4<T>(x * s, y * s, z * s, w);
	}

	/**
	 * Vector-scalar division.
	 * 
	 * Note that the homogeneous coordinate #w is not scaled.
	 * 
	 * @param s scalar to divide by
	 * @returns scaled vector
	 */
	template <typename U> SFVec4<T> operator/(U s) const {
		return SFVec4<T>(x / s, y / s, z / s, w);
	}

	/**
	 * Vector-matrix multiplication.
	 * 
	 * Right-multiplies this vector by the given matrix. The result has the equation
	 * \f$ v_2 = v_1^T \cdot M \f$.
	 * 
	 * @param m SFMatrix4 to multiply by
	 * @returns result of matrix multiplication
	 */
	template <typename U> SFVec4<T> operator*(const SFMatrix4<U>& m) const {
		SFVec4<T> v(0,0,0,0);
		const T* p1 = &x;
		const U* p2 = m.array();
		for (int i = 0; i < 4; i++, p1++) {
			v.x += *p1 * *p2++;
			v.y += *p1 * *p2++;
			v.z += *p1 * *p2++;
			v.w += *p1 * *p2++;
		}
		return v;
	}

	/**
	 * Vector assignment.
	 * 
	 * @param v vector to assign from
	 * @returns reference to this
	 */
	template <typename U> SFVec4<T>& operator=(const SFVec4<U>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}

	/**
	 * Vector in-place addition.
	 * 
	 * @param v vector to add
	 * @returns reference to this
	 */
	template <typename U> SFVec4<T>& operator+=(const SFVec4<U>& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	/**
	 * Vector in-place subtraction.
	 * 
	 * @param v vector to subtract
	 * @returns reference to this
	 */
	template <typename U> SFVec4<T>& operator-=(const SFVec4<U>& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	/**
	 * Vector in-place scalar multiplication.
	 * 
	 * @param s scalar to multiply by
	 * @returns reference to this
	 */
	template <typename U> SFVec4<T>& operator*=(U s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	/**
	 * Vector in-place scalar division.
	 * 
	 * @param s scalar to divide by
	 * @returns reference to this
	 */
	template <typename U> SFVec4<T>& operator/=(U s) {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	/**
	 * Vector-matrix in-place multiplication.
	 * 
	 * Right-multiplies the current vector by the given matrix.
	 * The resulting vector has the equation \f$ v' = v^T \cdot M \f$.
	 * 
	 * @param m SFMatrix4 to multiply by
	 * @returns reference to this
	 */
	template <typename U> SFVec4<T>& operator*=(const SFMatrix4<U>& m) {
		return this->operator=(*this * m);
	}
};

class SFVec2f : public SFVec2<float> {
	typedef SFVec2f TYPE;
	inline X3DField::Type getType() const { return SFVEC2F; }
	inline string getTypeName() const { return "SFVec2f"; }
	static inline const SFVec2f& unwrap(const X3DField& f) {
		if (f.getType() != SFVEC2F)
			throw X3DError("base type mismatch");
		return static_cast<const SFVec2f&>(f);
	}
	virtual const SFVec2f& operator=(const X3DField& f) {
		return *this = unwrap(f);
	}
};

class SFVec2d : public SFVec2<double> {
	typedef SFVec2d TYPE;
	inline X3DField::Type getType() const { return SFVEC2D; }
	inline string getTypeName() const { return "SFVec2d"; }
	static inline const SFVec2d& unwrap(const X3DField& f) {
		if (f.getType() != SFVEC2D)
			throw X3DError("base type mismatch");
		return static_cast<const SFVec2d&>(f);
	}
	virtual const SFVec2d& operator=(const X3DField& f) {
		return *this = unwrap(f);
	}
};

class SFVec3f : public SFVec3<float> {
	typedef SFVec3f TYPE;
	inline X3DField::Type getType() const { return SFVEC3F; }
	inline string getTypeName() const { return "SFVec3f"; }
	static inline const SFVec3f& unwrap(const X3DField& f) {
		if (f.getType() != SFVEC3F)
			throw X3DError("base type mismatch");
		return static_cast<const SFVec3f&>(f);
	}
	virtual const SFVec3f& operator=(const X3DField& f) {
		return *this = unwrap(f);
	}
};

class SFVec3d : public SFVec2<double> {
	typedef SFVec3d TYPE;
	inline X3DField::Type getType() const { return SFVEC3D; }
	inline string getTypeName() const { return "SFVec3d"; }
	static inline const SFVec3d& unwrap(const X3DField& f) {
		if (f.getType() != SFVEC3D)
			throw X3DError("base type mismatch");
		return static_cast<const SFVec3d&>(f);
	}
	virtual const SFVec3d& operator=(const X3DField& f) {
		return *this = unwrap(f);
	}
};

class SFVec4f : public SFVec4<float> {
	typedef SFVec4f TYPE;
	inline X3DField::Type getType() const { return SFVEC4F; }
	inline string getTypeName() const { return "SFVec4f"; }
	static inline const SFVec4f& unwrap(const X3DField& f) {
		if (f.getType() != SFVEC4F)
			throw X3DError("base type mismatch");
		return static_cast<const SFVec4f&>(f);
	}
	virtual const SFVec4f& operator=(const X3DField& f) {
		return *this = unwrap(f);
	}
};

class SFVec4d : public SFVec4<double> {
	typedef SFVec4d TYPE;
	inline X3DField::Type getType() const { return SFVEC4D; }
	inline string getTypeName() const { return "SFVec4d"; }
	static inline const SFVec4d& unwrap(const X3DField& f) {
		if (f.getType() != SFVEC4D)
			throw X3DError("base type mismatch");
		return static_cast<const SFVec4d&>(f);
	}
	virtual const SFVec4d& operator=(const X3DField& f) {
		return *this = unwrap(f);
	}
};

}

#endif // #ifndef _X3D_SFVEC_H_
