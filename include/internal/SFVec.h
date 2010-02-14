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
#include <iostream>

using std::string;
using std::cout;
using std::endl;

namespace X3D {

// forward declarations
template <typename T, X3DField::Type S> class SFMatrix3;
template <typename T, X3DField::Type S> class SFMatrix4;

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
template <typename T, X3DField::Type S>
class SFVec2 : public X3DField {
public:

    typedef SFVec2<T,S> TYPE;
    typedef SFVec2<T,S>& REF_TYPE;
    typedef const SFVec2<T,S>& CONST_TYPE;
    
    INLINE static X3DField::Type getStaticType() { return S; }
    INLINE X3DField::Type getType() const { return S; }

    static const SFVec2<T,S>& unwrap(const X3DField& field) {
        if (field.getType() != S)
            throw new X3DError(
                string("invalid type; expected ") +
                X3DField::getTypeName(S) + ", but was " +
                field.getTypeName());
        return *static_cast<const SFVec2<T,S>*>(&field);
    }
    const SFVec2<T,S>& operator()() const {
        return *this;
    }
    SFVec2<T,S>& operator()(const X3DField& field) {
        *this = unwrap(field);
        return *this;
    }
    bool operator==(const X3DField& field) const {
        return *this == unwrap(field);
    }
    bool operator!=(const X3DField& field) const {
        return *this != unwrap(field);
    }
    bool equals(const X3DField& field) const {
        return this->equals(unwrap(field));
    }

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
	SFVec2<T,S> normal() const {
		T m = mag();
		if (m != 0.0)
			return *this / m;
		else
			return SFVec2<T,S>();
	}

	/** 
	 * Normalize this vector.
	 * 
	 * After calling, this vector will either have unit length, or,
	 * if it had zero length, it will be unchanged.
	 * 
	 * @returns reference to this
	 */
	SFVec2<T,S>& normalize() {
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
    bool operator==(const SFVec2<T,S>& v) const {
        return (x == v.x) && (y == v.y);
    }

    /**
     * Soft comparison operator.
     * 
     * @param v vector to compare to
     * @returns whether vectors are equal
     */
    bool equals(const SFVec2<T,S>& v) const {
        return X3DField::float_close(x, v.x)
            && X3DField::float_close(y, v.y);
    }

    /**
     * Comparison operator.
     * 
     * @param v vector to compare to
     * @returns whether vectors are not equal
     */
    bool operator!=(const SFVec2<T,S>& v) const {
        return (x != v.x) || (y != v.y);
    }

	/**
	 * Vector addition.
	 * 
	 * @param v vector to add to
	 * @returns vector sum
	 */
	SFVec2<T,S> operator+(const SFVec2<T,S>& v) const {
		return SFVec2<T,S>(x + v.x, y + v.y);
	}

	/**
	 * Vector subtraction.
	 * 
	 * @param v vector to subtract
	 * @returns vector difference
	 */
	SFVec2<T,S> operator-(const SFVec2<T,S>& v) const {
		return SFVec2<T,S>(x - v.x, y - v.y);
	}

	/**
	 * Vector-scalar multiplication.
	 * 
	 * @param s scalar to multiply by
	 * @returns scaled vector
	 */
	template <typename U> SFVec2<T,S> operator*(U s) const {
		return SFVec2<T,S>(x * s, y * s);
	}

	/**
	 * Vector-scalar division.
	 * 
	 * @param s scalar to divide by
	 * @returns scaled vector
	 */
	template <typename U> SFVec2<T,S> operator/(U s) const {
		return SFVec2<T,S>(x / s, y / s);
	}

	/**
	 * Vector dot-product.
	 * 
	 * Returns the value \f$ v_1 \cdot v_2 \f$.
	 * 
	 * @returns vector dot product.
	 */
	T operator*(SFVec2<T,S>& v) const {
		return (x * v.x) + (y * v.y);
	}

	/**
	 * Vector in-place addition.
	 * 
	 * @param v vector to add
	 * @returns reference to this
	 */
	SFVec2<T,S>& operator+=(const SFVec2<T,S>& v) {
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
	SFVec2<T,S>& operator-=(const SFVec2<T,S>& v) {
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
	template <typename U> SFVec2<T,S>& operator*=(U s) {
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
	template <typename U> SFVec2<T,S>& operator/=(U s) {
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

    void print(ostream& os) const {
        os << x << ' ' << y;
    }

    SFVec2<T,S>& operator=(const SFVec2<T,S>& v) {
        x = v.x;
        y = v.y;
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
template <typename T, X3DField::Type S>
class SFVec3 : public X3DField {
public:

    typedef SFVec3<T,S> TYPE;
    typedef SFVec3<T,S>& REF_TYPE;
    typedef const SFVec3<T,S>& CONST_TYPE;
    
    INLINE static X3DField::Type getStaticType() { return S; }
    INLINE X3DField::Type getType() const { return S; }

    static const SFVec3<T,S>& unwrap(const X3DField& field) {
        if (field.getType() != S)
            throw new X3DError(
                string("invalid type; expected ") +
                X3DField::getTypeName(S) + ", but was " +
                field.getTypeName());
        return *static_cast<const SFVec3<T,S>*>(&field);
    }
    const SFVec3<T,S>& operator()() const {
        return *this;
    }
    SFVec3<T,S>& operator()(const X3DField& field) {
        *this = unwrap(field);
        return *this;
    }
    bool operator==(const X3DField& field) const {
        return *this == unwrap(field);
    }
    bool operator!=(const X3DField& field) const {
        return *this != unwrap(field);
    }
    bool equals(const X3DField& field) const {
        return this->equals(unwrap(field));
    }

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
	SFVec3<T,S> norm() const {
		T m = mag();
		if (m != 0.0)
			return *this / m;
		else
			return SFVec3<T,S>();
	}

	/** 
	 * Normalize this vector.
	 * 
	 * After calling, this vector will either have unit length, or,
	 * if it had zero length, it will be unchanged.
	 * 
	 * @returns reference to this
	 */
	SFVec3<T,S>& normalize() {
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
    bool operator==(const SFVec3<T,S>& v) const {
        return (x == v.x) && (y == v.y) && (z == v.z);
    }

    /**
     * Soft comparison operator.
     * 
     * @param v vector to compare to
     * @returns whether vectors are equal
     */
    bool equals(const SFVec3<T,S>& v) const {
        return X3DField::float_close(x, v.x)
            && X3DField::float_close(y, v.y)
            && X3DField::float_close(z, v.z);
    }

    /**
     * Comparison operator.
     * 
     * @param v vector to compare to
     * @returns whether vectors are not equal
     */
    bool operator!=(const SFVec3<T,S>& v) const {
        return (x != v.x) || (y != v.y) || (z != v.z);
    }

	/**
	 * Vector addition.
	 * 
	 * @param v vector to add to
	 * @returns vector sum
	 */
	SFVec3<T,S> operator+(const SFVec3<T,S>& v) const {
		return SFVec3<T,S>(x + v.x, y + v.y, z + v.z);
	}

	/**
	 * Vector subtraction.
	 * 
	 * @param v vector to subtract
	 * @returns vector difference
	 */
	SFVec3<T,S> operator-(const SFVec3<T,S>& v) const {
		return SFVec3<T,S>(x - v.x, y - v.y, z - v.z);
	}

	/**
	 * Vector-scalar multiplication.
	 * 
	 * @param s scalar to multiply by
	 * @returns scaled vector
	 */
	template <typename U> SFVec3<T,S> operator*(U s) const {
		return SFVec3<T,S>(x * s, y * s, z * s);
	}

	/**
	 * Vector-scalar division.
	 * 
	 * @param s scalar to divide by
	 * @returns scaled vector
	 */
	template <typename U> SFVec3<T,S> operator/(U s) const {
		return SFVec3<T,S>(x / s, y / s, z / s);
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
	SFVec3<T,S> operator*(const SFMatrix3<T,S>& m) const {
		SFVec3<T,S> v;
		const T* p1 = &x;
		const T* p2 = m.array();
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
	T operator*(SFVec3<T,S>& v) const {
		return (x * v.x) + (y * v.y) + (z * v.z);
	}

	/**
	 * Vector in-place addition.
	 * 
	 * @param v vector to add
	 * @returns reference to this
	 */
	SFVec3<T,S>& operator+=(const SFVec3<T,S>& v) {
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
	SFVec3<T,S>& operator-=(const SFVec3<T,S>& v) {
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
	template <typename U> SFVec3<T,S>& operator*=(U s) {
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
	SFVec3<T,S>& operator*=(const SFMatrix3<T,S>& m) {
        SFVec3<T,S> v = *this * m;
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
	}

	/**
	 * Vector in-place scalar division.
	 * 
	 * @param s scalar to divide by
	 * @returns reference to this
	 */
	template <typename U> SFVec3<T,S>& operator/=(U s) {
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
	SFVec3<T,S> operator^(const SFVec3<T,S>& v) const {
		return SFVec3<T,S>(
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

    void print(ostream& os) const {
        os << x << ' ' << y << ' ' << z;
    }

    SFVec3<T,S>& operator=(const SFVec3<T,S>& v) {
        x = v.x;
        y = v.y;
        z = v.z;
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
template <typename T, X3DField::Type S>
class SFVec4 : public X3DField {
public:

    typedef SFVec4<T,S> TYPE;
    typedef SFVec4<T,S>& REF_TYPE;
    typedef const SFVec4<T,S>& CONST_TYPE;
    
    INLINE static X3DField::Type getStaticType() { return S; }
    INLINE X3DField::Type getType() const { return S; }

    static const SFVec4<T,S>& unwrap(const X3DField& field) {
        if (field.getType() != S)
            throw new X3DError(
                string("invalid type; expected ") +
                X3DField::getTypeName(S) + ", but was " +
                field.getTypeName());
        return *static_cast<const SFVec4<T,S>*>(&field);
    }
    const SFVec4<T,S>& operator()() const {
        return *this;
    }
    SFVec4<T,S>& operator()(const X3DField& field) {
        *this = unwrap(field);
        return *this;
    }
    bool operator==(const X3DField& field) const {
        return *this == unwrap(field);
    }
    bool operator!=(const X3DField& field) const {
        return *this != unwrap(field);
    }
    bool equals(const X3DField& field) const {
        return this->equals(unwrap(field));
    }

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
	SFVec4(const SFVec4<T,S>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

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
    bool operator==(const SFVec4<T,S>& v) const {
        return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
    }

    /**
     * Soft comparison operator.
     * 
     * @param v vector to compare to
     * @returns whether vectors are equal
     */
    bool equals(const SFVec4<T,S>& v) const {
        return X3DField::float_close(x, v.x)
            && X3DField::float_close(y, v.y)
            && X3DField::float_close(z, v.z)
            && X3DField::float_close(w, v.w);
    }

    /**
     * Comparison operator.
     * 
     * @param v vector to compare to
     * @returns whether vectors are not equal
     */
    bool operator!=(const SFVec4<T,S>& v) const {
        return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w);
    }

	/**
	 * Vector addition.
	 * 
	 * @param v vector to add to
	 * @returns vector sum
	 */
	SFVec4<T,S> operator+(const SFVec4<T,S>& v) const {
		return SFVec4<T,S>(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	/**
	 * Vector subtraction.
	 * 
	 * @param v vector to subtract
	 * @returns vector difference
	 */
	SFVec4<T,S> operator-(const SFVec4<T,S>& v) const {
		return SFVec4<T,S>(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	/**
	 * Vector-scalar multiplication.
	 * 
	 * Note that the homogeneous coordinate #w is not scaled.
	 * 
	 * @param s scalar to multiply by
	 * @returns scaled vector
	 */
	template <typename U> SFVec4<T,S> operator*(U s) const {
		return SFVec4<T,S>(x * s, y * s, z * s, w);
	}

	/**
	 * Vector-scalar division.
	 * 
	 * Note that the homogeneous coordinate #w is not scaled.
	 * 
	 * @param s scalar to divide by
	 * @returns scaled vector
	 */
	template <typename U> SFVec4<T,S> operator/(U s) const {
		return SFVec4<T,S>(x / s, y / s, z / s, w);
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
	SFVec4<T,S> operator*(const SFMatrix4<T,S>& m) const {
		SFVec4<T,S> v(0,0,0,0);
		const T* p1 = &x;
		const T* p2 = m.array();
		for (int i = 0; i < 4; i++, p1++) {
			v.x += *p1 * *p2++;
			v.y += *p1 * *p2++;
			v.z += *p1 * *p2++;
			v.w += *p1 * *p2++;
		}
		return v;
	}

	/**
	 * Vector in-place addition.
	 * 
	 * @param v vector to add
	 * @returns reference to this
	 */
	SFVec4<T,S>& operator+=(const SFVec4<T,S>& v) {
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
	SFVec4<T,S>& operator-=(const SFVec4<T,S>& v) {
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
	template <typename U> SFVec4<T,S>& operator*=(U s) {
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
	template <typename U> SFVec4<T,S>& operator/=(U s) {
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
	SFVec4<T,S>& operator*=(const SFMatrix4<T,S>& m) {
        SFVec4<T,S> v = *this * m;
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
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

    void print(ostream& os) const {
        os << x << ' ' << y << ' ' << z << ' ' << w;
    }

    SFVec4<T,S>& operator=(const SFVec4<T,S>& v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
};

typedef SFVec2<float,X3DField::SFVEC2F> SFVec2f;
typedef SFVec2<double,X3DField::SFVEC2D> SFVec2d;
typedef SFVec3<float,X3DField::SFVEC3F> SFVec3f;
typedef SFVec3<double,X3DField::SFVEC3D> SFVec3d;
typedef SFVec4<float,X3DField::SFVEC4F> SFVec4f;
typedef SFVec4<double,X3DField::SFVEC4D> SFVec4d;

}

#endif // #ifndef _X3D_SFVEC_H_
