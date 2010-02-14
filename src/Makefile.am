AM_CPPFLAGS = $(DEPS_CFLAGS) -I$(top_srcdir)/include
lib_LTLIBRARIES = libsimpleX3D.la
libsimpleX3D_la_SOURCES = \
    internal/errors.cc \
    internal/X3DField.cc \
	internal/Node.cc \
	internal/SFImage.cc \
    internal/SFNode.cc \
	internal/Browser.cc \
    internal/Route.cc \
    internal/Profile.cc \
    internal/Component.cc \
    internal/NodeDef.cc \
    internal/FieldDef.cc \
    internal/SAIField.cc \
    internal/FieldIterator.cc \
    internal/World.cc \
    internal/Prototype.cc \
    internal/ProtoInst.cc \
	internal/builtin.cc \
	Core/X3DNode.cc \
	Core/MetadataSet.cc \
	Core/MetadataString.cc \
    Test/TestSuite.cc \
    Test/TestNode.cc \
    Test/Expect.cc \
	Time/TimeSensor.cc \
	Interpolation/X3DInterpolatorNode.cc \
	Interpolation/PositionInterpolator.cc \
	Interpolation/PositionInterpolator2D.cc \
	Interpolation/ScalarInterpolator.cc \
	Interpolation/CoordinateInterpolator.cc \
	Interpolation/CoordinateInterpolator2D.cc \
	Interpolation/EaseInEaseOut.cc \
	Grouping/X3DBoundedObject.cc \
	Grouping/X3DGroupingNode.cc
libsimpleX3D_la_LIBADD = $(DEPS_LIBS)
