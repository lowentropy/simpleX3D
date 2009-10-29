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

#ifndef _X3D_SFCOLOR_H_
#define _X3D_SFCOLOR_H_

#include "internal/types.h"
#include <sstream>
#include <ostream>

namespace X3D {

/**
 * RGB color value.
 * 
 * Each channel (red, green, and blue) is an 8-bit
 * value represented by an unsigned char.
 */
class SFColor : public X3DField {
public:
	unsigned char r; ///< red channel
	unsigned char g; ///< green channel
	unsigned char b; ///< blue channel

	// X3DField stuff

	typedef const SFColor& TYPE;
	inline X3DField::Type getType() const { return SFCOLOR; }
	inline string getTypeName() const { return "SFColor"; }
	inline const SFColor& operator()() const { return *this; }
	inline static const SFColor& unwrap(const X3DField& f) {
		if (f.getType() != SFCOLOR)
			throw X3DError("base type mismatch");
		return static_cast<const SFColor&>(f);
	}
	inline const SFColor& operator=(const X3DField& f) {
		return *this = unwrap(f);
	}
	
	/**
	 * Default constructor.
	 * 
	 * Default color is black (#r = #g = #b = 0).
	 */
	SFColor() : r(0), g(0), b(0) {}

	/**
	 * Copy constructor.
	 * 
	 * @param c color to copy from
	 */
	SFColor(const SFColor& c) { *this = c; }

	/**
	 * Equals operator
	 * 
	 * @param c color to copy from
	 */
	inline const SFColor& operator=(const SFColor& c) {
		r = c.r; g = c.g; b = c.b;
		return *this;
	}

	/**
	 * Full constructor.
	 * 
	 * @param r red value
	 * @param g green value
	 * @param b blue value
	 */
	SFColor(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}

	/**
	 * Array accessor (mutable version).
	 * 
	 * Returns a pointer into the packed RGB values. This pointer
	 * is mutable, so you can write new values into the color.
	 * 
	 * @returns mutable pointer to RGB array
	 */
	unsigned char* array() { return &r; }

	/**
	 * Array accessor (const version).
     * 
	 * Returns a pointer into the packed RGB values. This pointer
	 * is not mutable, so it's safe to use on colors declared const.
	 * 
	 * @returns const pointer to RGB array
	 */
	const unsigned char* array() const { return &r; }

    /**
     * Equality test.
     *
     * @param c color to test
     * @returns whether colors are equal
     */
    bool operator==(const SFColor& c) const {
        return (r == c.r) && (g == c.g) && (b == c.b);
    }
};


/**
 * RGBA color value.
 * 
 * Each channel (red, green, blue, and alpha) is an 8-bit
 * value represented by an unsigned char. The alpha channel
 * controls opacity (0=transparent, 255=opaque).
 */
class SFColorRGBA : public X3DField {
public:
	unsigned char r; ///< red channel
	unsigned char g; ///< green channel
	unsigned char b; ///< blue channel
	unsigned char a; ///< alpha channel

	// X3DField stuff 

	typedef const SFColorRGBA& TYPE;
	inline X3DField::Type getType() const { return SFCOLORRGBA; }
	inline string getTypeName() const { return "SFColorRGBA"; }
	inline const SFColorRGBA& operator()() const { return *this; }
	inline static const SFColorRGBA& unwrap(const X3DField& f) {
		if (f.getType() != SFCOLORRGBA)
			throw X3DError("base type mismatch");
		return static_cast<const SFColorRGBA&>(f);
	}
	inline const SFColorRGBA& operator=(const X3DField& f) {
		return *this = unwrap(f);
	}

	/**
	 * Default constructor.
	 * 
	 * Default color is black transparent (0,0,0,0).
	 */
	SFColorRGBA() : r(0), g(0), b(0), a(0) {}

	/**
	 * Copy constructor.
	 * 
	 * Copies RGB values from given color and sets
	 * alpha to opaque (255).
     *
     * @param c color to copy from
	 */
	SFColorRGBA(const SFColor& c) { *this = c; }

	/**
	 * Copy constructor.
	 * 
	 * @param c color to copy from
	 */
	SFColorRGBA(const SFColorRGBA& c) { *this = c; }

	/**
	 * Equals operator.
	 * 
	 * @param c color to copy from, and set alpha to 255
	 */
	inline const SFColorRGBA& operator=(const SFColor& c) {
		r = c.r; g = c.g; b = c.b; a = 255;
		return *this;
	}

	/**
	 * Equals operator.
	 * 
	 * @param c color to copy from.
	 */
	inline const SFColorRGBA& operator=(const SFColorRGBA& c) {
		r = c.r; g = c.g; b = c.b; a = c.a;
		return *this;
	}

	/**
	 * Full constructor.
	 * 
	 * @param r red value
	 * @param g green value
	 * @param b blue value
	 * @param a alpha value
	 */
	SFColorRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {}

	/**
	 * Partial constructor.
	 * 
	 * Initializes alpha to default opaque (255).
	 * 
	 * @param r red value
	 * @param g green value
	 * @param b blue value
	 */
	SFColorRGBA(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b), a(255) {}

	/**
	 * Array accessor (mutable version).
	 * 
	 * Returns a pointer into the packed RGBA values. This pointer
	 * is mutable, so you can write new values int othe color.
	 * 
	 * @returns mutable pointer to RGBA array
	 */
	unsigned char* array() { return &r; }

	/**
	 * Array accessor (const version).
     * 
	 * Returns a pointer into the packed RGBA values. This pointer
	 * is not mutable, so it's safe to use on colors declared const.
	 * 
	 * @returns const pointer to RGBA array
	 */
	const unsigned char* array() const { return &r; }

    /**
     * Equality test.
     *
     * @param c color to test
     * @returns whether colors are equal
     */
    bool operator==(const SFColorRGBA& c) const {
        return (r == c.r) && (g == c.g) && (b == c.b) & (a == c.a);
    }
    
};

/**
 * Insert SFColorinto stream.
 */
std::ostream& operator<<(std::ostream& str, const SFColor& c);

/**
 * Insert SFColorRGBA into stream.
 */
std::ostream& operator<<(std::ostream& str, const SFColorRGBA& c);

}

#endif // #ifndef _X3D_SFCOLOR_H_
