
AC_INIT([openlyrics], [0.7], [kfprimm@system87.com], [openlyrics],
        [http://github.com/kfprimm/openlyrics])
AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([1.10 -Wall no-define foreign])

PKG_CHECK_MODULES([DEPS], [libxml-2.0])

AC_CONFIG_HEADERS([config.h])
AC_PROG_CC
LT_INIT([disable-static])

AC_SUBST([OPENLYRICS_SO_VERSION], [0:7:0])
AC_SUBST([OPENLYRICS_API_VERSION], [0.7])

AC_CONFIG_FILES([Makefile
                 openlyrics-${OPENLYRICS_API_VERSION}.pc:openlyrics.pc.in])
AC_OUTPUT
