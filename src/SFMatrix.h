#ifndef _X3D_SFMATRIX_H_
#define _X3D_SFMATRIX_H_

#include "types.h"

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
template <typename T>
class SFMatrix3 {
private:
	T data[9]; ///< private element array
public:
	/**
	 * Default constructor.
	 * 
	 * The default value for any matrix dimension is its identity matrix.
	 */ 
	SFMatrix3() { static T i[] = {1,0,0,0,1,0,0,0,1}; *this = i; }

	/**
	 * Copy constructor.
	 * 
	 * @param m matrix to copy from
	 */
	template <typename U> SFMatrix3(const SFMatrix3<U>& m) { *this = m.array(); }

	/**
	 * Array constructor.
	 * 
	 * Copy the elements of the given array directly into the matrix.
	 * 
	 * @param a array of matrix elements
	 */
	template <typename U> SFMatrix3(U* a) { *this = a; }

	/**
	 * Index operator (mutable version).
	 * 
	 * @params index element index
	 * @returns mutable pointer into the array elements
	 */
	T& operator[](int index) { return &data[index]; }

	/**
	 * Index operator (const version).
     *
	 * @params index element index
	 * @returns const pointer into the array elements
	 */
	const T& operator[](int index) const { return data[index]; }

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
	template <typename U> SFMatrix3<T>& operator=(const SFMatrix3<U> m) {
		return this->operator=(m.array());
	}

	/**
	 * Matrix-vector multiplication.
	 * 
	 * Left-multiplies the given vector by this matrix. The equation
	 * of the return value is \f$ v_2 = M * v_1 \f$.
	 * 
	 * @returns result of multiplication
	 */
	template <typename U> SFVec3<T> operator*(const SFVec3<U> v) const {
		SFVec3<T> w;
		const T* p1 = data;
		const U* p2 = &v.x;
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
	template <typename U> SFMatrix3<T> operator*(const SFMatrix3<U> m) const {
		const T* a = data;
		const U* b = m.array();
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
		return SFMatrix3<T>(c);
	}

	/**
	 * Matrix-matrix in-place multiplication.
	 * 
	 * @param m matrix to multiply by
	 * @returns reference to this
	 */
	template <typename U> SFMatrix3<T>& operator*=(const SFMatrix3<U> m) {
		const T* a = data;
		const U* b = m.array();
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

private:

	template <typename U> SFMatrix3<T>& operator=(U* a) {
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
template <typename T>
class SFMatrix4 {
private:
	T data[16]; ///< private element array
public:
	/**
	 * Default constructor.
	 * 
	 * The default value for any matrix dimension is its identity matrix.
	 */ 
	SFMatrix4() { static T i[] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}; *this = i; }

	/**
	 * Copy constructor.
	 * 
	 * @param m matrix to copy from
	 */
	template <typename U> SFMatrix4(const SFMatrix4<U>& m) { *this = m.array(); }

	/**
	 * Array constructor.
	 * 
	 * Copy the elements of the given array directly into the matrix.
	 * 
	 * @param a array of matrix elements
	 */
	template <typename U> SFMatrix4(U* a) { *this = a; }

	/**
	 * Index operator (mutable version).
	 * 
	 * @params index element index
	 * @returns mutable pointer into the array elements
	 */
	T& operator[](int index) { return &data[index]; }

	/**
	 * Index operator (const version).
     *
	 * @params index element index
	 * @returns const pointer into the array elements
	 */
	const T& operator[](int index) const { return data[index]; }

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
	template <typename U> SFMatrix4<T>& operator=(const SFMatrix4<U> m) {
		return this->operator=(m.array());
	}

	/**
	 * Matrix-vector multiplication.
	 * 
	 * Left-multiplies the given vector by this matrix. The equation
	 * of the return value is \f$ v_2 = M * v_1 \f$.
	 * 
	 * @returns result of multiplication
	 */
	template <typename U> SFVec4<T> operator*(const SFVec4<U>& v) const {
		SFVec4<T> w(0, 0, 0, 0);
		const T* p1 = data;
		const U* p2 = &v.x;
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
	template <typename U> SFMatrix4<T> operator*(const SFMatrix4<U> m) const {
		const T* a = data;
		const U* b = m.array();
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
		return SFMatrix3<T>(c);
	}

	/**
	 * Matrix-matrix in-place multiplication.
	 * 
	 * @param m matrix to multiply by
	 * @returns reference to this
	 */
	template <typename U> SFMatrix4<T>& operator*=(const SFMatrix4<U> m) {
		const T* a = data;
		const U* b = m.array();
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

	template <typename U> SFMatrix4<T>& operator=(U* a) {
		T* p = data;
		for (int i = 0; i < 16; i++)
			*p++ = *a++;
		return *this;
	}
};

#endif // #ifndef _X3D_SFMATRIX_H_
