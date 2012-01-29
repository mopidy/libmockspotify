#! /bin/sh

if [ "`uname`" == "Darwin" ]; then
    LIBTOOLIZE=glibtoolize
else
    LIBTOOLIZE=libtoolize
fi

$LIBTOOLIZE && autoreconf --install
