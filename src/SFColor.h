#ifndef _X3D_SFCOLOR_H_
#define _X3D_SFCOLOR_H_

#include "types.h"

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

#endif // #ifndef _X3D_SFCOLOR_H_
