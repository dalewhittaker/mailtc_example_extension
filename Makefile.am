plugindir = "$(libdir)/mailtc"

plugin_LTLIBRARIES = example.la

AM_CPPFLAGS = \
		-DG_DISABLE_SINGLE_INCLUDES \
		-DG_DISABLE_DEPRECATED \
		-DLIBDIR=\"$(plugindir)\"

AM_CFLAGS = \
		-Wall \
		-Wextra \
		-ansi \
		-pedantic

INCLUDES = \
		$(GLIB_CFLAGS)

LDADD = \
		$(GLIB_LIBS)

example_la_SOURCES = \
		main.c

example_la_LDFLAGS = \
		-no-undefined \
		-module \
		-avoid-version \
		-rpath $(plugindir)

