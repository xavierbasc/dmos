DM50 Operavive System

SDL2 compilation

cd external/SDL2
./autogen.sh
./configure --prefix=$(pwd)/build --disable-shared --enable-static
make
make install
