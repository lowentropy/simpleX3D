AM_CPPFLAGS = $(DEPS_CFLAGS) $(GTEST_CFLAGS) $(GMOCK_CFLAGS)
TESTS = $(check_PROGRAMS)
check_PROGRAMS = run_tests
run_tests_SOURCES = run_tests.cc
run_tests_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/test $(AM_CPPFLAGS)
run_tests_LDADD = $(top_srcdir)/src/libsimpleX3D.la $(GTEST_LIBS) $(GMOCK_LIBS)
include_HEADERS = \
	internal/BrowserTests.h \
	internal/SFImageTests.h \
	internal/TypeTests.h \
    internal/FieldIteratorTests.h \
    internal/RouteTests.h \
    internal/RoutingTests.h \
    internal/XmlLoadTests.h \
    internal/ParseTests.h \
	internal/DynamicFieldTests.h \
	internal/NodeIteratorTests.h \
	internal/CloneTests.h \
	Core/X3DBindableNodeTests.h \
	X3DTests.h \
	data/Parse.xml \
	data/TimeSensor.xml \
	data/Unactivated.xml \
	data/Interpolate.xml
