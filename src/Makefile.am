AM_CPPFLAGS = $(DEPS_CFLAGS)
lib_LTLIBRARIES = libsimpleX3D.la
libsimpleX3D_la_SOURCES = \
    internal/X3DField.cc \
	internal/Node.cc \
	internal/SFImage.cc \
	internal/SFColor.cc \
	internal/Browser.cc \
    internal/Route.cc \
    internal/Profile.cc \
    internal/Component.cc \
    internal/NodeDef.cc \
    internal/FieldDef.cc \
	Core/X3DNode.cc \
	Core/MetadataSet.cc \
	Core/MetadataString.cc
libsimpleX3D_la_LIBADD = $(DEPS_LIBS)
include_HEADERS = \
	internal/X3DField.h \
	internal/errors.h \
	internal/Node.h \
	internal/Browser.h \
	internal/types.h \
	internal/InitField.h \
	internal/InField.h \
	internal/OutField.h \
	internal/InOutField.h \
	internal/profile.h \
	internal/builtin.h \
	internal/SFBool.h \
	internal/SFColor.h \
	internal/SFDouble.h \
	internal/SFFloat.h \
	internal/SFImage.h \
	internal/SFInt32.h \
	internal/SFMatrix.h \
	internal/SFNode.h \
	internal/SFRotation.h \
	internal/SFString.h \
	internal/SFTime.h \
	internal/SFVec.h \
	internal/MF.h \
	Core/X3DNode.h \
	Core/X3DChildNode.h \
    Core/X3DBindableNode.h \
    Core/X3DInfoNode.h \
    Core/X3DMetadataObject.h \
    Core/X3DPrototypeInstance.h \
    Core/X3DSensorNode.h \
    Core/MetadataDouble.h \
    Core/MetadataFloat.h \
    Core/MetadataInteger.h \
    Core/MetadataSet.h \
    Core/MetadataString.h \
    Core/WorldInfo.h \
    Time/X3DTimeDependentNode.h \
    Time/TimeSensor.h \
	internal/SAIField.h

# s/^.*or: \([^:]*\):.*$/    \1 \\/
