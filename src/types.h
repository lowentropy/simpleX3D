#ifndef _THEATRE_X3D_TYPES_
#define _THEATRE_X3D_TYPES_

#include <string>
#include <vector>
#include <stdexcept>
#include <unistd.h>

class X3DError : public std::runtime_error {
public:
	X3DError(const char* message) : std::runtime_error(message) {}
};

class SFNode {
	// TODO
};

class SFColor {
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
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
	SFColorRGBA(const SFColor& c) : r(c.r), g(c.g), b(c.b), a(255) {}
	SFColorRGBA(const SFColorRGBA& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
	SFColorRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {}
	SFColorRGBA(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b), a(255) {}
	unsigned char* array() { return &r; }
};

class SFRotation {
public:
	float x;
	float y;
	float z;
	float angle;
	SFRotation(const SFRotation& r) : x(r.x), y(r.y), z(r.z), angle(r.angle) {}
	SFRotation(float x, float y, float z, float a) : x(x), y(y), z(z), angle(a) {}
	float* array() { return &x; }
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
class Vec2 {
public:
	T x;
	T y;
	Vec2() : x(0), y(0) {}
	template <typename U> Vec2(Vec2<U> v) : x(v.x), y(v.y) {}
	Vec2(T x, T y) : x(x), y(y) {}
	T* array() { return &x; }
	template <typename U> Vec2<T> operator+(const Vec2<U>& v) const {
		return Vec2<T>(x + v.x, y + v.y);
	}
	template <typename U> Vec2<T> operator-(const Vec2<U>& v) const {
		return Vec2<T>(x - v.x, y - v.y);
	}
	template <typename U> Vec2<T> operator*(U s) const {
		return Vec2<T>(x * s, y * s);
	}
	template <typename U> Vec2<T> operator/(U s) const {
		return Vec2<T>(x / s, y / s);
	}
	template <typename U> T operator*(Vec2<U>& v) const {
		return (x * v.x) + (y * v.y);
	}
	template <typename U> Vec2<T>& operator=(const Vec2<U>& v) {
		x = v.x;
		y = v.y;
		return *this;
	}
	template <typename U> Vec2<T>& operator+=(const Vec2<U>& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	template <typename U> Vec2<T>& operator-=(const Vec2<U>& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	template <typename U> Vec2<T>& operator*=(U s) {
		x *= s;
		y *= s;
		return *this;
	}
	template <typename U> Vec2<T>& operator/=(U s) {
		x /= s;
		y /= s;
		return *this;
	}
};

template <typename T> class Matrix3;

template <typename T>
class Vec3 {
public:
	T x;
	T y;
	T z;
	Vec3() : x(0), y(0), z(0) {}
	template <typename U> Vec3(Vec3<U> v) : x(v.x), y(v.y), z(v.z) {}
	Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
	T* array() { return &x; }
	template <typename U> Vec3<T> operator+(const Vec3<U>& v) const {
		return Vec3<T>(x + v.x, y + v.y, z + v.z);
	}
	template <typename U> Vec3<T> operator-(const Vec3<U>& v) const {
		return Vec3<T>(x - v.x, y - v.y, z - v.z);
	}
	template <typename U> Vec3<T> operator*(U s) const {
		return Vec3<T>(x * s, y * s, z * s);
	}
	template <typename U> Vec3<T> operator/(U s) const {
		return Vec3<T>(x / s, y / s, z / s);
	}
	template <typename U> Vec3<T> operator*(const Matrix3<U>& m) const {
		Vec3<T> v;
		T* p1 = &x;
		U* p2 = m.array();
		for (int i = 0; i < 3; i++, p1++) {
			v.x += *p1 * *p2++;
			v.y += *p1 * *p2++;
			v.z += *p1 * *p2++;
		}
		return v;
	}
	template <typename U> T operator*(Vec3<U>& v) const {
		return (x * v.x) + (y * v.y) + (z * v.z);
	}
	template <typename U> Vec3<T>& operator=(const Vec3<U>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	template <typename U> Vec3<T>& operator+=(const Vec3<U>& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	template <typename U> Vec3<T>& operator-=(const Vec3<U>& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	template <typename U> Vec3<T>& operator*=(U s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	template <typename U> Vec3<T>& operator*=(const Matrix3<U>& m) {
		return this->operator=(*this * m);
	}
	template <typename U> Vec3<T>& operator/=(U s) {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}
	template <typename U> Vec3<T>& operator^(const Vec3<U>& v) const {
		return Vec3<T>(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		);
	}
};

template <typename T> class Matrix4;

template <typename T>
class Vec4 {
public:
	T x;
	T y;
	T z;
	T w;
	Vec4() : x(0), y(0), z(0), w(1) {}
	template <typename U> Vec4(Vec4<U> v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
	Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	T* array() { return &x; }
	template <typename U> Vec4<T> operator+(const Vec4<U>& v) const {
		return Vec4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
	}
	template <typename U> Vec4<T> operator-(const Vec4<U>& v) const {
		return Vec4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
	}
	template <typename U> Vec4<T> operator*(U s) const {
		return Vec4<T>(x * s, y * s, z * s, w * s);
	}
	template <typename U> Vec4<T> operator/(U s) const {
		return Vec4<T>(x / s, y / s, z / s, w / s);
	}
	template <typename U> T operator*(Vec4<U>& v) const {
		return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w);
	}
	template <typename U> Vec4<T> operator*(const Matrix4<U>& m) const {
		Vec4<T> v;
		T* p1 = &x;
		U* p2 = m.array();
		for (int i = 0; i < 4; i++, p1++) {
			v.x += *p1 * *p2++;
			v.y += *p1 * *p2++;
			v.z += *p1 * *p2++;
			v.w += *p1 * *p2++;
		}
		return v;
	}
	template <typename U> Vec4<T>& operator=(const Vec4<U>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}
	template <typename U> Vec4<T>& operator+=(const Vec4<U>& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}
	template <typename U> Vec4<T>& operator-=(const Vec4<U>& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
	template <typename U> Vec4<T>& operator*=(U s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}
	template <typename U> Vec4<T>& operator/=(U s) {
		x /= s;
		y /= s;
		z /= s;
		w /= s;
		return *this;
	}
};

template <typename T>
class Matrix3 {
private:
	T data[9];
public:
	Matrix3();
	template <typename U> Matrix3(const Matrix3<U>& m);
	template <typename U> Matrix3(U* a);
	T& operator[](int index) { return data[index]; }
	const T& operator[](int index) const { return data[index]; }
	T* array() { return data; }
};

template <typename T>
class Matrix4 {
private:
	T data[16];
public:
	Matrix4();
	template <typename U> Matrix4(const Matrix4<U>& m);
	template <typename U> Matrix4(U* a);
	T& operator[](int index) { return data[index]; }
	const T& operator[](int index) const { return data[index]; }
	T* array() { return data; }
};

typedef bool SFBool;
typedef double SFDouble;
typedef float SFFloat;
typedef int32_t SFInt32;
typedef Matrix3<SFFloat> SFMatrix3f;
typedef Matrix3<SFDouble> SFMatrix3d;
typedef Matrix4<SFFloat> SFMatrix4f;
typedef Matrix4<SFDouble> SFMatrix4d;
typedef std::string SFString;
typedef double SFTime;
typedef Vec2<SFFloat> SFVec2f;
typedef Vec2<SFDouble> SFVec2d;
typedef Vec3<SFFloat> SFVec3f;
typedef Vec3<SFDouble> SFVec3d;
typedef Vec4<SFFloat> SFVec4f;
typedef Vec4<SFDouble> SFVec4d;

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
