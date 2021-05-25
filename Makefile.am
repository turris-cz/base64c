ACLOCAL_AMFLAGS = -I .m4

lib_LTLIBRARIES = libbase64c.la
include_HEADERS = base64c.h
pkgconfig_DATA = base64c.pc
EXTRA_DIST = libbase64c.version

libbase64c_la_SOURCES = \
	%reldir%/base64c.c
libbase64c_la_CFLAGS = \
	-isystem '$(srcdir)' \
	${CODE_COVERAGE_CFLAGS}
libbase64c_la_LIBADD = \
	${CODE_COVERAGE_LIBS}
libbase64c_la_LDFLAGS = \
	-Wl,--version-script='$(srcdir)/libbase64c.version' \
	-version-info 0:1:0


linted_files = $(libbase64c_la_SOURCES) $(include_HEADERS)
if ENABLE_LINTERS
include $(srcdir)/lint.am
endif

if ENABLE_TESTS
DISTCHECK_CONFIGURE_FLAGS = --enable-tests
include $(srcdir)/tests/Makefile.am
endif
