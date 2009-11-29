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

#include "internal/types.h"
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
class SFImage : public X3DField {
protected:
	int width; ///< image width, in pixels
	int height; ///< image height, in pixels
	int components; ///< pixel depth (1-4). Can be 0 for empty image.
	int size; ///< size of #bytes array
	unsigned char* bytes; ///< packed pixel array

public:

	// X3DField stuff

	typedef SFImage& TYPE;
	typedef const SFImage& CONST_TYPE;

    /// @returns SFIMAGE
	INLINE X3DField::Type getType() const { return X3DField::SFIMAGE; }

    /// Unwrap generic SFImage value
	INLINE static const SFImage& unwrap(const X3DField& f) {
		if (f.getType() != SFIMAGE)
			throw X3DError(
                string("base type mismatch; expected SFImage") +
                ", but was " + f.getTypeName());
		return static_cast<const SFImage&>(f);
	}

	INLINE static SFImage& unwrap(X3DField& f) {
		if (f.getType() != SFIMAGE)
			throw X3DError(
                string("base type mismatch; expected SFImage") +
                ", but was " + f.getTypeName());
		return static_cast<SFImage&>(f);
	}

    /// @returns native SFImage value
	INLINE SFImage& operator()() {
		return *this;
	}

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

    /// Copy constructor
	SFImage(const SFImage& i) {
		alloc(i.width, i.height, i.components);
		*this = i;
	}

    /**
     * Assignment operator.
     *
     * @param i the image to copy
     */
    const SFImage& operator=(const SFImage& i);

    /**
     * Generic comparison operator.
     *
     * @param f field to compare to
     * @returns if images are equal
     */
    bool operator==(const X3DField& f) const { return *this == unwrap(f); }

    /**
     * Generic comparison operator.
     *
     * @param f field to compare to
     * @returns if images are not equal
     */
    bool operator!=(const X3DField& f) const { return *this != unwrap(f); }

    /**
     * Native comparison operator.
     *
     * @param i image to compare to
     * @returns if images are equal
     */
    bool operator==(const SFImage& i) const;

    /**
     * Native comparison operator.
     *
     * @param i image to compare to
     * @returns if images are not equal
     */
    bool operator!=(const SFImage& i) const;

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
	SFImage(int width, int height, int components);

    /**
     * Raw copy constructor.
     *
     * This constructor creates a blank image as in SFImage(),
     * then copies image bytes directly between the #bytes pointers.
     *
     * @param width image width
     * @param height image height
     * @param components image depth (0-4)
     * @param pixels array to copy data from
     */
	SFImage(int width, int height, int components, unsigned char* pixels);

    /**
     * Image destructor. If bytes is not NULL,
     * it is freed.
     */
	virtual ~SFImage();

    /**
     * Direct memory assignment.
     *
     * Replaces the image bytes with a COPY of the input array.
     *
     * @param array array of bytes to copy
     * @returns reference to this
     */
	SFImage& setBytes(const unsigned char* array);

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
	virtual unsigned int getPixel(int x, int y) const;

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
	virtual void setPixel(int x, int y, unsigned int pixel);

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
	virtual SFColor getColor(int x, int y) const;

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
	virtual void setColor(int x, int y, const SFColor c);

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
	virtual SFColorRGBA getColorRGBA(int x, int y) const;

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
	virtual void setColorRGBA(int x, int y, const SFColorRGBA c);
	
    bool parse(istream& is);

    void print(ostream& os) const;

private:
	
    /**
     * Allocate space for new image data.
     * 
     * @param width image width
     * @param height image height
     * @param components image depth (0-4)
     */
	void alloc(int width, int height, int components);

    /**
     * Free and reallocate image space.
     * 
     * @param width image width
     * @param height image height
     * @param components image depth (0-4)
     */
	void realloc(int width, int height, int components);

    /**
     * Locate a pointer into the image bytes by its (X,Y) location.
     * 
     * @param x x coordinate
     * @param y y coordinate
     * @returns pointer into image memory
     */
	unsigned char* locate(int x, int y);

    /**
     * Locate a pointer into the image bytes by its (X,Y) location.
     * Const version.
     * 
     * @param x x coordinate
     * @param y y coordinate
     * @returns pointer into image memory
     */
	const unsigned char* locate(int x, int y) const;
};

}

#endif // #ifndef _X3D_SFIMAGE_H_
