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

#include "internal/X3DField.h"
#include <sstream>
#include <ostream>

namespace X3D {

/**
 * RGB color value.
 * 
 * Each channel (red, green, and blue) is a floating-point
 * value represented by an char.
 */
class SFColor : public X3DField {
public:
	float r; ///< red channel
	float g; ///< green channel
	float b; ///< blue channel

	// X3DField stuff

	typedef SFColor& TYPE;
    typedef const SFColor& CONST_TYPE;

    /// @returns SFCOLOR
	INLINE X3DField::Type getType() const { return X3DField::SFCOLOR; }

    /// @returns native SFColor value
	INLINE SFColor& operator()() { return *this; }

    /// Unwraps generic SFColor value
	INLINE static const SFColor& unwrap(const X3DField& f) {
		if (f.getType() != SFCOLOR)
			throw X3DError(
                string("base type mismatch; expected SFColor") +
                ", but was " + f.getTypeName());
		return static_cast<const SFColor&>(f);
	}

    /// Unwraps generic SFColor value
	INLINE static SFColor& unwrap(X3DField& f) {
		if (f.getType() != SFCOLOR)
			throw X3DError(
                string("base type mismatch; expected SFColor") +
                ", but was " + f.getTypeName());
		return static_cast<SFColor&>(f);
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
     * Sorting operator (for MFColor).
     */
    INLINE bool operator<(const SFColor& c) const {
        return this < &c;
    }

	/**
	 * Equals operator
	 * 
	 * @param c color to copy from
	 */
	INLINE SFColor& operator=(const SFColor& c) {
		r = c.r; g = c.g; b = c.b;
		return *this;
	}

    /// High-level generic assignment operator
    SFColor& operator()(const X3DField& f) {
        return *this = unwrap(f);
    }

	/**
	 * Full constructor.
	 * 
	 * @param r red value
	 * @param g green value
	 * @param b blue value
	 */
	SFColor(float r, float g, float b) : r(r), g(g), b(b) {}

	/**
	 * Array accessor (mutable version).
	 * 
	 * Returns a pointer into the packed RGB values. This pointer
	 * is mutable, so you can write new values into the color.
	 * 
	 * @returns mutable pointer to RGB array
	 */
	float* array() { return &r; }

	/**
	 * Array accessor (const version).
     * 
	 * Returns a pointer into the packed RGB values. This pointer
	 * is not mutable, so it's safe to use on colors declared const.
	 * 
	 * @returns const pointer to RGB array
	 */
	const float* array() const { return &r; }

    /**
     * Equality test.
     *
     * @param c color to test
     * @returns whether colors are equal
     */
    bool operator==(const SFColor& c) const {
        return (r == c.r) && (g == c.g) && (b == c.b);
    }

    /**
     * Equality test.
     *
     * @param c color to test
     * @returns whether colors are not equal
     */
    bool operator!=(const SFColor& c) const {
        return (r != c.r) || (g != c.g) || (b != c.b);
    }

    /**
     * Generic equality test.
     * 
     * @param f field to test
     * @returns whether field is equal
     */
    bool operator==(const X3DField& f) const { return *this == unwrap(f); }

    /**
     * Generic equality test.
     * 
     * @param f field to test
     * @returns whether field is not equal
     */
    bool operator!=(const X3DField& f) const { return *this != unwrap(f); }

    bool parse(istream& is) {
        float r, g, b;
        is >> r >> g >> b;
        if (is.fail())
            return false;
        if (r < 0 || r > 1 ||
            g < 0 || g > 1 ||
            b < 0 || b > 1)
            return false;
        this->r = r;
        this->g = g;
        this->b = b;
        return true;
    }

    void print(ostream& os) const {
        os << r << ' ' << g << ' ' << b;
    }
};


/**
 * RGBA color value.
 * 
 * Each channel (red, green, blue, and alpha) is a floating-point
 * value represented by an char. The alpha channel
 * controls opacity (0=transparent, 1=opaque).
 */
class SFColorRGBA : public X3DField {
public:
	float r; ///< red channel
	float g; ///< green channel
	float b; ///< blue channel
	float a; ///< alpha channel

	// X3DField stuff 

	typedef SFColorRGBA& TYPE;
	typedef const SFColorRGBA& CONST_TYPE;

    /// @returns SFCOLORRGBA
	INLINE X3DField::Type getType() const { return SFCOLORRGBA; }

    /// @returns native SFColorRGBA value
	INLINE SFColorRGBA& operator()() { return *this; }

    /// Unwrap generic SFColorRGBA value
	INLINE static const SFColorRGBA& unwrap(const X3DField& f) {
		if (f.getType() != SFCOLORRGBA)
			throw X3DError(
                string("base type mismatch; expected SFColorRGBA") +
                ", but was " + f.getTypeName());
		return static_cast<const SFColorRGBA&>(f);
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
	 * alpha to opaque (1.0).
     *
     * @param c color to copy from
	 */
	SFColorRGBA(const SFColor& c) { *this = c; }

    /**
     * Sorting operator (for MFColorRGBA).
     */
    INLINE bool operator<(const SFColorRGBA& c) const {
        return this < &c;
    }

	/**
	 * Copy constructor.
	 * 
	 * @param c color to copy from
	 */
	SFColorRGBA(const SFColorRGBA& c) { *this = c; }

	/**
	 * Equals operator.
	 * 
	 * @param c color to copy from, and set alpha to 1.0
	 */
	INLINE SFColorRGBA& operator=(const SFColor& c) {
		r = c.r; g = c.g; b = c.b; a = 1;
		return *this;
	}

	/**
	 * Equals operator.
	 * 
	 * @param c color to copy from.
	 */
	INLINE SFColorRGBA& operator=(const SFColorRGBA& c) {
		r = c.r; g = c.g; b = c.b; a = c.a;
		return *this;
	}

    /// High-level generic assignment operator
    SFColorRGBA& operator()(const X3DField& f) {
        return *this = unwrap(f);
    }

	/**
	 * Full constructor.
	 * 
	 * @param r red value
	 * @param g green value
	 * @param b blue value
	 * @param a alpha value
	 */
	SFColorRGBA(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

	/**
	 * Partial constructor.
	 * 
	 * Initializes alpha to default opaque (1.0).
	 * 
	 * @param r red value
	 * @param g green value
	 * @param b blue value
	 */
	SFColorRGBA(float r, float g, float b) : r(r), g(g), b(b), a(1) {}

	/**
	 * Array accessor (mutable version).
	 * 
	 * Returns a pointer into the packed RGBA values. This pointer
	 * is mutable, so you can write new values int othe color.
	 * 
	 * @returns mutable pointer to RGBA array
	 */
	float* array() { return &r; }

	/**
	 * Array accessor (const version).
     * 
	 * Returns a pointer into the packed RGBA values. This pointer
	 * is not mutable, so it's safe to use on colors declared const.
	 * 
	 * @returns const pointer to RGBA array
	 */
	const float* array() const { return &r; }

    /**
     * Equality test.
     *
     * @param c color to test
     * @returns whether colors are equal
     */
    bool operator==(const SFColorRGBA& c) const {
        return (r == c.r) && (g == c.g) && (b == c.b) && (a == c.a);
    }

    /**
     * Equality test.
     *
     * @param c color to test
     * @returns whether colors are not equal
     */
    bool operator!=(const SFColorRGBA& c) const {
        return (r != c.r) || (g != c.g) || (b != c.b) || (a != c.a);
    }
    
    /**
     * Generic equality test.
     * 
     * @param f field to test
     * @returns whether field is equal
     */
    bool operator==(const X3DField& f) const { return *this == unwrap(f); }

    /**
     * Generic equality test.
     * 
     * @param f field to test
     * @returns whether field is not equal
     */
    bool operator!=(const X3DField& f) const { return *this != unwrap(f); }

    bool parse(istream& is) {
        float r, g, b, a;
        is >> r >> g >> b >> a;
        if (is.fail())
            return false;
        if (r < 0 || r > 1 ||
            g < 0 || g > 1 ||
            b < 0 || b > 1 ||
            a < 0 || a > 1)
            return false;
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
        return true;
    }

    void print(ostream& os) const {
        os << r << ' ' << g << ' ' << b << ' ' << a;
    }
};

}

#endif // #ifndef _X3D_SFCOLOR_H_
