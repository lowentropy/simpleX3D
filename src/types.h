#ifndef _X3D_TYPES_H_
#define _X3D_TYPES_H_

#include "errors.h"
#include "SFVec.h"
#include "SFMatrix.h"
#include "SFColor.h"
#include "SFImage.h"
#include "SFNode.h"
#include "SFRotation.h"

#include <string>
#include <vector>

typedef bool SFBool;
typedef double SFDouble;
typedef float SFFloat;
typedef int32_t SFInt32;
typedef SFMatrix3<SFFloat> SFMatrix3f;
typedef SFMatrix3<SFDouble> SFMatrix3d;
typedef SFMatrix4<SFFloat> SFMatrix4f;
typedef SFMatrix4<SFDouble> SFMatrix4d;
typedef std::string SFString;
typedef double SFTime;
typedef SFVec2<SFFloat> SFVec2f;
typedef SFVec2<SFDouble> SFVec2d;
typedef SFVec3<SFFloat> SFVec3f;
typedef SFVec3<SFDouble> SFVec3d;
typedef SFVec4<SFFloat> SFVec4f;
typedef SFVec4<SFDouble> SFVec4d;

typedef std::vector<SFBool> MFBool;
typedef std::vector<SFColor> MFColor;
typedef std::vector<SFColorRGBA> MFColorRGBA;
typedef std::vector<SFDouble> MFDouble;
typedef std::vector<SFFloat> MFFloat;
typedef std::vector<SFImage> MFImage;
typedef std::vector<SFInt32> MFInt32;
typedef std::vector<SFMatrix3f> MFMatrix3f;
typedef std::vector<SFMatrix3d> MFMatrix3d;
typedef std::vector<SFMatrix4f> MFMatrix4f;
typedef std::vector<SFMatrix4d> MFMatrix4d;
typedef std::vector<SFNode> MFNode;
typedef std::vector<SFRotation> MFRotation;
typedef std::vector<SFString> MFString;
typedef std::vector<SFTime> MFTime;
typedef std::vector<SFVec2f> MFVec2f;
typedef std::vector<SFVec2d> MFVec2d;
typedef std::vector<SFVec3f> MFVec3f;
typedef std::vector<SFVec3d> MFVec3d;
typedef std::vector<SFVec4f> MFVec4f;
typedef std::vector<SFVec4d> MFVec4d;

#endif // #ifndef _X3D_TYPES_H_
