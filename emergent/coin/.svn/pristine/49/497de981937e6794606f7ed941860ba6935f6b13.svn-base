export BITS=64

if [ "$BUILD_TYPE" == "" ]; then
  export BUILD_TYPE=release
else
  export BUILD_TYPE=$1
fi

export MSVS_EXT=msvs2015-$BITS
export BLD_EXT=qt56
export COINDIR=C:/Coin/4.0.0a

# Set up the build environment.
# The next few lines will move the cygwin compile tools to end of path so MSVS tools are found first.
unset CC
unset CXXmake
[ -n "${TMP}" ] || export TMP=/tmp
export PATH=`echo $PATH|sed 's,\(/usr/local/bin:/usr/bin\):\(.*\),\2:\1,'`
export COINDIR=`cygpath "$COINDIR"`

export COIN_BLD_DIR=/cygdrive/c/src/coin/build/$BUILD_TYPE
mkdir $COIN_BLD_DIR
cd $COIN_BLD_DIR

# Disabling pkg-config seems to be fairly important:
# Release libraries:
if [ "$BUILD_TYPE" == "release" ] || [ "$BUILD_TYPE" == "" ]; then
echo "this is a release build!"
/cygdrive/c/src/coin/configure --disable-pkgconfig --prefix=$COINDIR --with-coin=$COINDIR --with-msvcrt=md --disable-debug
fi

# Debug libraries:
if [ "$BUILD_TYPE" == "debug" ]; then
echo "this is a debug build!"
/cygdrive/c/src/coin/configure --disable-pkgconfig --prefix=$COINDIR --with-coin=$COINDIR --program-suffix=d --with-suffix=d --with-msvcrt=mdd
fi

cd $BUILD_TYPE

export PATH="/cygdrive/c/Program Files (x86)/Microsoft Visual Studio 14.0/VC/bin/amd64:$PATH"

echo "Next step is to run make -- do not use -j option"
