
export BITS=64

export BUILD_TYPE=$1
if [ "$BUILD_TYPE" == "" ]; then
  export BUILD_TYPE=release
fi

export MSVS_EXT=msvs2015-$BITS
export BLD_EXT=qt56
export QTDIR=C:/Qt/Qt5.6.1/5.6/msvc2015_64
export COINDIR=C:/Coin/4.0.0a

# Set up the build environment.
# The next few lines will move the cygwin compile tools to end of path so MSVS tools are found first.
unset CC
unset CXXmake
[ -n "${TMP}" ] || export TMP=/tmp
export PATH=`echo $PATH|sed 's,\(/usr/local/bin:/usr/bin\):\(.*\),\2:\1,'`
export COINDIR=`cygpath "$COINDIR"`
export QTDIR=`cygpath "$QTDIR"`

export CPPFLAGS="-I$QTDIR/include/QtCore -I$QTDIR/include/QtWidgets -I$QTDIR/include/QtOpenGL -I$QTDIR/include/QtGui"

export QTR_BLD_DIR=/cygdrive/c/src/quarter/build/$BUILD_TYPE
mkdir $QTR_BLD_DIR
cd $QTR_BLD_DIR

if [ "$BUILD_TYPE" == "release" ]; then
echo "this is a release build!"
export CONFIG_QTLIBS="-lQt5Core -lQt5Widgets -lQt5OpenGL -lQt5Gui -lQt5Xml -lqtmain -lgdi32"
export COIN_USE_LIBS="-lcoin4 -lopengl32"
/cygdrive/c/src/quarter/configure --disable-pkgconfig --with-qt=$QTDIR --prefix=$COINDIR --with-coin=$COINDIR --with-msvcrt=md --disable-debug
fi

if [ "$BUILD_TYPE" == "debug" ]; then
echo "this is a debug build!"
export CONFIG_QTLIBS="-lQt5Cored -lQt5Widgetsd -lQt5OpenGLd -lQt5Guid -lQt5Xmld -lqtmain -lgdi32"
/cygdrive/c/src/quarter/configure --disable-pkgconfig --with-qt=$QTDIR --prefix=$COINDIR --with-coin=$COINDIR --program-suffix=d --with-suffix=d --with-msvcrt=mtd
fi

cd $BUILD_TYPE

echo "next step is to run make -- do not use -j option"
