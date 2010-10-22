
AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

lib_LTLIBRARIES = libopenlyrics-@OPENLYRICS_API_VERSION@.la

libopenlyrics_@OPENLYRICS_API_VERSION@_la_CPPFLAGS = $(DEPS_CFLAGS) -Ilibopenlyrics/include
libopenlyrics_@OPENLYRICS_API_VERSION@_la_LIBADD = $(DEPS_LIBS)

libopenlyrics_@OPENLYRICS_API_VERSION@_la_SOURCES = libopenlyrics/song.c libopenlyrics/parse.c libopenlyrics/util.c \
                                                    libopenlyrics/data.c

libopenlyrics_@OPENLYRICS_API_VERSION@_la_LDFLAGS = -version-info $(OPENLYRICS_SO_VERSION)

OL_INCDIR = libopenlyrics/include/openlyrics
openlyrics_includedir = $(includedir)/openlyrics-$(OPENLYRICS_API_VERSION)/openlyrics
openlyrics_include_HEADERS = $(OL_INCDIR)/song.h $(OL_INCDIR)/parse.h $(OL_INCDIR)/util.h $(OL_INCDIR)/data.h

bin_PROGRAMS = oltool
oltool_SOURCES = tool/oltool.c
oltool_CPPFLAGS = -Ilibopenlyrics/include
oltool_LDADD = ./libopenlyrics-$(OPENLYRICS_API_VERSION).la

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = openlyrics-$(OPENLYRICS_API_VERSION).pc

dist_noinst_SCRIPTS = autogen.sh


