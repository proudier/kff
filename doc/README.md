
# Documentation

## Building

### Make

https://gl.developpez.com/tutoriel/outil/makefile/
https://stackoverflow.com/questions/448910/what-is-the-difference-between-the-gnu-makefile-variable-assignments-a
https://www.gnu.org/software/make/manual/html_node/File-Name-Functions.html#File-Name-Functions

### GCC

[Options summary](https://gcc.gnu.org/onlinedocs/gcc-8.2.0/gcc/Option-Summary.html#Option-Summary)
[About freestanding](https://gcc.gnu.org/onlinedocs/gcc/Standards.html#Standards)

## UEFI
https://wiki.osdev.org/UEFI
https://www.uefi.org/sites/default/files/resources/UEFI_Spec_2_7.pdf
Print description and flags print.c:980


## Debug

UEFI debug with GDB https://sourceforge.net/p/ast-phoenix/code/ci/master/tree/kernel/boot/Makefile#l52
https://web.archive.org/web/20180121183732/http://www.dirac.org:80/linux/gdb

# Misc

docker run --mount type=bind,source="$(pwd)"/src,target=/data --rm=true -ti nsquare-efi bash
