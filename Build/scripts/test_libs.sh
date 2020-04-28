#!/bin/bash
LUA=$1
makelibs()
{
  lib=$1
  if [ ! -e $LIBDIR/$lib ] ; then
    CURDIR=`pwd`
    cd $LIBDIR
    ./make_LIBS.sh $LUA
    cd $CURDIR
  fi
}

makelibs libgd.a 
makelibs libglui.a 
if [ "`uname`" == "Darwin" ]; then
  if [ "$GLUT" == "freeglut" ]; then
    makelibs libglut.a
  fi
else
  makelibs libglut.a 
fi
makelibs libjpeg.a 
makelibs libpng.a 
makelibs libz.a 
if [ "$LUA" == "lua" ];then
makelibs liblua.a
makelibs lpeg.so
fi

