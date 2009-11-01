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

#ifndef _X3D_MFFIELDS_H_
#define _X3D_MFFIELDS_H_

#include "internal/X3DField.h"
#include <list>
using std::list;

#define MAKE_MF(CONST,MF,SF,KIND) \
class MF : public KIND<SF> { \
public:\
    typedef MF& TYPE; \
    typedef const MF& CONST_TYPE; \
    MF() : KIND<SF>() {} \
    inline X3DField::Type getType() const { return X3DField::CONST; } \
    static inline const MF& unwrap(const X3DField& f) { \
        if (f.getType() != X3DField::CONST) \
            throw X3DError("base type mismatch"); \
        return static_cast<const MF&>(f); \
    } \
    inline MF& operator()() { \
        return *this; \
    } \
private: \
    MF(const MF& mf) {} \
};

namespace X3D {

template <typename T>
class MFBase : public X3DField {
protected:
    list<T> elements;
public:
    MFBase() : X3DField() {}
    void clear() {
        elements.clear();
    }
    bool operator==(const MFBase<T>& mf) const {
        return elements == mf.elements;
    }
    bool operator!=(const MFBase<T>& mf) const {
        return elements != mf.elements;
    }
};

template <class T>
class MFReference : public MFBase<T> {
public:
    MFReference() : MFBase<T>() {}
	void add(const T& elem) {
        MFBase<T>::elements.push_back(elem);
    }
};

template <typename T>
class MFNative : public MFBase<T> {
public:
    MFNative() : MFBase<T>() {}
	void add(T elem) {
        MFBase<T>::elements.push_back(elem);
    }
};

template <class N>
class MFNode : public MFNative<N*> {
public:
	typedef MFNode<N>& TYPE;
	typedef const MFNode<N>& CONST_TYPE;
    MFNode() : MFNative<N*>() {}
	inline X3DField::Type getType() const { return X3DField::MFNODE; }
	static inline const MFNode<N>& unwrap(const X3DField& f) {
		if (f.getType() != X3DField::MFNODE)
			throw X3DError("base type mismatch");
		return static_cast<const MFNode<N>&>(f);
	}
    inline MFNode<N>& operator()() {
        return *this;
    }
private:
    MFNode(const MFNode<N>& mf) {}
};

MAKE_MF(MFBOOL,		MFBool,		bool,		MFNative)
MAKE_MF(MFCOLOR,	MFColor,	SFColor,	MFReference)
MAKE_MF(MFCOLORRGBA,MFColorRGBA,SFColorRGBA,MFReference)
MAKE_MF(MFDOUBLE,	MFDouble,	double,		MFNative)
MAKE_MF(MFFLOAT,	MFFloat,	float,		MFNative)
MAKE_MF(MFIMAGE,	MFImage,	SFImage,	MFReference)
MAKE_MF(MFINT32,	MFInt32,	int,		MFNative)
MAKE_MF(MFMATRIX3D,	MFMatrix3d,	SFMatrix3d,	MFReference)
MAKE_MF(MFMATRIX3F,	MFMatrix3f,	SFMatrix3f,	MFReference)
MAKE_MF(MFMATRIX4D,	MFMatrix4d,	SFMatrix4d,	MFReference)
MAKE_MF(MFMATRIX4F,	MFMatrix4f,	SFMatrix4f,	MFReference)
MAKE_MF(MFROTATION,	MFRotation,	SFRotation,	MFReference)
MAKE_MF(MFSTRING,	MFString,	std::string,MFReference)
MAKE_MF(MFTIME,		MFTime,		double,		MFNative)
MAKE_MF(MFVEC2D,	MFVec2d,	SFVec2d,	MFReference)
MAKE_MF(MFVEC2F,	MFVec2f,	SFVec2f,	MFReference)
MAKE_MF(MFVEC3D,	MFVec3d,	SFVec3d,	MFReference)
MAKE_MF(MFVEC3F,	MFVec3f,	SFVec3f,	MFReference)
MAKE_MF(MFVEC4D,	MFVec4d,	SFVec4d,	MFReference)
MAKE_MF(MFVEC4F,	MFVec4f,	SFVec4f,	MFReference)

}

#endif // #ifndef _X3D_MFFIELDS_H_
