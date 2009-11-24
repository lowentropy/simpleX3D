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

#ifndef _X3D_ANYFIELD_H_
#define _X3D_ANYFIELD_H_

#include "internal/X3DField.h"

namespace X3D {

/**
 * An X3DField that can accept any type, and internally stores them
 * as pointers to whatever it's set to.
 */
class AnyField : public X3DField {
public:
	typedef const X3DField* TYPE;
	typedef const X3DField* CONST_TYPE;

    /// native stored value
	const X3DField* value;

    /// @returns SFINT32
	INLINE X3DField::Type getType() const { return X3DField::ANY; }

    /// Empty constructor.
	INLINE AnyField() : value(NULL) {}

    /// Initializing constructor.
	INLINE AnyField(const X3DField& x) : value(&x) {}

    /// Initializing constructor.
	INLINE AnyField(const X3DField* x) : value(x) {}

    /// @returns native integer value
	INLINE const X3DField* operator()() { return value; }

    /// Unwrap a generic SFInt32 value
	INLINE static const X3DField* unwrap(const X3DField& f) {
        // repeat the internal pointer (no chains!)
		if (f.getType() == ANY)
            return (static_cast<const AnyField&>(f)).value;
        // make a reference to this field... whatever it is
        else
            return &f;
	}

    /// Low-level assignment operator.
	INLINE const AnyField& operator=(const X3DField* x) { value = x; return *this; }

    /// High-level assignment operator.
	INLINE const AnyField& operator=(const AnyField& f) {
		value = f.value;
		return *this;
	}

    /// Generic comparison operator (equal)
    INLINE bool operator==(const X3DField& f) const { return value == unwrap(f); }

    /// Generic comparison operator (not equal)
    INLINE bool operator!=(const X3DField& f) const { return value != unwrap(f); }

    /// Native comparison operator (equal)
    INLINE bool operator==(const AnyField& x) const { return value == x.value; }

    /// Native comparison operator (not equal)
    INLINE bool operator!=(const AnyField& x) const { return value != x.value; }

    bool parse(istream& is) {
        return false;
    }

    // this is just for cheesy grins
    void print(ostream& os) const {
        if (value == NULL)
            os << "NULL";
        else
            value->print(os);
    }
};

}

#endif // #ifndef _X3D_ANYFIELD_H_
