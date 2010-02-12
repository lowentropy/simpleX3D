#include "internal/MF.h"
#include <cmath>

namespace X3D {

const string X3DField::typeNames[] = {
    "SFBool",
    "SFColor",
    "SFColorRGBA",
    "SFDouble",
    "SFFloat",
    "SFImage",
    "SFInt32",
    "SFMatrix3d",
    "SFMatrix3f",
    "SFMatrix4d",
    "SFMatrix4f",
    "SFNode",
    "SFRotation",
    "SFString",
    "SFTime",
    "SFVec2d",
    "SFVec2f",
    "SFVec3d",
    "SFVec3f",
    "SFVec4d",
    "SFVec4f",
    "MFBool",
    "MFColor",
    "MFColorRGBA",
    "MFDouble",
    "MFFloat",
    "MFImage",
    "MFInt32",
    "MFMatrix3d",
    "MFMatrix3f",
    "MFMatrix4d",
    "MFMatrix4f",
    "MFNode",
    "MFRotation",
    "MFString",
    "MFTime",
    "MFVec2d",
    "MFVec2f",
    "MFVec3d",
    "MFVec3f",
    "MFVec4d",
    "MFVec4f"
};

const string& X3DField::getTypeName(X3DField::Type type) {
    return X3DField::typeNames[type];
}

const string& X3DField::getTypeName() const {
    return getTypeName(getType());
}

X3DField::Type X3DField::getMFType() const {
    int sf = (int) getType();
    if (sf < 21)
        sf = 21;
    return (X3DField::Type) sf;
}

const string& X3DField::getMFTypeName() const {
    return getTypeName(getMFType());
}

typedef X3DField* (*TypeCon)();
std::map<string, TypeCon> X3DField::constructorMap;
std::map<string, X3DField::Type> X3DField::typeMap;

#define MAKE_TYPE_CON(NAME) static X3DField* new##NAME() { return new NAME(); }
#define INSERT_TYPE_CON(NAME) constructorMap[#NAME] = new##NAME;
#define INSERT_TYPE_MAP(NAME,CONST) typeMap[#NAME] = CONST;

MAKE_TYPE_CON(SFBool)
MAKE_TYPE_CON(SFColor)
MAKE_TYPE_CON(SFColorRGBA)
MAKE_TYPE_CON(SFDouble)
MAKE_TYPE_CON(SFFloat)
MAKE_TYPE_CON(SFImage)
MAKE_TYPE_CON(SFInt32)
MAKE_TYPE_CON(SFMatrix3d)
MAKE_TYPE_CON(SFMatrix3f)
MAKE_TYPE_CON(SFMatrix4d)
MAKE_TYPE_CON(SFMatrix4f)
MAKE_TYPE_CON(SFRotation)
MAKE_TYPE_CON(SFString)
MAKE_TYPE_CON(SFTime)
MAKE_TYPE_CON(SFVec2d)
MAKE_TYPE_CON(SFVec2f)
MAKE_TYPE_CON(SFVec3d)
MAKE_TYPE_CON(SFVec3f)
MAKE_TYPE_CON(SFVec4d)
MAKE_TYPE_CON(SFVec4f)
MAKE_TYPE_CON(MFBoolList) /*MAKE_TYPE_CON(MFBoolSet)*/ MAKE_TYPE_CON(MFBoolArray)
MAKE_TYPE_CON(MFColorList) /*MAKE_TYPE_CON(MFColorSet)*/ MAKE_TYPE_CON(MFColorArray)
MAKE_TYPE_CON(MFColorRGBAList) /*MAKE_TYPE_CON(MFColorRGBASet)*/ MAKE_TYPE_CON(MFColorRGBAArray)
MAKE_TYPE_CON(MFDoubleList) /*MAKE_TYPE_CON(MFDoubleSet)*/ MAKE_TYPE_CON(MFDoubleArray)
MAKE_TYPE_CON(MFFloatList) /*MAKE_TYPE_CON(MFFloatSet)*/ MAKE_TYPE_CON(MFFloatArray)
MAKE_TYPE_CON(MFImageList) /*MAKE_TYPE_CON(MFImageSet)*/ MAKE_TYPE_CON(MFImageArray)
MAKE_TYPE_CON(MFInt32List) /*MAKE_TYPE_CON(MFInt32Set)*/ MAKE_TYPE_CON(MFInt32Array)
MAKE_TYPE_CON(MFMatrix3dList) /*MAKE_TYPE_CON(MFMatrix3dSet)*/ MAKE_TYPE_CON(MFMatrix3dArray)
MAKE_TYPE_CON(MFMatrix3fList) /*MAKE_TYPE_CON(MFMatrix3fSet)*/ MAKE_TYPE_CON(MFMatrix3fArray)
MAKE_TYPE_CON(MFMatrix4dList) /*MAKE_TYPE_CON(MFMatrix4dSet)*/ MAKE_TYPE_CON(MFMatrix4dArray)
MAKE_TYPE_CON(MFMatrix4fList) /*MAKE_TYPE_CON(MFMatrix4fSet)*/ MAKE_TYPE_CON(MFMatrix4fArray)
MAKE_TYPE_CON(MFRotationList) /*MAKE_TYPE_CON(MFRotationSet)*/ MAKE_TYPE_CON(MFRotationArray)
MAKE_TYPE_CON(MFStringList) /*MAKE_TYPE_CON(MFStringSet)*/ MAKE_TYPE_CON(MFStringArray)
MAKE_TYPE_CON(MFTimeList) /*MAKE_TYPE_CON(MFTimeSet)*/ MAKE_TYPE_CON(MFTimeArray)
MAKE_TYPE_CON(MFVec2dList) /*MAKE_TYPE_CON(MFVec2dSet)*/ MAKE_TYPE_CON(MFVec2dArray)
MAKE_TYPE_CON(MFVec2fList) /*MAKE_TYPE_CON(MFVec2fSet)*/ MAKE_TYPE_CON(MFVec2fArray)
MAKE_TYPE_CON(MFVec3dList) /*MAKE_TYPE_CON(MFVec3dSet)*/ MAKE_TYPE_CON(MFVec3dArray)
MAKE_TYPE_CON(MFVec3fList) /*MAKE_TYPE_CON(MFVec3fSet)*/ MAKE_TYPE_CON(MFVec3fArray)
MAKE_TYPE_CON(MFVec4dList) /*MAKE_TYPE_CON(MFVec4dSet)*/ MAKE_TYPE_CON(MFVec4dArray)
MAKE_TYPE_CON(MFVec4fList) /*MAKE_TYPE_CON(MFVec4fSet)*/ MAKE_TYPE_CON(MFVec4fArray)

static X3DField* newSFNode() { return new SFNode<Node>(); }
static X3DField* newMFNodeList() { return new MFNodeList<Node>(); }
static X3DField* newMFNodeSet() { return new MFNodeSet<Node>(); }
static X3DField* newMFNodeArray() { return new MFNodeArray<Node>(); }

bool X3DField::equals(const X3DField& field) const {
    return *this == field;
}

X3DField::Type X3DField::getType(const string& typeName) {
    if (typeMap.empty()) {
    	INSERT_TYPE_MAP(SFBool,SFBOOL)
    	INSERT_TYPE_MAP(SFColor,SFCOLOR)
    	INSERT_TYPE_MAP(SFColorRGBA,SFCOLORRGBA)
    	INSERT_TYPE_MAP(SFDouble,SFDOUBLE)
    	INSERT_TYPE_MAP(SFFloat,SFFLOAT)
    	INSERT_TYPE_MAP(SFImage,SFIMAGE)
    	INSERT_TYPE_MAP(SFInt32,SFINT32)
    	INSERT_TYPE_MAP(SFMatrix3d,SFMATRIX3D)
    	INSERT_TYPE_MAP(SFMatrix3f,SFMATRIX3F)
    	INSERT_TYPE_MAP(SFMatrix4d,SFMATRIX4D)
    	INSERT_TYPE_MAP(SFMatrix4f,SFMATRIX4F)
    	INSERT_TYPE_MAP(SFNode,SFNODE)
    	INSERT_TYPE_MAP(SFRotation,SFROTATION)
    	INSERT_TYPE_MAP(SFString,SFSTRING)
    	INSERT_TYPE_MAP(SFTime,SFTIME)
    	INSERT_TYPE_MAP(SFVec2d,SFVEC2D)
    	INSERT_TYPE_MAP(SFVec2f,SFVEC2F)
    	INSERT_TYPE_MAP(SFVec3d,SFVEC3D)
    	INSERT_TYPE_MAP(SFVec3f,SFVEC3F)
    	INSERT_TYPE_MAP(SFVec4d,SFVEC4D)
    	INSERT_TYPE_MAP(SFVec4f,SFVEC4F)
    	INSERT_TYPE_MAP(MFBool,MFBOOL)
    	INSERT_TYPE_MAP(MFColor,MFCOLOR)
    	INSERT_TYPE_MAP(MFColorRGBA,MFCOLORRGBA)
    	INSERT_TYPE_MAP(MFDouble,MFDOUBLE)
    	INSERT_TYPE_MAP(MFFloat,MFFLOAT)
    	INSERT_TYPE_MAP(MFImage,MFIMAGE)
    	INSERT_TYPE_MAP(MFInt32,MFINT32)
    	INSERT_TYPE_MAP(MFMatrix3d,MFMATRIX3D)
    	INSERT_TYPE_MAP(MFMatrix3f,MFMATRIX3F)
    	INSERT_TYPE_MAP(MFMatrix4d,MFMATRIX4D)
    	INSERT_TYPE_MAP(MFMatrix4f,MFMATRIX4F)
    	INSERT_TYPE_MAP(MFNode,MFNODE)
    	INSERT_TYPE_MAP(MFRotation,MFROTATION)
    	INSERT_TYPE_MAP(MFString,MFSTRING)
    	INSERT_TYPE_MAP(MFTime,MFTIME)
    	INSERT_TYPE_MAP(MFVec2d,MFVEC2D)
    	INSERT_TYPE_MAP(MFVec2f,MFVEC2F)
    	INSERT_TYPE_MAP(MFVec3d,MFVEC3D)
    	INSERT_TYPE_MAP(MFVec3f,MFVEC3F)
    	INSERT_TYPE_MAP(MFVec4d,MFVEC4D)
    	INSERT_TYPE_MAP(MFVec4f,MFVEC4F)
    }
    if (!typeMap.count(typeName))
        throw X3DError(string("invalid field type: ") + typeName);
    return typeMap[typeName];
}

// XXX this is duuuuuuumb
X3DField* X3DField::create(Type type) {
    return create(getTypeName(type));
}

X3DField* X3DField::create(const string& typeName) {
    if (constructorMap.empty()) {
    	INSERT_TYPE_CON(SFBool)
    	INSERT_TYPE_CON(SFColor)
    	INSERT_TYPE_CON(SFColorRGBA)
    	INSERT_TYPE_CON(SFDouble)
    	INSERT_TYPE_CON(SFFloat)
    	INSERT_TYPE_CON(SFImage)
    	INSERT_TYPE_CON(SFInt32)
    	INSERT_TYPE_CON(SFMatrix3d)
    	INSERT_TYPE_CON(SFMatrix3f)
    	INSERT_TYPE_CON(SFMatrix4d)
    	INSERT_TYPE_CON(SFMatrix4f)
    	INSERT_TYPE_CON(SFNode)
    	INSERT_TYPE_CON(SFRotation)
    	INSERT_TYPE_CON(SFString)
    	INSERT_TYPE_CON(SFTime)
    	INSERT_TYPE_CON(SFVec2d)
    	INSERT_TYPE_CON(SFVec2f)
    	INSERT_TYPE_CON(SFVec3d)
    	INSERT_TYPE_CON(SFVec3f)
    	INSERT_TYPE_CON(SFVec4d)
    	INSERT_TYPE_CON(SFVec4f)
    	INSERT_TYPE_CON(MFBoolList) /*INSERT_TYPE_CON(MFBoolSet)*/ INSERT_TYPE_CON(MFBoolArray)
    	INSERT_TYPE_CON(MFColorList) /*INSERT_TYPE_CON(MFColorSet)*/ INSERT_TYPE_CON(MFColorArray)
    	INSERT_TYPE_CON(MFColorRGBAList) /*INSERT_TYPE_CON(MFColorRGBASet)*/ INSERT_TYPE_CON(MFColorRGBAArray)
    	INSERT_TYPE_CON(MFDoubleList) /*INSERT_TYPE_CON(MFDoubleSet)*/ INSERT_TYPE_CON(MFDoubleArray)
    	INSERT_TYPE_CON(MFFloatList) /*INSERT_TYPE_CON(MFFloatSet)*/ INSERT_TYPE_CON(MFFloatArray)
    	INSERT_TYPE_CON(MFImageList) /*INSERT_TYPE_CON(MFImageSet)*/ INSERT_TYPE_CON(MFImageArray)
    	INSERT_TYPE_CON(MFInt32List) /*INSERT_TYPE_CON(MFInt32Set)*/ INSERT_TYPE_CON(MFInt32Array)
    	INSERT_TYPE_CON(MFMatrix3dList) /*INSERT_TYPE_CON(MFMatrix3dSet)*/ INSERT_TYPE_CON(MFMatrix3dArray)
    	INSERT_TYPE_CON(MFMatrix3fList) /*INSERT_TYPE_CON(MFMatrix3fSet)*/ INSERT_TYPE_CON(MFMatrix3fArray)
    	INSERT_TYPE_CON(MFMatrix4dList) /*INSERT_TYPE_CON(MFMatrix4dSet)*/ INSERT_TYPE_CON(MFMatrix4dArray)
    	INSERT_TYPE_CON(MFMatrix4fList) /*INSERT_TYPE_CON(MFMatrix4fSet)*/ INSERT_TYPE_CON(MFMatrix4fArray)
    	INSERT_TYPE_CON(MFNodeList) /*INSERT_TYPE_CON(MFNodeSet)*/ INSERT_TYPE_CON(MFNodeArray)
    	INSERT_TYPE_CON(MFRotationList) /*INSERT_TYPE_CON(MFRotationSet)*/ INSERT_TYPE_CON(MFRotationArray)
    	INSERT_TYPE_CON(MFStringList) /*INSERT_TYPE_CON(MFStringSet)*/ INSERT_TYPE_CON(MFStringArray)
    	INSERT_TYPE_CON(MFTimeList) /*INSERT_TYPE_CON(MFTimeSet)*/ INSERT_TYPE_CON(MFTimeArray)
    	INSERT_TYPE_CON(MFVec2dList) /*INSERT_TYPE_CON(MFVec2dSet)*/ INSERT_TYPE_CON(MFVec2dArray)
    	INSERT_TYPE_CON(MFVec2fList) /*INSERT_TYPE_CON(MFVec2fSet)*/ INSERT_TYPE_CON(MFVec2fArray)
    	INSERT_TYPE_CON(MFVec3dList) /*INSERT_TYPE_CON(MFVec3dSet)*/ INSERT_TYPE_CON(MFVec3dArray)
    	INSERT_TYPE_CON(MFVec3fList) /*INSERT_TYPE_CON(MFVec3fSet)*/ INSERT_TYPE_CON(MFVec3fArray)
    	INSERT_TYPE_CON(MFVec4dList) /*INSERT_TYPE_CON(MFVec4dSet)*/ INSERT_TYPE_CON(MFVec4dArray)
    	INSERT_TYPE_CON(MFVec4fList) /*INSERT_TYPE_CON(MFVec4fSet)*/ INSERT_TYPE_CON(MFVec4fArray)
    }
    if (!constructorMap.count(typeName))
        throw X3DError(string("invalid field type: ") + typeName);
    return constructorMap[typeName]();
}

std::ostream& operator<<(std::ostream& os, const X3DField& f) {
    f.print(os);
    return os;
}

bool X3DField::float_close(double u, double v) {
    double d = fabs(u - v);
    if (d < 1e-150)
        return true;
    double av = fabs(v);
    double m = fabs(u);
    if (av > m) m = av;
    return (d / m) < 1e-8;
}

}
