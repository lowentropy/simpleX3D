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

class SFTime : public X3DField {
public:
	typedef double TYPE;
	typedef double CONST_TYPE;
	double value;

	inline X3DField::Type getType() const { return X3DField::SFTIME; }

	inline SFTime() : value(0) {}
	inline SFTime(double x) : value(x) {}
	inline double operator()() { return value; }

	inline static double unwrap(const X3DField& f) {
		if (f.getType() != X3DField::SFTIME)
			throw X3DError("base type mismatch");
		return (static_cast<const SFTime&>(f)).value;
	}

	inline const SFTime& operator=(double x) { value = x; return *this; }
	inline const SFTime& operator=(const SFTime& f) {
		value = f.value;
		return *this;
	}

    inline bool operator==(const SFTime& t) const { return value == t.value; }
    inline bool operator!=(const SFTime& t) const { return value != t.value; }
};

}

#endif // #ifndef _X3D_SFTIME_H_
