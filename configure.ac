AC_PREREQ(2.57)

m4_define([mailtc_package],[mailtc_example_extension])
m4_define([mailtc_version],[1.4.3])

m4_define([glib_required_version],[2.28.0])

AC_INIT([mailtc_package],[mailtc_version])

AC_SUBST(ACLOCAL_AMFLAGS,"-I autotools")

AC_CONFIG_HEADERS([config.h])

GLIB_REQUIRED_VERSION=glib_required_version

AC_SUBST(GLIB_REQUIRED_VERSION)

AM_INIT_AUTOMAKE([dist-bzip2 no-dist-gzip])

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_PROG_CC
AM_PROG_CC_STDC
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_C_CONST
AC_HEADER_STDC
AC_DISABLE_STATIC
LT_INIT
LIBTOOL="$LIBTOOL --silent"
ACLOCAL="$ACLOCAL $ACLOCAL_FLAGS"

PKG_PROG_PKG_CONFIG(0,23)
PKG_CHECK_MODULES(GLIB,glib-2.0 >= $GLIB_REQUIRED_VERSION)

AC_SUBST([GLIB_CFLAGS])
AC_SUBST([GLIB_LIBS])

AC_CONFIG_FILES([
Makefile
])

AC_OUTPUT

AC_MSG_RESULT([
Now type 'make' to build $PACKAGE $VERSION,
and then type 'make install' for installation.
])

