AM_CPPFLAGS = $(DEPS_CFLAGS) $(GTEST_CFLAGS) $(GMOCK_CFLAGS)
TESTS = $(check_PROGRAMS)
check_PROGRAMS = test_should_create_SFImage
test_should_create_SFImage_SOURCES = test_should_create_SFImage.cc
test_should_create_SFImage_CPPFLAGS = -I$(top_srcdir)/src
test_should_create_SFImage_LDADD = $(top_srcdir)/src/libsimpleX3D.la $(GTEST_LIBS) $(GMOCK_LIBS)
