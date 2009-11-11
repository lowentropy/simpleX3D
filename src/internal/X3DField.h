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

#include "internal/config.h"
#include "internal/errors.h"
#include <string>
using std::string;

namespace X3D {

/**
 * This is the base class for all simple data types within X3D. Although the
 * only explicit abstract method is getType() (which returns an enumeration value
 * identifying the X3D type), all X3DField implementations also obey a contract
 * which includes the static unwrap() method, generic comparison operators == and
 * !=, and the native-value access operator().
 */
class X3DField {
public:

    /// enumeration identifying x3d type
	typedef enum {
		SFBOOL = 0,
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

    /// string representation of x3d type names
    static const string typeNames[];

    /// convert enumeration to string for type names
    static const string& getTypeName(Type type);

    /// get string representation of this value's type
    const string& getTypeName();

    /// Empty constructor.
	X3DField() {}

    /// Empty virtual destructor.
    virtual ~X3DField() {}

    /**
     * Abstract method to identify the X3D type of this value.
     * This method is used to safely unwrap generic field values,
     * which allows simpleX3D to operate at runtime with great
     * flexibility.
     * 
     * @returns X3D type of field-value
     */
	virtual Type getType() const = 0;

private:

    /// Disallow copy constructor.
	X3DField(const X3DField& field) {}
};

}

#endif // #ifndef _X3D_X3DFIELD_H_
