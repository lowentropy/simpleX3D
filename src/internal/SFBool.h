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

#ifndef _X3D_SFBOOL_H_
#define _X3D_SFBOOL_H_

#include "internal/X3DField.h"

namespace X3D {

/**
 * Generic Boolean type container.
 */
class SFBool : public X3DField {
public:
	typedef bool TYPE;
	typedef bool REF_TYPE;
    typedef bool CONST_TYPE;

    /// native stored value
	bool value;

    /// @returns SFBOOL
    INLINE static X3DField::Type getStaticType() { return X3DField::SFBOOL; }

    /// @returns SFBOOL
	INLINE X3DField::Type getType() const { return X3DField::SFBOOL; }

    /// Empty constructor.
	INLINE SFBool() : value(false) {}

    /// Initializing constructor.
	INLINE SFBool(bool x) : value(x) {}

    /// Low-level value access.
	INLINE bool operator()() const { return value; }

    /// Unwraps generic value.
	INLINE static bool unwrap(const X3DField& f) {
		if (f.getType() != SFBOOL)
			throw X3DError(
                string("base type mismatch; expected SFBool") +
                ", but was " + f.getTypeName());
		return (static_cast<const SFBool&>(f)).value;
	}

    /// Low-level assignment operator
	INLINE SFBool& operator=(bool x) { value = x; return *this; }

    /// High-level assignment operator
	INLINE SFBool& operator=(const SFBool& f) {
		value = f.value;
		return *this;
	}

    /// High-level assignment operator
    SFBool& operator()(const X3DField& f) {
        return *this = unwrap(f);
    }

    /// Generic comparison operator (equal)
    INLINE bool operator==(const X3DField& f) const { return value == unwrap(f); }

    /// Generic comparison operator (not equal)
    INLINE bool operator!=(const X3DField& f) const { return value != unwrap(f); }

    /// Native comparison operator (equal)
    INLINE bool operator==(const SFBool& b) const { return value == b.value; }

    /// Native comparison operator (not equal)
    INLINE bool operator!=(const SFBool& b) const { return value != b.value; }

    bool parse(istream& is) {
        bool b;
        is >> std::boolalpha >> b;
        if (is.fail())
            return false;
        value = b;
        return true;
    }

    void print(ostream& os) const {
        os << std::boolalpha << value;
    }
};

}

#endif // #ifndef _X3D_SFBOOL_H_
