#include "types.h"
#include <string.h>

/**
 * Copy constructor.
 *
 * @param i the image to copy
 */
SFImage::SFImage(const SFImage& i) {
	SFImage(i.width, i.height, i.components, i.bytes);
}

/**
 * Empty image constructor.
 * 
 * The total size of the image will be
 * #width * #height * #components. If all
 * three parameters are zero, the bytes
 * array will be NULL.

 * @param width image width
 * @param height image height
 * @param components image depth (0-4)
 */
SFImage::SFImage(int width, int height, int components) {
	if (width < 0 || height < 0)
		throw X3DError("size cannot be negative");
	if (components < 0 || components > 4)
		throw X3DError("components must be in range [0,4]");
	if (components == 0 && (width !=0 || height != 0))
		throw X3DError("for non-empty image, components must be in range [1,4]");
	size = width * height * components;
	bytes = size ? new unsigned char[size] : NULL;
}

/**
 * Raw copy constructor.
 * 
 * This constructor creates a blank image as in SFImage(),
 * then copies image bytes directly between the #bytes pointers.
 * 
 * @param width image width
 * @param height image height
 * @param components image depth (0-4)
 * @param bytes array to copy data from
 */
SFImage::SFImage(int width, int height, int components, unsigned char* bytes) {
	SFImage(width, height, components);
	if (bytes == NULL)
		throw X3DError("trying to copy NULL bytes");
	if (size)
		memcpy(this->bytes, bytes, size);
}

/**
 * Image destructor. If bytes is not NULL,
 * it is freed.
 */
SFImage::~SFImage() {
	if (bytes != NULL)
		delete[] bytes;
}

/**
 * Extract a raw pixel value.
 * 
 * The value returned is an unsigned int, but will only
 * have a number of lower bytes set equal to #components.
 * The high bytes are always set to zero.
 * 
 * @param x X coordinate
 * @param y Y coordinate
 * @returns raw (packed) pixel
 * @see setPixel
 */
unsigned int SFImage::getPixel(int x, int y) const {
	int index = y * width + x;
	if (index < 0 || index >= width*height)
		throw X3DError("pixel coordinates out-of-bounds");
	unsigned char* ptr;
	unsigned int value;
	switch (components) {
		case 1:
			return ((uint8_t*) bytes)[index];
		case 2:
			return ((uint16_t*) bytes)[index];
		case 3:
			ptr = &bytes[index*3];
			value = *ptr++;
			value = value << 8 | *ptr++;
			value = value << 8 | *ptr;
			return value;
		case 4:
			return ((uint32_t*) bytes)[index];
	}
}

void SFImage::setPixel(int x, int y, unsigned int pixel) {
	int index = y * width + x;
	if (index < 0 || index >= width*height)
		throw X3DError("pixel coordinates out-of-bounds");
	unsigned char* ptr;
	switch (components) {
		case 1:
			((uint8_t*) bytes)[index] = (uint8_t) pixel;
			break;
		case 2:
			((uint16_t*) bytes)[index] = (uint16_t) pixel;
			break;
		case 3:
			ptr = &bytes[index*3+2];
			*ptr-- = pixel & 255; pixel >>= 8;
			*ptr-- = pixel & 255; pixel >>= 8;
			*ptr   = pixel & 255;
			break;
		case 4:
			((uint32_t*) bytes)[index] = (uint32_t) pixel;
			break;
	}
}

SFColor SFImage::getColor(int x, int y) const {
	int index;
	unsigned char* ptr;
	unsigned int pixel;
	unsigned char r, g, b;
	switch (components) {
		case 1:
			pixel = (unsigned char) getPixel(x, y);
			return SFColor(pixel, pixel, pixel);
		case 2:
			pixel = (unsigned char) (getPixel(x, y) >> 8);
			return SFColor(pixel, pixel, pixel);
		case 3:
			index = y * width + x;
			if (index < 0 || index >= width*height)
				throw X3DError("pixel coordinates out-of-bounds");
			ptr = &bytes[index * 3];
			return SFColor(*ptr++, *ptr++, *ptr);
		case 4:
			pixel = getPixel(x, y);
			pixel >>= 8;
			b = pixel & 255; pixel >>= 8;
			g = pixel & 255; pixel >>= 8;
			r = pixel;
			return SFColor(r, g, b);
	}
}

void SFImage::setColor(int x, int y, const SFColor c) {
	int index;
	unsigned int pixel;
	unsigned char* ptr;
	switch (components) {
		case 1:
			pixel = (c.r + c.g + c.b) / 3;
			setPixel(x, y, pixel);
			break;
		case 2:
			pixel = (c.r + c.g + c.b) / 3;
			setPixel(x, y, (pixel << 8) | 255);
			break;
		case 3:
			index = y * width + x;
			if (index < 0 || index >= width*height)
				throw X3DError("pixel coordinates out-of-bounds");
			ptr = &bytes[index * 3];
			*ptr++ = c.r;
			*ptr++ = c.g;
			*ptr   = c.b;
			break;
		case 4:
			pixel = (c.r << 24) | (c.g << 16) | (c.b << 8) | 255;
			setPixel(x, y, pixel);
			break;
	}
}

SFColorRGBA SFImage::getColorRGBA(int x, int y) const {
	int index;
	unsigned char c_pixel, alpha, value;
	unsigned short s_pixel;
	unsigned int i_pixel;
	unsigned char* ptr;
	unsigned char r, g, b, a;
	switch (components) {
		case 1:
			c_pixel = (unsigned char) getPixel(x, y);
			return SFColorRGBA(c_pixel, c_pixel, c_pixel, 255);
		case 2:
			s_pixel = (unsigned short) getPixel(x, y);
			alpha = (unsigned char) (s_pixel & 255);
			value = (unsigned char) ((s_pixel >> 8) & 255);
			return SFColorRGBA(value, value, value, alpha);
		case 3:
			index = y * width + x;
			if (index < 0 || index >= width*height)
				throw X3DError("pixel coordinates out-of-bounds");
			ptr = &bytes[index * 3];
			return SFColorRGBA(*ptr++, *ptr++, *ptr, 255);
		case 4:
			i_pixel = getPixel(x, y);
			a = i_pixel & 255; i_pixel >>= 8;
			b = i_pixel & 255; i_pixel >>= 8;
			g = i_pixel & 255; i_pixel >>= 8;
			r = i_pixel;
			return SFColorRGBA(r, g, b, a);
	}
}

void SFImage::setColorRGBA(int x, int y, const SFColorRGBA c) {
	int index;
	unsigned int pixel;
	unsigned char* ptr;
	switch (components) {
		case 1:
			pixel = (c.r + c.g + c.b) / 3;
			setPixel(x, y, pixel);
			break;
		case 2:
			pixel = (c.r + c.g + c.b) / 3;
			pixel = (pixel << 8) | c.a;
			setPixel(x, y, pixel);
			break;
		case 3:
			index = y * width + x;
			if (index < 0 || index >= width*height)
				throw X3DError("pixel coordinates out-of-bounds");
			ptr = &bytes[index * 3];
			*ptr++ = c.r;
			*ptr++ = c.g;
			*ptr   = c.b;
			break;
		case 4:
			pixel = (c.r << 24) | (c.g << 16) | (c.b << 8) | c.a;
			setPixel(x, y, pixel);
			break;
	}
}
