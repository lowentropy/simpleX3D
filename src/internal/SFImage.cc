/*
 * Copyright 2009 Nathan Matthews <lowentropy@gmail.com>
 *
 * This file is part of SimpleX3D.
 *
 * SimpleX3D is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SimpleX3D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SimpleX3D.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "internal/types.h"

using namespace X3D;

#define COLOR2CHAR(x) ((unsigned char) ((x) * 255))
#define CHAR2COLOR(x) (((float) x) / 255)

const SFImage& SFImage::operator=(const SFImage& i) {
	if (i.width != width || i.height != height || i.components != components)
		throw X3DError("mismatched image properties in =");
	setBytes(i.bytes);
}

bool SFImage::operator==(const SFImage& i) const {
    if (i.width != width || i.height != height || i.components != components)
        return false;
    return 0 == memcmp(bytes, i.bytes, size);
}

bool SFImage::operator!=(const SFImage& i) const {
    if (i.width != width || i.height != height || i.components != components)
        return true;
    return 0 != memcmp(bytes, i.bytes, size);
}

SFImage::SFImage(int width, int height, int components) {
	alloc(width, height, components);
}

void SFImage::alloc(int width, int height, int components) {
	if (width < 0 || height < 0)
		throw X3DError("size cannot be negative");
	if (components < 0 || components > 4)
		throw X3DError("components must be in range [0,4]");
	if (components == 0 && (width !=0 || height != 0))
		throw X3DError("for non-empty image, components must be in range [1,4]");
	this->width = width;
	this->height = height;
	this->components = components;
	this->size = width * height * components;
	bytes = this->size ? new unsigned char[size] : NULL;
}

SFImage::SFImage(int width, int height, int components, unsigned char* bytes) {
	alloc(width, height, components);
	setBytes(bytes);
}

SFImage::~SFImage() {
	if (bytes != NULL)
		delete[] bytes;
}

SFImage& SFImage::setBytes(const unsigned char* array) {
	if (size) {
		if (array == NULL)
			throw X3DError("tried to assign NULL");
		memcpy(this->bytes, array, size);
	}
	return *this;
}

unsigned int SFImage::getPixel(int x, int y) const {
	const unsigned char* ptr = locate(x, y);
	unsigned int pixel = 0;
	for (int i = 0; i < components; i++)
		pixel = (pixel << 8) | *ptr++;
	return pixel;
}

void SFImage::setPixel(int x, int y, unsigned int pixel) {
	unsigned char* ptr = locate(x, y) + components;
	for (int i = 0; i < components; i++) {
		*--ptr = pixel & 255;
		pixel >>= 8;
	}
}

SFColor SFImage::getColor(int x, int y) const {
	SFColor c;
	const unsigned char* ptr = locate(x, y);
	if (components < 3) {
		c.r = c.g = c.b = CHAR2COLOR(*ptr);
	} else {
		c.r = CHAR2COLOR(*ptr++);
		c.g = CHAR2COLOR(*ptr++);
		c.b = CHAR2COLOR(*ptr);
	}
	return c;
}

void SFImage::setColor(int x, int y, const SFColor c) {
	unsigned char* ptr = locate(x, y);
	if (components < 3) {
		*ptr = COLOR2CHAR((c.r + c.g + c.b) / 3);
	} else {
		*ptr++ = COLOR2CHAR(c.r);
		*ptr++ = COLOR2CHAR(c.g);
		*ptr++ = COLOR2CHAR(c.b);
	}
}

SFColorRGBA SFImage::getColorRGBA(int x, int y) const {
	SFColorRGBA c;
	const unsigned char* ptr = locate(x, y);
	if (components < 3) {
		c.r = c.g = c.b = CHAR2COLOR(*ptr++);
	} else {
		c.r = CHAR2COLOR(*ptr++);
		c.g = CHAR2COLOR(*ptr++);
		c.b = CHAR2COLOR(*ptr++);
	}
	c.a = (components % 2 == 0) ? CHAR2COLOR(*ptr) : 1;
	return c;
}

void SFImage::setColorRGBA(int x, int y, const SFColorRGBA c) {
	unsigned char* ptr = locate(x, y);
	if (components < 3) {
		*ptr++ = COLOR2CHAR((c.r + c.g + c.b) / 3);
	} else {
		*ptr++ = COLOR2CHAR(c.r);
		*ptr++ = COLOR2CHAR(c.g);
		*ptr++ = COLOR2CHAR(c.b);
	}
	if (components % 2 == 0)
		*ptr = COLOR2CHAR(c.a);
}

unsigned char* SFImage::locate(int x, int y) {
	int index = (y * width + x) * components;
	if (index < 0 || index >= size)
		throw X3DError("coordinates out of bounds");
	return &bytes[index];
}

const unsigned char* SFImage::locate(int x, int y) const {
	int index = (y * width + x) * components;
	if (index < 0 || index >= size)
		throw X3DError("coordinates out of bounds");
	return &bytes[index];
}
