#ifndef _X3D_SFIMAGE_H_
#define _X3D_SFIMAGE_H_

#include "types.h"

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

	// the rest are documented in SFImage.cc

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

#endif // #ifndef _X3D_SFIMAGE_H_
