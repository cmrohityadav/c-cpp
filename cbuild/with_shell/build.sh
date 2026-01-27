CXX="g++"
CXXFLAGS="-Wall -Wextra -O2 -std=c++17"
INCLUDE_DIR_2="include_cal"
SRC_DIR="src"
APP_DIR="apps"
BUILD_DIR="build"
OBJ_DIR="$BUILD_DIR/obj"
BIN_DIR="$BUILD_DIR/bin"


echo "Creating build directories..."
mkdir -p "$OBJ_DIR/basic"
mkdir -p "$OBJ_DIR/scientific"
mkdir -p "$OBJ_DIR/apps"
mkdir -p "$BIN_DIR"

echo "Compiling core libraries...."

# -Iinclude_cal tells the compiler:
# When you see a #include in my code, start looking for headers inside the folder include_cal
$CXX $CXXFLAGS -I"$INCLUDE_DIR_2" -c "$SRC_DIR/basic/calculator.cpp" -o "$OBJ_DIR/basic/calculator.o"

echo "Compiling applications......."
$CXX $CXXFLAGS -I"$INCLUDE_DIR_2" -c $APP_DIR/basic_calculator/main.cpp -o "$OBJ_DIR/apps/calculator.o"

echo "Linking executables......"
$CXX $CXXFLAGS "$OBJ_DIR/basic/calculator.o" "$OBJ_DIR/apps/calculator.o" -o "$BIN_DIR/simple_calculator"

