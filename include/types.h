#ifndef _THEATRE_X3D_TYPES_
#define _THEATRE_X3D_TYPES_

#include <string>
#include <vector>
#include <unistd.h>

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
public:
	int width;
	int height;
	int components;
	int size;
	unsigned char* bytes;
	SFImage(const SFImage& i);
	SFImage(int width, int height, int components);
	SFImage(int width, int height, int components, unsigned char* pixels);
	~SFImage();
	unsigned int getPixel(int x, int y) const;
	void setPixel(int x, int y, unsigned int pixel);
	SFColor getColor(int x, int y) const;
	void setColor(int x, int y, const SFColor c);
	SFColorRGBA getColorRGBA(int x, int y) const;
	void setColorRGBA(int x, int y, const SFColorRGBA c);
};

template <class T>
class Vec2 {
	T x;
	T y;
	template <class U> Vec2(Vec2<U> v) : x(v.x), y(v.y) {}
	Vec2(T x, T y) : x(x), y(y) {}
	T* array() { return &x; }
};

template <class T>
class Vec3 {
	T x;
	T y;
	T z;
	template <class U> Vec3(Vec3<U> v) : x(v.x), y(v.y), z(v.z) {}
	Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
	T* array() { return &x; }
};

template <class T>
class Vec4 {
	T x;
	T y;
	T z;
	T w;
	template <class U> Vec4(Vec4<U> v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
	Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	T* array() { return &x; }
};

template <class T>
class Matrix3 {
	Vec3<T> vec[3];
	template <class U> Matrix3(const Matrix3<U> m);
	template <class U> Matrix3(U* a);
	template <class U> Matrix3(Vec3<U>* v);
	T* array() { return &vec[0].x; }
};

template <class T>
class Matrix4 {
	Vec4<T> vec[4];
	template <class U> Matrix4(const Matrix4<U> m);
	template <class U> Matrix4(U* a);
	template <class U> Matrix4(Vec4<U>* v);
	T* array() { return &vec[0].x; }
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
