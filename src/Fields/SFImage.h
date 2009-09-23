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

#ifndef _X3D_SFIMAGE_H_
#define _X3D_SFIMAGE_H_

#include "types.h"
#include <string.h>

namespace X3D {

/**
 * Generic image class. Image can be of arbitrary size. The pixel depth is
 * constrained to four modes, which defines how pixel values are structured:

 * - #components = 1: pixel = "I" (grayscale, opaque)
 * - #components = 2: pixel = "IA" (grayscale with transparency)
 * - #components = 3: pixel = "RGB" (full color, opaque)
 * - #components = 4: pixel = "RGBA" (full color with transparency)
 * 
 * where I = intensity, R = red, G = green, B = blue, and A = alpha.
 *
 * Pixels are stored in row-major order in the #bytes array, whose total
 * size is indicated by the #size.
 */
class SFImage {
protected:
	int width; ///< image width, in pixels
	int height; ///< image height, in pixels
	int components; ///< pixel depth (1-4). Can be 0 for empty image.
	int size; ///< size of #bytes array
	unsigned char* bytes; ///< packed pixel array
public:
	/**
	 * Default constructor.
	 * 
	 * Creates an empty image. All parameters are zero, and #bytes
	 * is set to NULL.
	 */
	explicit SFImage() { SFImage(0,0,0); }

	/**
     * Accessor for #width.
	 * 
	 * @returns image width
	 */
	int getWidth() { return width; }

	/**
	 * Accessor for #height.
	 * 
	 * @returns image height
	 */
	int getHeight() { return height; }

	/**
	 * Acessor for #components.
	 * 
	 * @returns image pixel depth
	 */
	int getComponents() { return components; }

	/**
	 * Accessor for #size.
	 * 
	 * @returns image byte array size
	 */
	int getSize() { return size; }

	/**
	 * Array accessor (mutable version).
	 * 
	 * Returns a pointer into the packed image pixels. This
	 * pointer is mutable, so you can write raw pixels into
	 * the image.
	 * 
	 * @returns mutable pointer to pixel array
	 */
	unsigned char* array() { return bytes; }

	/**
	 * Array accessor (const version).
	 * 
	 * Returns a pointer into the packed image pixels. This
	 * pointer is not mutable, so it's safe to use on an
	 * image which was declared const.
	 * 
	 * @returns const pointer to pixel array
	 */
	const unsigned char* array() const { return bytes; }

	/**
	 * Direct memory assignment.
	 * 
	 * Replaces the image bytes with a COPY of the input array.
	 * 
	 * @params array array of bytes to copy
	 * @returns reference to this
	 */
	SFImage& setBytes(const unsigned char* array) { if (size) memcpy(this->bytes, array, size); }

	// the rest are documented in SFImage.cc

	SFImage(const SFImage& i);
	SFImage(int width, int height, int components);
	SFImage(int width, int height, int components, unsigned char* pixels);
	virtual ~SFImage();
	virtual unsigned int getPixel(int x, int y) const;
	virtual void setPixel(int x, int y, unsigned int pixel);
	virtual SFColor getColor(int x, int y) const;
	virtual void setColor(int x, int y, const SFColor c);
	virtual SFColorRGBA getColorRGBA(int x, int y) const;
	virtual void setColorRGBA(int x, int y, const SFColorRGBA c);


private:
	
	void alloc(int width, int height, int components);
	unsigned char* locate(int x, int y);
	const unsigned char* locate(int x, int y) const;
};

}

#endif // #ifndef _X3D_SFIMAGE_H_
