
AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}


lib_LTLIBRARIES = libopenlyrics-@OPENLYRICS_API_VERSION@.la

libopenlyrics_@OPENLYRICS_API_VERSION@_la_CPPFLAGS = $(DEPS_CFLAGS) -Ilibopenlyrics/include
libopenlyrics_@OPENLYRICS_API_VERSION@_la_LIBADD = $(DEPS_LIBS)

libopenlyrics_@OPENLYRICS_API_VERSION@_la_SOURCES = libopenlyrics/song.c \
                                              		libopenlyrics/parse.c \
                                              		libopenlyrics/util.c

libopenlyrics_@OPENLYRICS_API_VERSION@_la_LDFLAGS = -version-info $(OPENLYRICS_SO_VERSION)

openlyrics_includedir = $(includedir)/openlyrics-$(OPENLYRICS_API_VERSION)
openlyrics_include_HEADERS =	libopenlyrics/include/openlyrics/song.h \
								libopenlyrics/include/openlyrics/parse.h \
								libopenlyrics/include/openlyrics/util.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = openlyrics-$(OPENLYRICS_API_VERSION).pc

dist_noinst_SCRIPTS = autogen.sh
