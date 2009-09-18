#!/bin/sh
make distclean
rm -f Makefile.in aclocal.m4 configure
rm -f src/Makefile.in
rm -rf build-aux autom4te.cache m4
