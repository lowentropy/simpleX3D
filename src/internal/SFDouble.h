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

#ifndef _X3D_SFDOUBLE_H_
#define _X3D_SFDOUBLE_H_

#include "internal/X3DField.h"

namespace X3D {

/**
 * Generic double-precision float container.
 */
class SFDouble : public X3DField {
public:
	typedef double TYPE;
	typedef double CONST_TYPE;

    /// native stored value
	double value;

    /// @returns SFDOUBLE
	INLINE X3DField::Type getType() const { return X3DField::SFDOUBLE; }

    /// Empty constructor.
	INLINE SFDouble() : value(0) {}

    /// Initializing constructor.
	INLINE SFDouble(double x) : value(x) {}

    /// @returns native value
	INLINE double operator()() { return value; }

    /// Unwrap generic SFDouble value
	INLINE static double unwrap(const X3DField& f) {
		if (f.getType() != SFDOUBLE)
			throw X3DError(
                string("base type mismatch; expected SFDouble") +
                ", but was " + f.getTypeName());
		return (static_cast<const SFDouble&>(f)).value;
	}

    /// Low-level assignment operator
	INLINE const SFDouble& operator=(double x) { value = x; return *this; }

    /// High-level assignment operator
	INLINE const SFDouble& operator=(const SFDouble& f) {
		value = f.value;
		return *this;
	}

    /// Generic comparison operator (equal)
    INLINE bool operator==(const X3DField& f) const { return value == unwrap(f); }

    /// Generic comparison operator (not equal)
    INLINE bool operator!=(const X3DField& f) const { return value != unwrap(f); }

    /// Native comparison operator (equal)
    INLINE bool operator==(const SFDouble& b) const { return value == b.value; }

    /// Native comparison operator (not equal)
    INLINE bool operator!=(const SFDouble& b) const { return value != b.value; }

    bool parse(istream& is) {
        double d;
        is >> d;
        if (is.fail())
            return false;
        value = d;
        return true;
    }

    void print(ostream& os) const {
        os << value;
    }
};

}

#endif // #ifndef _X3D_SFDOUBLE_H_
