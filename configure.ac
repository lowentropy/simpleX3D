#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT(simpleX3D, 0.0.1, lowentropy@gmail.com)
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([src/SFImage.cc])

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
AC_CHECK_HEADER(gmock/gmock.h)
AC_CHECK_LIB(gmock, testing::InitGoogleMock)

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_HEADER_STDC
#AC_CHECK_FUNCS([memset memcpy snprintf])

AC_CONFIG_FILES([
	Makefile
    src/Makefile
    test/Makefile
])
AC_OUTPUT
