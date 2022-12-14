#!/bin/bash
ARGS="$1"
ROOTDIR="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
BUILDDIR=$ROOTDIR/build/
mkdir -p $BUILDDIR
cd $BUILDDIR

cmake -DCMAKE_BUILD_TYPE=release $ROOTDIR

test "$ARGS" = "install" && {
    make install
    exit 0
}


make

cd "$ROOTDIR"
cp "$BUILDDIR/compile_commands.json" .

echo Finished creation of: kekcat
