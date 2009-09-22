#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT(simpleX3D, 0.0.1, lowentropy@gmail.com)
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([src/Fields/SFImage.cc])

# Checks for programs.
AC_LANG([C++])
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_LIBTOOL
AC_CHECK_TOOL(AR,ar)
AC_CHECK_TOOL(LD,ld)

AC_SUBST(DEPS_CFLAGS)
AC_SUBST(DEPS_LDFLAGS)

# Check for google mocks
AC_CHECK_PROG(GTEST_CONFIG, gtest-config, "yes")
if test x"$GTEST_CONFIG" = "xyes"; then
  GTEST_CFLAGS=`gtest-config --cppflags --cxxflags`
  GTEST_LIBS=`gtest-config --ldflags --libs`
  AC_DEFINE(HAVE_LIB_GTEST, 1, [define if you have google gtest library])

  # Check if there is Google Mocking library installed.
  AC_CHECK_PROG(GMOCK_CONFIG, gmock-config, "yes")
  if test x"$GMOCK_CONFIG" = "xyes"; then
    GMOCK_CFLAGS=`gmock-config --cppflags --cxxflags`
    GMOCK_LIBS=`gmock-config --ldflags --libs`
    AC_DEFINE(HAVE_LIB_GMOCK, 1, [define if you have google gmock library])
  else
    # We don't run test cases which use Google Mocking framework.
    GMOCK_CFLAGS=
    GMOCK_LIBS=
  fi
else
  # We'll use src/googletest.h for our unittests.
  GTEST_CFLAGS=
  GTEST_LIBS=
fi
AM_CONDITIONAL(HAVE_GMOCK, test x"$GMOCK_CONFIG" = "xyes")


# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_HEADER_STDC
#AC_CHECK_FUNCS([memset memcpy snprintf])

AC_SUBST(GTEST_CFLAGS)
AC_SUBST(GTEST_LIBS)
AC_SUBST(GMOCK_CFLAGS)
AC_SUBST(GMOCK_LIBS)

AC_CONFIG_FILES([
	Makefile
    src/Makefile
    test/Makefile
])
AC_OUTPUT
