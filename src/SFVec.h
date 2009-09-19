#ifndef _X3D_SFVEC_H_
#define _X3D_SFVEC_H_

#include "types.h"
#include <math.h>

template <typename T> class SFMatrix3;
template <typename T> class SFMatrix4;

template <typename T>
class SFVec2 {
public:
	T x;
	T y;
	SFVec2() : x(0), y(0) {}
	template <typename U> SFVec2(SFVec2<U> v) : x(v.x), y(v.y) {}
	SFVec2(T x, T y) : x(x), y(y) {}
	T* array() { return &x; }
	T mag() const { return sqrt(x*x + y*y); }
	SFVec2<T> norm() const {
		T m = mag();
		if (m != 0.0)
			return *this / m;
		else
			return SFVec2<T>();
	}
	SFVec2<T>& normalize() {
		T m = mag();
		if (m != 0.0)
			return *this /= m;
		else
			return *this = SFVec2<T>();
	}
	template <typename U> SFVec2<T> operator+(const SFVec2<U>& v) const {
		return SFVec2<T>(x + v.x, y + v.y);
	}
	template <typename U> SFVec2<T> operator-(const SFVec2<U>& v) const {
		return SFVec2<T>(x - v.x, y - v.y);
	}
	template <typename U> SFVec2<T> operator*(U s) const {
		return SFVec2<T>(x * s, y * s);
	}
	template <typename U> SFVec2<T> operator/(U s) const {
		return SFVec2<T>(x / s, y / s);
	}
	template <typename U> T operator*(SFVec2<U>& v) const {
		return (x * v.x) + (y * v.y);
	}
	template <typename U> SFVec2<T>& operator=(const SFVec2<U>& v) {
		x = v.x;
		y = v.y;
		return *this;
	}
	template <typename U> SFVec2<T>& operator+=(const SFVec2<U>& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	template <typename U> SFVec2<T>& operator-=(const SFVec2<U>& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	template <typename U> SFVec2<T>& operator*=(U s) {
		x *= s;
		y *= s;
		return *this;
	}
	template <typename U> SFVec2<T>& operator/=(U s) {
		x /= s;
		y /= s;
		return *this;
	}
};

template <typename T>
class SFVec3 {
public:
	T x;
	T y;
	T z;
	SFVec3() : x(0), y(0), z(0) {}
	template <typename U> SFVec3(SFVec3<U> v) : x(v.x), y(v.y), z(v.z) {}
	SFVec3(T x, T y, T z) : x(x), y(y), z(z) {}
	T* array() { return &x; }
	T mag() const { return sqrt(x*x + y*y + z*z); }
	SFVec3<T> norm() const {
		T m = mag();
		if (m != 0.0)
			return *this / m;
		else
			return SFVec3<T>();
	}
	SFVec3<T>& normalize() {
		T m = mag();
		if (m != 0.0)
			return *this /= m;
		else
			return *this = SFVec3<T>();
	}
	template <typename U> SFVec3<T> operator+(const SFVec3<U>& v) const {
		return SFVec3<T>(x + v.x, y + v.y, z + v.z);
	}
	template <typename U> SFVec3<T> operator-(const SFVec3<U>& v) const {
		return SFVec3<T>(x - v.x, y - v.y, z - v.z);
	}
	template <typename U> SFVec3<T> operator*(U s) const {
		return SFVec3<T>(x * s, y * s, z * s);
	}
	template <typename U> SFVec3<T> operator/(U s) const {
		return SFVec3<T>(x / s, y / s, z / s);
	}
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
	template <typename U> T operator*(SFVec3<U>& v) const {
		return (x * v.x) + (y * v.y) + (z * v.z);
	}
	template <typename U> SFVec3<T>& operator=(const SFVec3<U>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	template <typename U> SFVec3<T>& operator+=(const SFVec3<U>& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	template <typename U> SFVec3<T>& operator-=(const SFVec3<U>& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	template <typename U> SFVec3<T>& operator*=(U s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	template <typename U> SFVec3<T>& operator*=(const SFMatrix3<U>& m) {
		return this->operator=(*this * m);
	}
	template <typename U> SFVec3<T>& operator/=(U s) {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}
	template <typename U> SFVec3<T>& operator^(const SFVec3<U>& v) const {
		return SFVec3<T>(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		);
	}
};

template <typename T>
class SFVec4 {
public:
	T x;
	T y;
	T z;
	T w;
	SFVec4() : x(0), y(0), z(0), w(1) {}
	template <typename U> SFVec4(SFVec4<U> v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
	SFVec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	T* array() { return &x; }
	template <typename U> SFVec4<T> operator+(const SFVec4<U>& v) const {
		return SFVec4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
	}
	template <typename U> SFVec4<T> operator-(const SFVec4<U>& v) const {
		return SFVec4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
	}
	template <typename U> SFVec4<T> operator*(U s) const {
		return SFVec4<T>(x * s, y * s, z * s, w);
	}
	template <typename U> SFVec4<T> operator/(U s) const {
		return SFVec4<T>(x / s, y / s, z / s, w);
	}
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
	template <typename U> SFVec4<T>& operator=(const SFVec4<U>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}
	template <typename U> SFVec4<T>& operator+=(const SFVec4<U>& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}
	template <typename U> SFVec4<T>& operator-=(const SFVec4<U>& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
	template <typename U> SFVec4<T>& operator*=(U s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	template <typename U> SFVec4<T>& operator/=(U s) {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}
};

#endif // #ifndef _X3D_SFVEC_H_
