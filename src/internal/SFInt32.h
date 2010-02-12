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

#ifndef _X3D_SFINT32_H_
#define _X3D_SFINT32_H_

#include "internal/X3DField.h"

namespace X3D {

/**
 * Generic integer container type.
 */
class SFInt32 : public X3DField {
public:
	typedef int TYPE;
	typedef int REF_TYPE;
	typedef int CONST_TYPE;

    /// native stored value
	int value;

    /// @returns SFINT32
	INLINE X3DField::Type getType() const { return X3DField::SFINT32; }

    /// Empty constructor.
	INLINE SFInt32() : value(0) {}

    /// Initializing constructor.
	INLINE SFInt32(int x) : value(x) {}

    /// @returns native integer value
	INLINE int operator()() const { return value; }

    INLINE int operator++() { return ++value; }

    INLINE int operator--() { return --value; }

    INLINE int operator++(int) { return value++; }

    INLINE int operator--(int) { return value--; }

    /// Unwrap a generic SFInt32 value
	INLINE static int unwrap(const X3DField& f) {
		if (f.getType() != SFINT32)
			throw X3DError(
                string("base type mismatch; expected SFInt32") +
                ", but was " + f.getTypeName());
		return (static_cast<const SFInt32&>(f)).value;
	}

    /// Low-level assignment operator.
	INLINE SFInt32& operator=(int x) { value = x; return *this; }

    /// High-level assignment operator.
	INLINE SFInt32& operator=(const SFInt32& f) {
		value = f.value;
		return *this;
	}

    /// High-level assignment operator
    SFInt32& operator()(const X3DField& f) {
        return *this = unwrap(f);
    }

    /// Generic comparison operator (equal)
    INLINE bool operator==(const X3DField& f) const { return value == unwrap(f); }

    /// Generic comparison operator (not equal)
    INLINE bool operator!=(const X3DField& f) const { return value != unwrap(f); }

    /// Native comparison operator (equal)
    INLINE bool operator==(const SFInt32& x) const { return value == x.value; }

    /// Native comparison operator (not equal)
    INLINE bool operator!=(const SFInt32& x) const { return value != x.value; }

    bool parse(istream& is) {
        int x;
        is >> x;
        if (is.fail())
            return false;
        value = x;
        return true;
    }

    void print(ostream& os) const {
        os << value;
    }
};

}

#endif // #ifndef _X3D_SFINT32_H_
