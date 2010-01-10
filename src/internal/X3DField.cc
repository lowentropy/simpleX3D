#include "internal/X3DField.h"
#include "internal/MF.h"

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

typedef X3DField* (*TypeCon)();
std::map<string, TypeCon> X3DField::constructorMap;

#define MAKE_TYPE_CON(NAME) static X3DField* new##NAME() { return new NAME(); }
#define INSERT_TYPE_CON(NAME) constructorMap[#NAME] = new##NAME;

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
MAKE_TYPE_CON(MFBool)
MAKE_TYPE_CON(MFColor)
MAKE_TYPE_CON(MFColorRGBA)
MAKE_TYPE_CON(MFDouble)
MAKE_TYPE_CON(MFFloat)
MAKE_TYPE_CON(MFImage)
MAKE_TYPE_CON(MFInt32)
MAKE_TYPE_CON(MFMatrix3d)
MAKE_TYPE_CON(MFMatrix3f)
MAKE_TYPE_CON(MFMatrix4d)
MAKE_TYPE_CON(MFMatrix4f)
MAKE_TYPE_CON(MFRotation)
MAKE_TYPE_CON(MFString)
MAKE_TYPE_CON(MFTime)
MAKE_TYPE_CON(MFVec2d)
MAKE_TYPE_CON(MFVec2f)
MAKE_TYPE_CON(MFVec3d)
MAKE_TYPE_CON(MFVec3f)
MAKE_TYPE_CON(MFVec4d)
MAKE_TYPE_CON(MFVec4f)

static X3DField* newSFNode() { return new SFNode<Node>(); }
static X3DField* newMFNode() { return new MFNode<Node>(); }

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
    	INSERT_TYPE_CON(MFBool)
    	INSERT_TYPE_CON(MFColor)
    	INSERT_TYPE_CON(MFColorRGBA)
    	INSERT_TYPE_CON(MFDouble)
    	INSERT_TYPE_CON(MFFloat)
    	INSERT_TYPE_CON(MFImage)
    	INSERT_TYPE_CON(MFInt32)
    	INSERT_TYPE_CON(MFMatrix3d)
    	INSERT_TYPE_CON(MFMatrix3f)
    	INSERT_TYPE_CON(MFMatrix4d)
    	INSERT_TYPE_CON(MFMatrix4f)
    	INSERT_TYPE_CON(MFNode)
    	INSERT_TYPE_CON(MFRotation)
    	INSERT_TYPE_CON(MFString)
    	INSERT_TYPE_CON(MFTime)
    	INSERT_TYPE_CON(MFVec2d)
    	INSERT_TYPE_CON(MFVec2f)
    	INSERT_TYPE_CON(MFVec3d)
    	INSERT_TYPE_CON(MFVec3f)
    	INSERT_TYPE_CON(MFVec4d)
    	INSERT_TYPE_CON(MFVec4f)
    }
    if (!constructorMap.count(typeName))
        throw X3DError(string("invalid field type: ") + typeName);
    return constructorMap[typeName]();
}

std::ostream& operator<<(std::ostream& os, const X3DField& f) {
    f.print(os);
    return os;
}

}
