#!/bin/sh
make distclean
rm -f Makefile.in configure
rm -f src/Makefile.in
rm -rf build-aux autom4te.cache
rm -rf aclocal.m4 config.log config.status libtool
