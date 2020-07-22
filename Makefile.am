ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libbase64c.la

libbase64c_la_SOURCES = base64c.c
libbase64c_la_CFLAGS = -isystem %reldir%

include_HEADERS = base64c.h
pkgconfig_DATA = base64c.pc


linted_files = $(libbase64c_la_SOURCES) $(include_HEADERS)
include $(srcdir)/lint.am

include $(srcdir)/tests/Makefile.am
