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

#ifndef _X3D_SFMATRIX_H_
#define _X3D_SFMATRIX_H_

#include "internal/SFVec.h"
#include <string.h>

using std::string;

namespace X3D {

/**
 * 3x3 Matrix.
 * 
 * This is the base class for SFMatrix3f and SFMatrix3d, having template parameters
 * SFFloat and SFDouble, respectively. In either instance, the matrix can generally
 * accept both types as arguments, and generally returns values and matrices of its
 * own type.
 * 
 * The matrix elements are packed in row-major order.
 */
template <typename T, X3DField::Type S>
class SFMatrix3 : public X3DField {
public:

    typedef SFMatrix3<T,S> TYPE;
    typedef SFMatrix3<T,S>& REF_TYPE;
    typedef const SFMatrix3<T,S>& CONST_TYPE;

    INLINE static X3DField::Type getStaticType() { return S; }
    INLINE X3DField::Type getType() const { return S; }

    static const SFMatrix3<T,S>& unwrap(const X3DField& field) {
        if (field.getType() != S)
            throw new X3DError(
                string("invalid type; expected ") +
                X3DField::getTypeName(S) + ", but was " +
                field.getTypeName());
        return *static_cast<const SFMatrix3<T,S>*>(&field);
    }
    const SFMatrix3<T,S>& operator()() const {
        return *this;
    }
    SFMatrix3<T,S>& operator()(const X3DField& field) {
        *this = unwrap(field);
        return *this;
    }
    bool operator==(const X3DField& field) const {
        return *this == unwrap(field);
    }
    bool operator!=(const X3DField& field) const {
        return *this != unwrap(field);
    }


private:
	T data[9]; ///< private element array

public:

	/**
	 * Default constructor.
	 * 
	 * The default value for any matrix dimension is its identity matrix.
	 */ 
	SFMatrix3() : X3DField() { static T i[] = {1,0,0,0,1,0,0,0,1}; *this = i; }

	/**
	 * Array constructor.
	 * 
	 * Copy the elements of the given array directly into the matrix.
	 * 
	 * @param a array of matrix elements
	 */
	template <typename U> SFMatrix3(U* a) : X3DField() { *this = a; }

	/**
	 * Index operator (mutable version).
	 * 
	 * @param index element index
	 * @returns mutable pointer into the array elements
	 */
	T& operator[](int index) { return &data[index]; }

	/**
	 * Index operator (const version).
     *
	 * @param index element index
	 * @returns const pointer into the array elements
	 */
	const T& operator[](int index) const { return data[index]; }

    /**
     * Sorting operator (for MFMatrix3X)
     */
    bool operator<(const SFMatrix3<T,S>& m) const {
        return this < &m;
    }

	/**
	 * Array access (mutable version).
	 * 
	 * @returns mutable pointer to the array elements
	 */
	T* array() { return data; }

	/**
	 * Array access (const version).
	 * 
	 * @returns const pointer to the array elements
	 */
	const T* array() const { return data; }

	/**
	 * Assignment operator.
	 * 
	 * @param m matrix to assign from
	 * @returns reference to this
	 */
	SFMatrix3<T,S>& operator=(const SFMatrix3<T,S>& m) {
		return this->operator=(m.array());
	}

    /**
     * Comparison operator.
     * 
     * @param m matrix to compare to
     * @returns whether matrices are equal
     */
    bool operator==(const SFMatrix3<T,S>& m) const {
        for (int i = 0; i < 9; i++)
            if (data[i] != m.data[i])
                return false;
        return true;
    }

    /**
     * Comparison operator.
     * 
     * @param m matrix to compare to
     * @returns whether matrices are not equal
     */
    bool operator!=(const SFMatrix3<T,S>& m) const {
        for (int i = 0; i < 9; i++)
            if (data[i] != m.data[i])
                return true;
        return false;
    }

	/**
	 * Matrix-vector multiplication.
	 * 
	 * Left-multiplies the given vector by this matrix. The equation
	 * of the return value is \f$ v_2 = M * v_1 \f$.
	 * 
	 * @returns result of multiplication
	 */
	SFVec3<T,S> operator*(const SFVec3<T,S>& v) const {
		SFVec3<T,S> w;
		const T* p1 = data;
		const T* p2 = &v.x;
		for (int i = 0; i < 3; i++, p1++, p2++) {
			p2 = &v.x;
			w.x += *(p1+0) * *p2;
			w.y += *(p1+3) * *p2;
			w.z += *(p1+6) * *p2;
		}
		return w;
	}

	/**
	 * Matrix-matrix multiplication.
	 *
	 * @param m matrix to multiply by
	 * @returns result of multiplication
	 */
	SFMatrix3<T,S> operator*(const SFMatrix3<T,S>& m) const {
		const T* a = data;
		const T* b = m.array();
		T c[9] = {
			a[0]*b[0] + a[1]*b[3] + a[2]*b[6],
			a[0]*b[1] + a[1]*b[4] + a[2]*b[7],
			a[0]*b[2] + a[1]*b[5] + a[2]*b[8],
			a[3]*b[0] + a[4]*b[3] + a[5]*b[6],
			a[3]*b[1] + a[4]*b[4] + a[5]*b[7],
			a[3]*b[2] + a[4]*b[5] + a[5]*b[8],
			a[6]*b[0] + a[7]*b[3] + a[8]*b[6],
			a[6]*b[1] + a[7]*b[4] + a[8]*b[7],
			a[6]*b[2] + a[7]*b[5] + a[8]*b[8]
		};
		return SFMatrix3<T,S>(c);
	}

	/**
	 * Matrix-matrix in-place multiplication.
	 * 
	 * @param m matrix to multiply by
	 * @returns reference to this
	 */
	SFMatrix3<T,S>& operator*=(const SFMatrix3<T,S>& m) {
		const T* a = data;
		const T* b = m.array();
		T c[9] = {
			a[0]*b[0] + a[1]*b[3] + a[2]*b[6],
			a[0]*b[1] + a[1]*b[4] + a[2]*b[7],
			a[0]*b[2] + a[1]*b[5] + a[2]*b[8],
			a[3]*b[0] + a[4]*b[3] + a[5]*b[6],
			a[3]*b[1] + a[4]*b[4] + a[5]*b[7],
			a[3]*b[2] + a[4]*b[5] + a[5]*b[8],
			a[6]*b[0] + a[7]*b[3] + a[8]*b[6],
			a[6]*b[1] + a[7]*b[4] + a[8]*b[7],
			a[6]*b[2] + a[7]*b[5] + a[8]*b[8]
		};
		return this->operator=(c);
	}

    bool parse(istream& is) {
        T arr[9];
        for (int i = 0; i < 9; i++) {
            is >> arr[i];
            if (is.fail())
                return false;
        }
        *this = arr;
        return true;
    }

    void print(ostream& os) const {
        for (int i = 0; i < 9; i++)
            os << data[i] << ' ';
    }

private:

    /**
     * Internal raw array assignment operator.
     * 
     * @param a new array of matrix data
     * @returns self-reference
     */
	template <typename U> SFMatrix3<T,S>& operator=(U* a) {
		T* p = data;
		for (int i = 0; i < 9; i++)
			*p++ = *a++;
		return *this;
	}
};

/**
 * 4x4 Matrix.
 * 
 * This is the base class for SFMatrix4f and SFMatrix4d, having template parameters
 * SFFloat and SFDouble, respectively. In either instance, the matrix can generally
 * accept both types as arguments, and generally returns values and matrices of its
 * own type.
 * 
 * The matrix elements are packed in row-major order.
 */
template <typename T, X3DField::Type S>
class SFMatrix4 : public X3DField {
public:

    typedef SFMatrix4<T,S> TYPE;
    typedef SFMatrix4<T,S>& REF_TYPE;
    typedef const SFMatrix4<T,S>& CONST_TYPE;

    INLINE static X3DField::Type getStaticType() { return S; }
    INLINE X3DField::Type getType() const { return S; }

    static const SFMatrix4<T,S>& unwrap(const X3DField& field) {
        if (field.getType() != S)
            throw new X3DError(
                string("invalid type; expected ") +
                X3DField::getTypeName(S) + ", but was " +
                field.getTypeName());
        return *static_cast<const SFMatrix4<T,S>*>(&field);
    }
    const SFMatrix4<T,S>& operator()() const {
        return *this;
    }
    SFMatrix4<T,S>& operator()(const X3DField& field) {
        *this = unwrap(field);
        return *this;
    }
    bool operator==(const X3DField& field) const {
        return *this == unwrap(field);
    }
    bool operator!=(const X3DField& field) const {
        return *this != unwrap(field);
    }

private:
	T data[16]; ///< private element array
public:
	/**
	 * Default constructor.
	 * 
	 * The default value for any matrix dimension is its identity matrix.
	 */ 
	SFMatrix4() : X3DField() { static T i[] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}; *this = i; }

	/**
	 * Array constructor.
	 * 
	 * Copy the elements of the given array directly into the matrix.
	 * 
	 * @param a array of matrix elements
	 */
	template <typename U> SFMatrix4(U* a) : X3DField() { *this = a; }

	/**
	 * Index operator (mutable version).
	 * 
	 * @param index element index
	 * @returns mutable pointer into the array elements
	 */
	T& operator[](int index) { return &data[index]; }

	/**
	 * Index operator (const version).
     *
	 * @param index element index
	 * @returns const pointer into the array elements
	 */
	const T& operator[](int index) const { return data[index]; }

    /**
     * Sorting operator (for MFMatrix4X)
     */
    bool operator<(const SFMatrix4<T,S>& m) const {
        return this < &m;
    }

	/**
	 * Array access (mutable version).
	 * 
	 * @returns mutable pointer to the array elements
	 */
	T* array() { return data; }

	/**
	 * Array access (const version).
	 * 
	 * @returns const pointer to the array elements
	 */
	const T* array() const { return data; }

	/**
	 * Assignment operator.
	 * 
	 * @param m matrix to assign from
	 * @returns reference to this
	 */
	SFMatrix4<T,S>& operator=(const SFMatrix4<T,S>& m) {
		return this->operator=(m.array());
	}

    /**
     * Comparison operator.
     * 
     * @param m matrix to compare to
     * @returns whether matrices are equal
     */
    bool operator==(const SFMatrix4<T,S>& m) const {
        for (int i = 0; i < 16; i++)
            if (data[i] != m.data[i])
                return false;
        return true;
    }

    /**
     * Comparison operator.
     * 
     * @param m matrix to compare to
     * @returns whether matrices are not equal
     */
    bool operator!=(const SFMatrix4<T,S>& m) const {
        for (int i = 0; i < 16; i++)
            if (data[i] != m.data[i])
                return true;
        return false;
    }

	/**
	 * Matrix-vector multiplication.
	 * 
	 * Left-multiplies the given vector by this matrix. The equation
	 * of the return value is \f$ v_2 = M * v_1 \f$.
	 * 
	 * @returns result of multiplication
	 */
	SFVec4<T,S> operator*(const SFVec4<T,S>& v) const {
		SFVec4<T,S> w(0, 0, 0, 0);
		const T* p1 = data;
		const T* p2 = &v.x;
		for (int i = 0; i < 4; i++, p1++, p2++) {
			w.x += *(p1+0) * *p2;
			w.y += *(p1+4) * *p2;
			w.z += *(p1+8) * *p2;
			w.w += *(p1+12) * *p2;
		}
		return w;
	}

	/**
	 * Matrix-matrix multiplication.
	 *
	 * @param m matrix to multiply by
	 * @returns result of multiplication
	 */
	SFMatrix4<T,S> operator*(const SFMatrix4<T,S>& m) const {
		const T* a = data;
		const T* b = m.array();
		T c[16] = {
			a[ 0]*b[ 0] + a[ 1]*b[ 4] + a[ 2]*b[ 8] + a[ 3]*b[12],
			a[ 0]*b[ 1] + a[ 1]*b[ 5] + a[ 2]*b[ 9] + a[ 3]*b[13],
			a[ 0]*b[ 2] + a[ 1]*b[ 6] + a[ 2]*b[10] + a[ 3]*b[14],
			a[ 0]*b[ 3] + a[ 1]*b[ 7] + a[ 2]*b[11] + a[ 3]*b[15],
			a[ 4]*b[ 0] + a[ 5]*b[ 4] + a[ 6]*b[ 8] + a[ 7]*b[12],
			a[ 4]*b[ 1] + a[ 5]*b[ 5] + a[ 6]*b[ 9] + a[ 7]*b[13],
			a[ 4]*b[ 2] + a[ 5]*b[ 6] + a[ 6]*b[10] + a[ 7]*b[14],
			a[ 4]*b[ 3] + a[ 5]*b[ 7] + a[ 6]*b[11] + a[ 7]*b[15],
			a[ 8]*b[ 0] + a[ 9]*b[ 4] + a[10]*b[ 8] + a[11]*b[12],
			a[ 8]*b[ 1] + a[ 9]*b[ 5] + a[10]*b[ 9] + a[11]*b[13],
			a[ 8]*b[ 2] + a[ 9]*b[ 6] + a[10]*b[10] + a[11]*b[14],
			a[ 8]*b[ 3] + a[ 9]*b[ 7] + a[10]*b[11] + a[11]*b[15],
			a[12]*b[ 0] + a[13]*b[ 4] + a[14]*b[ 8] + a[15]*b[12],
			a[12]*b[ 1] + a[13]*b[ 5] + a[14]*b[ 9] + a[15]*b[13],
			a[12]*b[ 2] + a[13]*b[ 6] + a[14]*b[10] + a[15]*b[14],
			a[12]*b[ 3] + a[13]*b[ 7] + a[14]*b[11] + a[15]*b[15]
		};
		return SFMatrix3<T,S>(c);
	}

	/**
	 * Matrix-matrix in-place multiplication.
	 * 
	 * @param m matrix to multiply by
	 * @returns reference to this
	 */
	SFMatrix4<T,S>& operator*=(const SFMatrix4<T,S>& m) {
		const T* a = data;
		const T* b = m.array();
		T c[16] = {
			a[ 0]*b[ 0] + a[ 1]*b[ 4] + a[ 2]*b[ 8] + a[ 3]*b[12],
			a[ 0]*b[ 1] + a[ 1]*b[ 5] + a[ 2]*b[ 9] + a[ 3]*b[13],
			a[ 0]*b[ 2] + a[ 1]*b[ 6] + a[ 2]*b[10] + a[ 3]*b[14],
			a[ 0]*b[ 3] + a[ 1]*b[ 7] + a[ 2]*b[11] + a[ 3]*b[15],
			a[ 4]*b[ 0] + a[ 5]*b[ 4] + a[ 6]*b[ 8] + a[ 7]*b[12],
			a[ 4]*b[ 1] + a[ 5]*b[ 5] + a[ 6]*b[ 9] + a[ 7]*b[13],
			a[ 4]*b[ 2] + a[ 5]*b[ 6] + a[ 6]*b[10] + a[ 7]*b[14],
			a[ 4]*b[ 3] + a[ 5]*b[ 7] + a[ 6]*b[11] + a[ 7]*b[15],
			a[ 8]*b[ 0] + a[ 9]*b[ 4] + a[10]*b[ 8] + a[11]*b[12],
			a[ 8]*b[ 1] + a[ 9]*b[ 5] + a[10]*b[ 9] + a[11]*b[13],
			a[ 8]*b[ 2] + a[ 9]*b[ 6] + a[10]*b[10] + a[11]*b[14],
			a[ 8]*b[ 3] + a[ 9]*b[ 7] + a[10]*b[11] + a[11]*b[15],
			a[12]*b[ 0] + a[13]*b[ 4] + a[14]*b[ 8] + a[15]*b[12],
			a[12]*b[ 1] + a[13]*b[ 5] + a[14]*b[ 9] + a[15]*b[13],
			a[12]*b[ 2] + a[13]*b[ 6] + a[14]*b[10] + a[15]*b[14],
			a[12]*b[ 3] + a[13]*b[ 7] + a[14]*b[11] + a[15]*b[15]
		};
		return this->operator=(c);
	}

private:

    /**
     * Raw array assignment operator.
     * 
     * @param a new array of matrix data
     * @returns self-reference
     */
	template <typename U> SFMatrix4<T,S>& operator=(U* a) {
		T* p = data;
		for (int i = 0; i < 16; i++)
			*p++ = *a++;
		return *this;
	}

public:
    bool parse(istream& is) {
        T arr[16];
        for (int i = 0; i < 16; i++) {
            is >> arr[i];
            if (is.fail())
                return false;
        }
        *this = arr;
        return true;
    }

    void print(ostream& os) const {
        for (int i = 0; i < 16; i++)
            os << data[i] << ' ';
    }

};

typedef SFMatrix3<float,X3DField::SFMATRIX3F> SFMatrix3f;
typedef SFMatrix3<double,X3DField::SFMATRIX3D> SFMatrix3d;
typedef SFMatrix4<float,X3DField::SFMATRIX4F> SFMatrix4f;
typedef SFMatrix4<double,X3DField::SFMATRIX4D> SFMatrix4d;

}

#endif // #ifndef _X3D_SFMATRIX_H_
