# generate libinchi.so.1 (symlink) and libinchi.so.dev

cd INCHI-1-SRC/INCHI_API/libinchi/gcc
make -j LIB_DIR=../../../../tests VERSION=.dev
make clean
