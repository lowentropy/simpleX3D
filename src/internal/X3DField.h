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

#ifndef _X3D_X3DFIELD_H_
#define _X3D_X3DFIELD_H_

#include <string>
using std::string;

namespace X3D {

class X3DField {
public:

	typedef enum {
		SFBOOL,
		SFCOLOR,
		SFCOLORRGBA,
		SFDOUBLE,
		SFFLOAT,
		SFIMAGE,
		SFINT32,
		SFMATRIX3D,
		SFMATRIX3F,
		SFMATRIX4D,
		SFMATRIX4F,
		SFNODE,
		SFROTATION,
		SFSTRING,
		SFTIME,
		SFVEC2D,
		SFVEC2F,
		SFVEC3D,
		SFVEC3F,
		SFVEC4D,
		SFVEC4F,
		MFBOOL,
		MFCOLOR,
		MFCOLORRGBA,
		MFDOUBLE,
		MFFLOAT,
		MFIMAGE,
		MFINT32,
		MFMATRIX3D,
		MFMATRIX3F,
		MFMATRIX4D,
		MFMATRIX4F,
		MFNODE,
		MFROTATION,
		MFSTRING,
		MFTIME,
		MFVEC2D,
		MFVEC2F,
		MFVEC3D,
		MFVEC3F,
		MFVEC4D,
		MFVEC4F
	} Type;

	typedef enum {
		INIT_ONLY,
		INPUT_ONLY,
		OUTPUT_ONLY,
		INPUT_OUTPUT
	} Access;

	virtual Type getType() const = 0;
	virtual string getTypeName() const = 0;
	virtual const X3DField& operator=(const X3DField& f) = 0;
	X3DField() {}

private:
	X3DField(const X3DField& field) {}
};

}

#define X3DFIELD_BODY(NAME,CONST,NATIVE) \
	typedef NATIVE TYPE; \
	NATIVE value; \
	inline NAME() {} \
	inline NAME(const NATIVE& value) : value(value) {} \
	inline X3DField::Type getType() const { return CONST; } \
	inline string getTypeName() const { return #NAME; } \
	inline const NATIVE& operator=(const NATIVE& v) { value = v; return v; } \
	inline const NATIVE& operator()() const { return value; } \
	static inline const NATIVE& unwrap(const X3DField& f) { \
		if (f.getType() != CONST) \
			throw X3DError("base type mismatch"); \
		return (static_cast<const NAME*>(&f))->value; \
	} \
	virtual const NAME& operator=(const NAME& f) { \
		value = f.value; \
		return *this; \
	} \
	virtual const NAME& operator=(const X3DField& f) { \
		value = unwrap(f); \
		return *this; \
	}

#endif // #ifndef _X3D_X3DFIELD_H_
