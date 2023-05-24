# generate libinchi.so.1 (symlink) and libinchi.so.1.06.00 in `tests` directory

cd ../INCHI-1-SRC/INCHI_API/libinchi/gcc
make -j LIB_DIR=../../../../tests
make clean
