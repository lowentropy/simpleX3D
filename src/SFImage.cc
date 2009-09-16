#include "types.h"

SFImage::SFImage(const SFImage& i) {
	this(i.width, i.height, i.components, i.bytes);
}

SFImage::SFImage(int width, int height, int components) {
	size = width * height * components;
	bytes = size ? new unsigned char[size] : NULL;
}

SFImage::SFImage(int width, int height, int components, unsigned char* bytes) {
	this(width, height, components);
	if (size)
		memcpy(this->bytes, bytes, size);
}

SFImage::~SFImage() {
	if (bytes != NULL)
		delete[] bytes;
}

unsigned int SFImage::getPixel(int x, int y) const {
	return this[y * width + x];
}

void SFImage::setPixel(int x, int y, unsigned int pixel) {
	this[y * width + x] = pixel;
}

unsigned int SFImage::operator[](int index) const {
	switch (components) {
		case 1:
			return ((uint8_t*) pixels)[index];
		case 2:
			return ((uint16_t*) pixels)[index];
		case 3:
			unsigned char* ptr = &pixels[index*3];
			unsigned int value = *ptr++;
			value = value << 8 | *ptr++;
			value = value << 8 | *ptr++;
			return value;
		case 4:
			return ((uint32_t*) pixels)[index];
	}
}

void SFImage::operator[]=(int index, unsigned int pixel) {
	switch (components) {
		case 1:
			((uint8_t*) pixels)[index] = (uint8_t) pixel;
			break;
		case 2:
			((uint16_t*) pixels)[index] = (uint16_t) pixel;
			break;
		case 3:
			unsigned char* ptr = &pixels[index*3+2];
			*ptr-- = pixel & 255; pixel >>= 8;
			*ptr-- = pixel & 255; pixel >>= 8;
			*ptr-- = pixel & 255;
			break;
		case 4:
			((uint32_t*) pixels)[index] = (uint32_t) pixel;
			break;
	}
}

SFColor SFImage::getColor(int x, int y) const {
	switch (components) {
		case 1:
			unsigned char pixel = (unsigned char) getPixel(x, y);
			return SFColor(pixel, pixel, pixel);
		case 2:
			unsigned char pixel = (unsigned char) (getPixel(x, y) >> 8);
			return SFColor(pixel, pixel, pixel);
		case 3:
			unsigned char* ptr = pixels[(y * width + x) * 3];
			return SFColor(*ptr++, *ptr++, *ptr);
		case 4:
			unsigned int pixel = getPixel(x, y);
			pixel >>= 8;
			unsigned char b = pixel & 255; pixel >>= 8;
			unsigned char g = pixel & 255; pixel >>= 8;
			unsigned char r = pixel;
			return SFColor(r, g, b);
	}
}

SFColorRGBA SFImage::getColorRGBA(int x, int y) const {
	switch (components) {
		case 1:
			unsigned char pixel = (unsigned char) getPixel(x, y);
			return SFColorRGBA(pixel, pixel, pixel, 255);
		case 2:
			unsigned short pixel = (unsigned short) getPixel(x, y);
			unsigned char alpha = (unsigned char) (pixel & 255);
			unsigned char value = (unsigned char) ((pixel >> 8) & 255);
			return SFColorRGBA(value, value, value, alpha);
		case 3:
			unsigned char* ptr = pixels[(y * width + x) * 3];
			return SFColorRGBA(*ptr++, *ptr++, *ptr, 255);
		case 4:
			unsigned int pixel = getPixel(x, y);
			unsigned char a = pixel & 255; pixel >>= 8;
			unsigned char b = pixel & 255; pixel >>= 8;
			unsigned char g = pixel & 255; pixel >>= 8;
			unsigned char r = pixel;
			return SFColorRGBA(r, g, b, a);
	}
}
