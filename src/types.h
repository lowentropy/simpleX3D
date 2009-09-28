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

/** 
 * \file types.h
 * 
 * Describes abstract field types as defined in
 * ISO-IEC-19775-1.2 Part 5: Field type reference.
 * 
 * \see http://www.web3d.org/x3d/specifications/ISO-IEC-19775-1.2-X3D-AbstractSpecification/index.html
 */

#ifndef _X3D_TYPES_H_
#define _X3D_TYPES_H_

#include "config.h"
#include "macros.h"
#include "pointer.h"
#include "errors.h"
#include "Fields/SFVec.h"
#include "Fields/SFMatrix.h"
#include "Fields/SFColor.h"
#include "Fields/SFImage.h"
#include "Fields/SFRotation.h"

#include <string>
#include <vector>

namespace X3D {

typedef bool SFBool; ///< boolean type
typedef double SFDouble; ///< double-precision float
typedef float SFFloat; ///< single-precision float
typedef int32_t SFInt32; ///< 32-bit signed integer
typedef SFMatrix3<SFFloat> SFMatrix3f; ///< 3x3 matrix of SFFloat
typedef SFMatrix3<SFDouble> SFMatrix3d; ///< 3x3 matrix of SFDouble
typedef SFMatrix4<SFFloat> SFMatrix4f; ///< 4x4 matrix of SFFloat
typedef SFMatrix4<SFDouble> SFMatrix4d; ///< 4x4 matrix of SFDouble
typedef std::string SFString; ///< UTF-8 string
typedef double SFTime; ///< seconds since midnight of Jan 1, 1970
typedef SFVec2<SFFloat> SFVec2f; ///< 2-dimensional vector of SFFloat
typedef SFVec2<SFDouble> SFVec2d; ///< 2-dimensional vector of SFDouble
typedef SFVec3<SFFloat> SFVec3f; ///< 3-dimensional vector of SFFloat
typedef SFVec3<SFDouble> SFVec3d; ///< 3-dimensional vector of SFDouble
typedef SFVec4<SFFloat> SFVec4f; ///< 4-dimensional vector of SFFloat
typedef SFVec4<SFDouble> SFVec4d; ///< 4-dimensional vector of SFDouble

typedef std::vector<SFBool> MFBool; ///< list of SFBool values
typedef std::vector<SFColor> MFColor; ///< list of SFColor values
typedef std::vector<SFColorRGBA> MFColorRGBA; ///< list of SFColorRGBA values
typedef std::vector<SFDouble> MFDouble; ///< list of SFDouble values
typedef std::vector<SFFloat> MFFloat; ///< list of SFFloat values
typedef std::vector<SFImage> MFImage; ///< list of SFImage values
typedef std::vector<SFInt32> MFInt32; ///< list of SFInt32 values
typedef std::vector<SFMatrix3f> MFMatrix3f; ///< list of SFMatrix3f values
typedef std::vector<SFMatrix3d> MFMatrix3d; ///< list of SFMatrix3d values
typedef std::vector<SFMatrix4f> MFMatrix4f; ///< list of SFMatrix4f values
typedef std::vector<SFMatrix4d> MFMatrix4d; ///< list of SFMatrix4d values
typedef std::vector<SFRotation> MFRotation; ///< list of SFRotation values
typedef std::vector<SFString> MFString; ///< list of SFString values
typedef std::vector<SFTime> MFTime; ///< list of SFTime values
typedef std::vector<SFVec2f> MFVec2f; ///< list of SFVec2f values
typedef std::vector<SFVec2d> MFVec2d; ///< list of SFVec2d values
typedef std::vector<SFVec3f> MFVec3f; ///< list of SFVec3f values
typedef std::vector<SFVec3d> MFVec3d; ///< list of SFVec3d values
typedef std::vector<SFVec4f> MFVec4f; ///< list of SFVec4f values
typedef std::vector<SFVec4d> MFVec4d; ///< list of SFVec4d values

}

#include "fields.h"
#include "Core/X3DNode.h"

namespace X3D {

	typedef Core::X3DNode* SFNode; ///< pointer to an X3DNode
	typedef std::vector<SFNode>* MFNode; ///< list of SFNode values

	typedef enum {
		SFBoolType,
		SFDoubleType,
		SFFloatType,
		SFInt32Type,
		SFMatrix3fType,
		SFMatrix3dType,
		SFMatrix4fType,
		SFMatrix4dType,
		SFStringType,
		SFTimeType,
		SFVec2fType,
		SFVec2dType,
		SFVec3fType,
		SFVec3dType,
		SFVec4fType,
		SFVec4dType,
		SFNodeType,
		MFBoolType,
		MFDoubleType,
		MFFloatType,
		MFInt32Type,
		MFMatrix3fType,
		MFMatrix3dType,
		MFMatrix4fType,
		MFMatrix4dType,
		MFStringType,
		MFTimeType,
		MFVec2fType,
		MFVec2dType,
		MFVec3fType,
		MFVec3dType,
		MFVec4fType,
		MFVec4dType,
		MFNodeType
	} FieldType;
}

#endif // #ifndef _X3D_TYPES_H_
