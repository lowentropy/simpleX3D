#ifndef _X3D_SFIMAGE_H_
#define _X3D_SFIMAGE_H_

#include "types.h"

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

#endif // #ifndef _X3D_SFIMAGE_H_
