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

#ifndef _X3D_SFTIME_H_
#define _X3D_SFTIME_H_

#include "internal/X3DField.h"

namespace X3D {

/**
 * Generic container for a Time value, which is stored as a double-precision
 * float indicating the number of seconds since midnight on Jan 1, 1970.
 */
class SFTime : public X3DField {
public:

	typedef double TYPE;
	typedef double REF_TYPE;
	typedef double CONST_TYPE;

    /// native stored value
	double value;

    /// @returns SFTIME
	INLINE X3DField::Type getType() const { return X3DField::SFTIME; }

    /// Empty constructor.
	INLINE SFTime() : value(0) {}

    /// Initializing constructor.
	INLINE SFTime(double x) : value(x) {}

    /// @returns native time value (as double)
	INLINE double operator()() const { return value; }

    /// Unwrap generic time field (as double)
	INLINE static double unwrap(const X3DField& f) {
		if (f.getType() != X3DField::SFTIME)
			throw X3DError(
                string("base type mismatch; expected SFTime") +
                ", but was " + f.getTypeName());
		return (static_cast<const SFTime&>(f)).value;
	}

    /// Low-level assignment operator.
	INLINE SFTime& operator=(double x) { value = x; return *this; }

    /// High-level assignment operator.
	INLINE SFTime& operator=(const SFTime& f) {
		value = f.value;
		return *this;
	}

    /// High-level assignment operator
    SFTime& operator()(const X3DField& f) {
        return *this = unwrap(f);
    }

    /// Generic comparison operator (equal)
    INLINE bool operator==(const X3DField& f) const { return value == unwrap(f); }

    /// Generic comparison operator (not equal)
    INLINE bool operator!=(const X3DField& f) const { return value != unwrap(f); }

    /// Native comparison operator (equal)
    INLINE bool operator==(const SFTime& t) const { return value == t.value; }

    /// Native comparison operator (not equal)
    INLINE bool operator!=(const SFTime& t) const { return value != t.value; }

    /// Imprecise generic comparison
    INLINE bool equals(const X3DField& f) const { return equals(unwrap(f)); }

    /// Imprecise comparison
    INLINE bool equals(const SFTime& f) const {
        return X3DField::float_close(value, f.value);
    }

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

#endif // #ifndef _X3D_SFTIME_H_
