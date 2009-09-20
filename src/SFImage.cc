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
	const unsigned char* ptr = locate(x, y);
	unsigned int pixel = 0;
	for (int i = 0; i < components; i++)
		pixel = (pixel << 8) | *ptr++;
	return pixel;
}

/**
 * Inject a raw pixel value.
 * 
 * The unsigned int argument should only have a number of lower
 * bytes set equal to #components. The upper bytes will be ignored.
 * 
 * @param x X coordinate
 * @param y Y coordinate
 * @param pixel packed pixel value
 * @see getPixel
 */
void SFImage::setPixel(int x, int y, unsigned int pixel) {
	unsigned char* ptr = locate(x, y) + components;
	for (int i = 0; i < components; i++) {
		*--ptr = pixel & 255;
		pixel >>= 8;
	}
}

/**
 * Retrieve a pixel's RGB color.
 * 
 * The alpha channel, if present, is not returned. If the image
 * is grayscale, all three color channels are set equal to the
 * grayscale value.
 * 
 * @param x X coordinate
 * @param y Y coordinate
 * @returns RGB color for pixel
 * @see setColor
 */
SFColor SFImage::getColor(int x, int y) const {
	SFColor c;
	const unsigned char* ptr = locate(x, y);
	if (components < 3) {
		c.r = c.g = c.b = *ptr;
	} else {
		c.r = *ptr++;
		c.g = *ptr++;
		c.b = *ptr;
	}
	return c;
}

/**
 * Updates a pixel's RGB color.
 * 
 * If the image has an alpha channel, it is not changed. If the image
 * is grayscale, then the updated value will be the average intensity
 * of the given color.
 * 
 * @param x X coordinate
 * @param y Y coordinate
 * @param c RGB color to set
 * @see getColor
 */
void SFImage::setColor(int x, int y, const SFColor c) {
	unsigned char* ptr = locate(x, y);
	if (components < 3) {
		*ptr = (c.r + c.g + c.b) / 3;
	} else {
		*ptr++ = c.r;
		*ptr++ = c.g;
		*ptr++ = c.b;
	}
}

/**
 * Retrieve a pixel's RGBA color.
 * 
 * If the image does not have an alpha channel, the returned alpha will
 * be 255 (opaque). If the image is grayscale, all three color channels
 * will be set equal to the intensity value.
 * 
 * @param x X coordinate
 * @param y Y coordinate
 * @returns RGBA color for pixel
 * @see setColorRGBA
 */
SFColorRGBA SFImage::getColorRGBA(int x, int y) const {
	SFColorRGBA c;
	const unsigned char* ptr = locate(x, y);
	if (components < 3) {
		c.r = c.g = c.b = *ptr++;
	} else {
		c.r = *ptr++;
		c.g = *ptr++;
		c.b = *ptr++;
	}
	if (components % 2 == 0)
		c.a = *ptr;
	return c;
}

/**
 * Update a pixel's RGBA color.
 * 
 * If the image does not have an alpha channel, the alpha color value
 * is ignored. If the image is grayscale, the updated value will be
 * the average intensity of the color.
 * 
 * @param x X coordinate
 * @param y Y coordinate
 * @param c RGBA color to set
 * @see getColorRGBA
 */
void SFImage::setColorRGBA(int x, int y, const SFColorRGBA c) {
	unsigned char* ptr = locate(x, y);
	if (components < 3) {
		*ptr++ = (c.r + c.g + c.b) / 3;
	} else {
		*ptr++ = c.r;
		*ptr++ = c.g;
		*ptr++ = c.b;
	}
	if (components % 2 == 0)
		*ptr = c.a;
}

// PRIVATE STUFF HERE

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
