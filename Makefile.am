ACLOCAL_AMFLAGS = -I .m4

lib_LTLIBRARIES = libbase64c.la
include_HEADERS = base64c.h
pkgconfig_DATA = base64c.pc

libbase64c_la_SOURCES = \
	%reldir%/base64c.c
libbase64c_la_CFLAGS = \
	-isystem %reldir% \
	${CODE_COVERAGE_CFLAGS}
libbase64c_la_LDFLAGS = -version-info 0:1:0
libbase64c_la_LIDADD = ${CODE_COVERAGE_LIBS}


linted_files = $(libbase64c_la_SOURCES) $(include_HEADERS)
if ENABLE_LINTERS
include $(srcdir)/lint.am
endif

if ENABLE_TESTS
include $(srcdir)/tests/Makefile.am
endif
