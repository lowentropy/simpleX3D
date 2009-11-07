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
	typedef float CONST_TYPE;

    /// native stored value
	float value;

    /// @returns SFFLOAT
	inline X3DField::Type getType() const { return X3DField::SFFLOAT; }

    /// Empty constructor.
	inline SFFloat() : value(0) {}

    /// Initializing constructor.
	inline SFFloat(float x) : value(x) {}

    /// @returns native value
	inline float operator()() { return value; }

    /// Unwrap generic SFFloat value
	inline static float unwrap(const X3DField& f) {
		if (f.getType() != SFFLOAT)
			throw X3DError("base type mismatch");
		return (static_cast<const SFFloat&>(f)).value;
	}

    /// Low-level assignment operator
	inline const SFFloat& operator=(float x) { value = x; return *this; }

    /// High-level assignment operator
	inline const SFFloat& operator=(const SFFloat& f) {
		value = f.value;
		return *this;
	}

    /// Generic comparison operator (equal)
    inline bool operator==(const X3DField& f) const { return value == unwrap(f); }

    /// Generic comparison operator (not equal)
    inline bool operator!=(const X3DField& f) const { return value != unwrap(f); }

    /// Native comparison operator (equal)
    inline bool operator==(const SFFloat& b) const { return value == b.value; }

    /// Native comparison operator (not equal)
    inline bool operator!=(const SFFloat& b) const { return value != b.value; }
};

}

#endif // #ifndef _X3D_SFFLOAT_H_
