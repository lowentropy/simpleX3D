#ifndef _X3D_SFMATRIX_H_
#define _X3D_SFMATRIX_H_

#include "types.h"

template <typename T>
class SFMatrix3 {
private:
	T data[9];
public:
	SFMatrix3() { static T i[] = {1,0,0,0,1,0,0,0,1}; *this = i; }
	template <typename U> SFMatrix3(const SFMatrix3<U>& m) { *this = m.array(); }
	template <typename U> SFMatrix3(U* a) { *this = a; }
	T& operator[](int index) { return data[index]; }
	const T& operator[](int index) const { return data[index]; }
	T* array() { return data; }
	const T* array() const { return data; }
	template <typename U> SFMatrix3<T>& operator=(U* a) {
		T* p = data;
		for (int i = 0; i < 9; i++)
			*p++ = *a++;
		return *this;
	}
};

template <typename T>
class SFMatrix4 {
private:
	T data[16];
public:
	SFMatrix4() { static T i[] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}; *this = i; }
	template <typename U> SFMatrix4(const SFMatrix4<U>& m) { *this = m.array(); }
	template <typename U> SFMatrix4(U* a) { *this = a; }
	T& operator[](int index) { return data[index]; }
	const T& operator[](int index) const { return data[index]; }
	T* array() { return data; }
	const T* array() const { return data; }
	template <typename U> SFMatrix4<T>& operator=(U* a) {
		T* p = data;
		for (int i = 0; i < 16; i++)
			*p++ = *a++;
		return *this;
	}
};

#endif // #ifndef _X3D_SFMATRIX_H_
