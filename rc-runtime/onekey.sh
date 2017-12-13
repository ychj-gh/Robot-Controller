#!/bin/bash
EXE=rc-runtime.exe
BUILD=./build
NFSDIR=/home/mynfs/rc-runtime/

if [ ! -d "$BUILD" ]; then
	mkdir "$BUILD"
fi

cd $BUILD

cmake ..
make

mv ../$EXE ${NFSDIR}

echo "Rc OneKey: Success !"
