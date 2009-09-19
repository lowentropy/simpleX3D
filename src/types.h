#ifndef _THEATRE_X3D_TYPES_
#define _THEATRE_X3D_TYPES_

#include <string>
#include <vector>
#include <stdexcept>
#include <unistd.h>
#include <math.h>

class X3DError : public std::runtime_error {
public:
	X3DError(const char* message) : std::runtime_error(message) {}
};

class SFNode {
	// TODO
};

template <typename T> class SFMatrix3;
template <typename T> class SFMatrix4;

class SFColor {
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	SFColor() : r(0), g(0), b(0) {}
	SFColor(const SFColor& c) : r(c.r), g(c.g), b(c.b) {}
	SFColor(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}
	unsigned char* array() { return &r; }
};

class SFColorRGBA {
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	SFColorRGBA() : r(0), g(0), b(0), a(0) {}
	SFColorRGBA(const SFColor& c) : r(c.r), g(c.g), b(c.b), a(255) {}
	SFColorRGBA(const SFColorRGBA& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
	SFColorRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {}
	SFColorRGBA(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b), a(255) {}
	unsigned char* array() { return &r; }
};

class SFImage {
protected:
	int width;
	int height;
	int components;
	int size;
	unsigned char* bytes;
public:
	explicit SFImage() { SFImage(0,0,0); }
	SFImage(const SFImage& i);
	SFImage(int width, int height, int components);
	SFImage(int width, int height, int components, unsigned char* pixels);
	~SFImage();
	int getWidth() { return width; }
	int getHeight() { return height; }
	int getComponents() { return components; }
	int getSize() { return size; }
	unsigned char* array() { return bytes; }
	unsigned int getPixel(int x, int y) const;
	void setPixel(int x, int y, unsigned int pixel);
	SFColor getColor(int x, int y) const;
	void setColor(int x, int y, const SFColor c);
	SFColorRGBA getColorRGBA(int x, int y) const;
	void setColorRGBA(int x, int y, const SFColorRGBA c);
};

template <typename T>
class SFVec2 {
public:
	T x;
	T y;
	SFVec2() : x(0), y(0) {}
	template <typename U> SFVec2(SFVec2<U> v) : x(v.x), y(v.y) {}
	SFVec2(T x, T y) : x(x), y(y) {}
	T* array() { return &x; }
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
		return SFVec4<T>(x * s, y * s, z * s, w * s);
	}
	template <typename U> SFVec4<T> operator/(U s) const {
		return SFVec4<T>(x / s, y / s, z / s, w / s);
	}
	template <typename U> T operator*(SFVec4<U>& v) const {
		return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w);
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
		w *= s;
		return *this;
	}
	template <typename U> SFVec4<T>& operator/=(U s) {
		x /= s;
		y /= s;
		z /= s;
		w /= s;
		return *this;
	}
};

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


typedef bool SFBool;
typedef double SFDouble;
typedef float SFFloat;
typedef int32_t SFInt32;
typedef SFMatrix3<SFFloat> SFMatrix3f;
typedef SFMatrix3<SFDouble> SFMatrix3d;
typedef SFMatrix4<SFFloat> SFMatrix4f;
typedef SFMatrix4<SFDouble> SFMatrix4d;
typedef std::string SFString;
typedef double SFTime;
typedef SFVec2<SFFloat> SFVec2f;
typedef SFVec2<SFDouble> SFVec2d;
typedef SFVec3<SFFloat> SFVec3f;
typedef SFVec3<SFDouble> SFVec3d;
typedef SFVec4<SFFloat> SFVec4f;
typedef SFVec4<SFDouble> SFVec4d;

typedef std::vector<SFBool> MFBool;
typedef std::vector<SFColor> MFColor;
typedef std::vector<SFColorRGBA> MFColorRGBA;
typedef std::vector<SFDouble> MFDouble;
typedef std::vector<SFFloat> MFFloat;
typedef std::vector<SFImage> MFImage;
typedef std::vector<SFInt32> MFInt32;
typedef std::vector<SFMatrix3f> MFMatrix3f;
typedef std::vector<SFMatrix3d> MFMatrix3d;
typedef std::vector<SFMatrix4f> MFMatrix4f;
typedef std::vector<SFMatrix4d> MFMatrix4d;
typedef std::vector<SFNode> MFNode;
typedef std::vector<SFRotation> MFRotation;
typedef std::vector<SFString> MFString;
typedef std::vector<SFTime> MFTime;
typedef std::vector<SFVec2f> MFVec2f;
typedef std::vector<SFVec2d> MFVec2d;
typedef std::vector<SFVec3f> MFVec3f;
typedef std::vector<SFVec3d> MFVec3d;
typedef std::vector<SFVec4f> MFVec4f;
typedef std::vector<SFVec4d> MFVec4d;

#endif // #ifndef _THEATRE_X3D_TYPES_
