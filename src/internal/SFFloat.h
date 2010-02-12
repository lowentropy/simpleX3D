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

#ifndef _X3D_SFFLOAT_H_
#define _X3D_SFFLOAT_H_

#include "internal/X3DField.h"

namespace X3D {

/**
 * Generic single-precision float container.
 */
class SFFloat : public X3DField {
public:
	typedef float TYPE;
	typedef float REF_TYPE;
	typedef float CONST_TYPE;

    /// native stored value
	float value;

    /// @returns SFFLOAT
	INLINE X3DField::Type getType() const { return X3DField::SFFLOAT; }

    /// Empty constructor.
	INLINE SFFloat() : value(0) {}

    /// Initializing constructor.
	INLINE SFFloat(float x) : value(x) {}

    /// @returns native value
	INLINE float operator()() const { return value; }

    /// Unwrap generic SFFloat value
	INLINE static float unwrap(const X3DField& f) {
		if (f.getType() != SFFLOAT)
			throw X3DError(
                string("base type mismatch; expected SFFloat") +
                ", but was " + f.getTypeName());
		return (static_cast<const SFFloat&>(f)).value;
	}

    /// Low-level assignment operator
	INLINE SFFloat& operator=(float x) { value = x; return *this; }

    /// High-level assignment operator
	INLINE SFFloat& operator=(const SFFloat& f) {
		value = f.value;
		return *this;
	}

    /// High-level generic assignment operator
    SFFloat& operator()(const X3DField& f) {
        return *this = unwrap(f);
    }

    /// Generic comparison operator (equal)
    INLINE bool operator==(const X3DField& f) const { return value == unwrap(f); }

    /// Generic comparison operator (not equal)
    INLINE bool operator!=(const X3DField& f) const { return value != unwrap(f); }

    /// Native comparison operator (equal)
    INLINE bool operator==(const SFFloat& b) const { return value == b.value; }

    /// Native comparison operator (not equal)
    INLINE bool operator!=(const SFFloat& b) const { return value != b.value; }

    /// Imprecise generic comparison
    INLINE bool equals(const X3DField& f) const { return equals(unwrap(f)); }

    /// Imprecise comparison
    INLINE bool equals(const SFFloat& f) const {
        return X3DField::float_close(value, f.value);
    }

    bool parse(istream& is) {
        float f;
        is >> f;
        if (is.fail())
            return false;
        value = f;
        return true;
    }

    void print(ostream& os) const {
        os << value;
    }
};

}

#endif // #ifndef _X3D_SFFLOAT_H_
