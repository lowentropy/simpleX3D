#include "types.h"
#include <string.h>

SFImage::SFImage(const SFImage& i) {
	SFImage(i.width, i.height, i.components, i.bytes);
}

SFImage::SFImage(int width, int height, int components) {
	size = width * height * components;
	bytes = size ? new unsigned char[size] : NULL;
}

SFImage::SFImage(int width, int height, int components, unsigned char* bytes) {
	SFImage(width, height, components);
	if (size)
		memcpy(this->bytes, bytes, size);
}

SFImage::~SFImage() {
	if (bytes != NULL)
		delete[] bytes;
}

unsigned int SFImage::getPixel(int x, int y) const {
	int index = y * width + x;
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
			value = value << 8 | *ptr++;
			return value;
		case 4:
			return ((uint32_t*) bytes)[index];
	}
}

void SFImage::setPixel(int x, int y, unsigned int pixel) {
	int index = y * width + x;
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
			*ptr-- = pixel & 255;
			break;
		case 4:
			((uint32_t*) bytes)[index] = (uint32_t) pixel;
			break;
	}
}

SFColor SFImage::getColor(int x, int y) const {
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
			ptr = &bytes[(y * width + x) * 3];
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

SFColorRGBA SFImage::getColorRGBA(int x, int y) const {
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
			ptr = &bytes[(y * width + x) * 3];
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
