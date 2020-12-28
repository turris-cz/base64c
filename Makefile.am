ACLOCAL_AMFLAGS = -I .m4

lib_LTLIBRARIES = libbase64c.la

libbase64c_la_SOURCES = base64c.c
libbase64c_la_CFLAGS = -isystem %reldir%
libbase64c_la_LDFLAGS = -version-info 0:1:0

include_HEADERS = base64c.h
pkgconfig_DATA = base64c.pc


linted_files = $(libbase64c_la_SOURCES) $(include_HEADERS)
if ENABLE_LINTERS
include $(srcdir)/lint.am
endif

if ENABLE_TESTS
include $(srcdir)/tests/Makefile.am
endif
