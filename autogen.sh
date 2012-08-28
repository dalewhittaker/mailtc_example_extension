#!/bin/sh

LIBTOOLIZE_FLAGS="--force --automake --copy"
AUTOMAKE_FLAGS="--add-missing --copy"
rm -rf ./autom4te.cache
touch NEWS README ChangeLog

aclocal $ACLOCAL_FLAGS || exit $?
libtoolize $LIBTOOLIZE_FLAGS || exit $?
autoheader || exit $?
automake $AUTOMAKE_FLAGS || exit $?
autoconf || exit $?

./configure "$@" || exit $?
