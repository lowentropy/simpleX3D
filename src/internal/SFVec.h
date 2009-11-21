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

#include "internal/X3DField.h"
#include <string.h>
#include <math.h>

using std::string;

namespace X3D {

// forward declarations
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
     * Comparison operator.
     * 
     * @param v vector to compare to
     * @returns whether vectors are equal
     */
    template <typename U> bool operator==(const SFVec2<U>& v) const {
        return (x == v.x) && (y == v.y);
    }

    /**
     * Comparison operator.
     * 
     * @param v vector to compare to
     * @returns whether vectors are not equal
     */
    template <typename U> bool operator!=(const SFVec2<U>& v) const {
        return (x != v.x) || (y != v.y);
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

    /**
     * Parse a string into a vector. Vectors are represented as floats
     * separated by whitespace. If parsing fails, the value of this vector
     * will be unchanged.
     * 
     * @param ss stream to read vector from
     * @returns whether parsing was successful.
     */
    bool parse(istream& ss) {
        T x, y;
        ss >> x >> y;
        if (ss.fail())
            return false;
        this->x = x;
        this->y = y;
        return true;
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
     * Comparison operator.
     * 
     * @param v vector to compare to
     * @returns whether vectors are equal
     */
    template <typename U> bool operator==(const SFVec3<U>& v) const {
        return (x == v.x) && (y == v.y) && (z == v.z);
    }

    /**
     * Comparison operator.
     * 
     * @param v vector to compare to
     * @returns whether vectors are not equal
     */
    template <typename U> bool operator!=(const SFVec3<U>& v) const {
        return (x != v.x) || (y != v.y) || (z != v.z);
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

    /**
     * Parse a string into a vector. Vectors are represented as floats
     * separated by whitespace. If parsing fails, the value of this vector
     * will be unchanged.
     * 
     * @param ss stream to read vector from
     * @returns whether parsing was successful.
     */
    bool parse(istream& ss) {
        T x, y, z;
        ss >> x >> y >> z;
        if (ss.fail())
            return false;
        this->x = x;
        this->y = y;
        this->z = z;
        return true;
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
     * Comparison operator.
     * 
     * @param v vector to compare to
     * @returns whether vectors are equal
     */
    template <typename U> bool operator==(const SFVec4<U>& v) const {
        return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
    }

    /**
     * Comparison operator.
     * 
     * @param v vector to compare to
     * @returns whether vectors are not equal
     */
    template <typename U> bool operator!=(const SFVec4<U>& v) const {
        return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w);
    }

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

    /**
     * Parse a string into a vector. Vectors are represented as floats
     * separated by whitespace. If parsing fails, the value of this vector
     * will be unchanged.
     * 
     * @param ss stream to read vector from
     * @returns whether parsing was successful.
     */
    bool parse(istream& ss) {
        T x, y, z, w;
        ss >> x >> y >> z >> w;
        if (ss.fail())
            return false;
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
        return true;
    }
};

/// 2d vector of floats
class SFVec2f : public SFVec2<float> {
public:
	typedef SFVec2f& TYPE;
	typedef const SFVec2f& CONST_TYPE;

	/**
	 * Default constructor.
	 * 
	 * Default value is (0,0).
	 */
	SFVec2f() : SFVec2<float>() {}

	/**
	 * Copy constructor.
	 * 
	 * @param v SFVec2 to copy from
	 */
	SFVec2f(const SFVec2f& v) : SFVec2<float>(v.x, v.y) {}

	/**
	 * Full constructor.
	 * 
	 * @param x X coordinate
	 * @param y Y coordinate
	 */
	template <typename U> SFVec2f(U x, U y) : SFVec2<float>(x, y) {}

    /// @returns SFVEC2F
	INLINE X3DField::Type getType() const { return X3DField::SFVEC2F; }

    /// Unwrap generic vector field
	static INLINE const SFVec2f& unwrap(const X3DField& f) {
		if (f.getType() != X3DField::SFVEC2F)
			throw X3DError("base type mismatch");
		return static_cast<const SFVec2f&>(f);
	}

    /// @returns native vector value
    INLINE SFVec2f& operator()() {
        return *this;
    }

    /**
     * Generic comparison operator.
     * 
     * @param f field to compare to
     * @returns whether vectors are equal.
     */
    bool operator==(const X3DField& f) const { 
        return this->SFVec2<float>::operator==(unwrap(f));
    }

    /**
     * Generic comparison operator.
     * 
     * @param f field to compare to
     * @returns whether vectors are not equal.
     */
    bool operator!=(const X3DField& f) const {
        return this->SFVec2<float>::operator!=(unwrap(f));
    }
};

/// 2d vector of doubles
class SFVec2d : public SFVec2<double> {
public:
	typedef SFVec2d& TYPE;
	typedef const SFVec2d& CONST_TYPE;

	/**
	 * Default constructor.
	 * 
	 * Default value is (0,0).
	 */
	SFVec2d() : SFVec2<double>() {}

	/**
	 * Copy constructor.
	 * 
	 * @param v SFVec2 to copy from
	 */
	SFVec2d(const SFVec2f& v) : SFVec2<double>(v.x, v.y) {}

	/**
	 * Copy constructor.
	 * 
	 * @param v SFVec2 to copy from
	 */
	SFVec2d(const SFVec2d& v) : SFVec2<double>(v.x, v.y) {}

	/**
	 * Full constructor.
	 * 
	 * @param x X coordinate
	 * @param y Y coordinate
	 */
	template <typename U> SFVec2d(U x, U y) : SFVec2<double>(x, y) {}

    /// @returns SFVEC2D
	INLINE X3DField::Type getType() const { return X3DField::SFVEC2D; }

    /// Unwrap generic vector field
	static INLINE const SFVec2d& unwrap(const X3DField& f) {
		if (f.getType() != X3DField::SFVEC2D)
			throw X3DError("base type mismatch");
		return static_cast<const SFVec2d&>(f);
	}

    /// @returns native vector value
    INLINE SFVec2d& operator()() {
        return *this;
    }

    /**
     * Generic comparison operator.
     * 
     * @param f field to compare to
     * @returns whether vectors are equal.
     */
    bool operator==(const X3DField& f) const {
        return this->SFVec2<double>::operator==(unwrap(f));
    }

    /**
     * Generic comparison operator.
     * 
     * @param f field to compare to
     * @returns whether vectors are not equal.
     */
    bool operator!=(const X3DField& f) const {
        return this->SFVec2<double>::operator!=(unwrap(f));
    }
};

/// 3d vector of floats
class SFVec3f : public SFVec3<float> {
public:
	typedef SFVec3f& TYPE;
	typedef const SFVec3f& CONST_TYPE;

	/**
	 * Default constructor.
	 * 
	 * Default value is (0,0,0).
	 */
	SFVec3f() : SFVec3<float>() {}

	/**
	 * Copy constructor.
	 * 
	 * @param v SFVec3 to copy from
	 */
	SFVec3f(const SFVec3f& v) : SFVec3<float>(v.x, v.y, v.z) {};

	/**
	 * Full constructor.
	 * 
	 * @param x X coordinate
	 * @param y Y coordinate
	 * @param z Z coordinate
	 */
	template <typename U> SFVec3f(U x, U y, U z) : SFVec3<float>(x, y) {}

    /// @returns SFVEC3F
	INLINE X3DField::Type getType() const { return X3DField::SFVEC3F; }

    /// Unwrap generic vector field
	static INLINE const SFVec3f& unwrap(const X3DField& f) {
		if (f.getType() != X3DField::SFVEC3F)
			throw X3DError("base type mismatch");
		return static_cast<const SFVec3f&>(f);
	}

    /// @returns native vector value
    INLINE SFVec3f& operator()() {
        return *this;
    }

    /**
     * Generic comparison operator.
     * 
     * @param f field to compare to
     * @returns whether vectors are equal.
     */
    bool operator==(const X3DField& f) const {
        return this->SFVec3<float>::operator==(unwrap(f));
    }

    /**
     * Generic comparison operator.
     * 
     * @param f field to compare to
     * @returns whether vectors are not equal.
     */
    bool operator!=(const X3DField& f) const {
        return this->SFVec3<float>::operator!=(unwrap(f));
    }
};

/// 3d vector of doubles
class SFVec3d : public SFVec3<double> {
public:
	typedef SFVec3d& TYPE;
	typedef const SFVec3d& CONST_TYPE;

	/**
	 * Default constructor.
	 * 
	 * Default value is (0,0,0).
	 */
	SFVec3d() : SFVec3<double>() {}

	/**
	 * Copy constructor.
	 * 
	 * @param v SFVec3 to copy from
	 */
	SFVec3d(const SFVec3f& v) : SFVec3<double>(v.x, v.y, v.z) {}

	/**
	 * Copy constructor.
	 * 
	 * @param v SFVec3 to copy from
	 */
	SFVec3d(const SFVec3d& v) : SFVec3<double>(v.x, v.y, v.z) {}

	/**
	 * Full constructor.
	 * 
	 * @param x X coordinate
	 * @param y Y coordinate
	 * @param z Z coordinate
	 */
	template <typename U> SFVec3d(U x, U y, U z) : SFVec3<double>(x, y, z) {}

    /// @returns SFVEC3D
	INLINE X3DField::Type getType() const { return X3DField::SFVEC3D; }

    /// Unwrap generic vector field.
	static const SFVec3d& unwrap(const X3DField& f) {
		if (f.getType() != X3DField::SFVEC3D)
			throw X3DError("base type mismatch");
		return static_cast<const SFVec3d&>(f);
	}

    /// @returns native vector value
    INLINE SFVec3d& operator()() {
        return *this;
    }

    /**
     * Generic comparison operator.
     * 
     * @param f field to compare to
     * @returns whether vectors are equal.
     */
    bool operator==(const X3DField& f) const {
        return this->SFVec3<double>::operator==(unwrap(f));
    }

    /**
     * Generic comparison operator.
     * 
     * @param f field to compare to
     * @returns whether vectors are not equal.
     */
    bool operator!=(const X3DField& f) const {
        return this->SFVec3<double>::operator!=(unwrap(f));
    }
};

/// 4d vector of floats
class SFVec4f : public SFVec4<float> {
public:
	typedef SFVec4f& TYPE;
	typedef const SFVec4f& CONST_TYPE;

	/**
	 * Default constructor.
	 * 
	 * Default value is (0,0,0,1).
	 */
	SFVec4f() : SFVec4<float>() {}

	/**
	 * Copy constructor.
	 * 
	 * @param v SFVec4 to copy from
	 */
	SFVec4f(const SFVec4f& v) : SFVec4<float>(v.x, v.y, v.z, v.w) {}

	/**
	 * Full constructor.
	 * 
	 * @param x X coordinate
	 * @param y Y coordinate
	 * @param z Z coordinate
	 * @param w W coordinate
	 */
	template <typename U> SFVec4f(U x, U y, U z, U w) : SFVec4<float>(x,y,z,w) {}

    /// @returns SFVEC4F
	INLINE X3DField::Type getType() const { return X3DField::SFVEC4F; }

    /// Unwrap generic vector field
	static INLINE const SFVec4f& unwrap(const X3DField& f) {
		if (f.getType() != X3DField::SFVEC4F)
			throw X3DError("base type mismatch");
		return static_cast<const SFVec4f&>(f);
	}

    /// @returns native vector value
    INLINE SFVec4f& operator()() {
        return *this;
    }

    /**
     * Generic comparison operator.
     * 
     * @param f field to compare to
     * @returns whether vectors are equal.
     */
    bool operator==(const X3DField& f) const {
        return this->SFVec4<float>::operator==(unwrap(f));
    }

    /**
     * Generic comparison operator.
     * 
     * @param f field to compare to
     * @returns whether vectors are not equal.
     */
    bool operator!=(const X3DField& f) const {
        return this->SFVec4<float>::operator!=(unwrap(f));
    }
};

/// 4d vector of doubles
class SFVec4d : public SFVec4<double> {
public:
	typedef SFVec4d& TYPE;
	typedef const SFVec4d& CONST_TYPE;

	/**
	 * Default constructor.
	 * 
	 * Default value is (0,0,0,1).
	 */
	SFVec4d() : SFVec4<double>() {}

	/**
	 * Copy constructor.
	 * 
	 * @param v SFVec4 to copy from
	 */
	SFVec4d(const SFVec4f& v) : SFVec4<double>(v.x, v.y, v.z, v.w) {}

	/**
	 * Copy constructor.
	 * 
	 * @param v SFVec4 to copy from
	 */
	SFVec4d(const SFVec4d& v) : SFVec4<double>(v.x, v.y, v.z, v.w) {}

	/**
	 * Full constructor.
	 * 
	 * @param x X coordinate
	 * @param y Y coordinate
	 * @param z Z coordinate
	 * @param w W coordinate
	 */
	template <typename U> SFVec4d(U x, U y, U z, U w) : SFVec4<double>(x,y,z,w) {}

    /// @returns SFVEC4D
	INLINE X3DField::Type getType() const { return X3DField::SFVEC4D; }

    /// Unwrap generic vector field.
	static INLINE const SFVec4d& unwrap(const X3DField& f) {
		if (f.getType() != X3DField::SFVEC4D)
			throw X3DError("base type mismatch");
		return static_cast<const SFVec4d&>(f);
	}

    /// @returns native vector value
    INLINE SFVec4d& operator()() {
        return *this;
    }

    /**
     * Generic comparison operator.
     * 
     * @param f field to compare to
     * @returns whether vectors are equal.
     */
    bool operator==(const X3DField& f) const {
        return this->SFVec4<double>::operator==(unwrap(f));
    }

    /**
     * Generic comparison operator.
     * 
     * @param f field to compare to
     * @returns whether vectors are not equal.
     */
    bool operator!=(const X3DField& f) const {
        return this->SFVec4<double>::operator!=(unwrap(f));
    }
};

}

#endif // #ifndef _X3D_SFVEC_H_
