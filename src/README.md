This is KFF - the Kernel For Fun. Don't expect any _grandiose_ outcome from this; this is strictly a learning project.

# How to build (cross-compile)

## Set up your cross-compiler

### Preparations

`mkdir -p $XGCC/src`

Download and extract under `$XGCC/src`
- [https://ftp.gnu.org/gnu/binutils/](Binutils)
- [https://ftp.gnu.org/gnu/gcc/](GCC)

The following versions are known to work together:
- binutils-2.31.1
- gcc-8.2.0

Edit `$XGCC/env.sh`:

```
export PREFIX="$HOME/Applications/xgcc"
export TARGET=x86_64-elf
export PATH="$PREFIX/bin:$PATH"
```

Source `$XGCC/env.sh`: in your shell:
```
source $XGCC/env.sh
```

### Compile Binutils

```
cd $XGCC/src/binutils-X.Y.Z
./configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror --enable-targets=all
make -j12
make install
```

### Compile GCC

#### LibGCC with no-red-zone

Go to `$XGCC/src/gcc.X.Y.Z/`

Ensure libgcc is built with no redzone – Add this to `gcc/config/i386/t-x86_64-elf`:

```
# Add libgcc multilib variant without red-zone requirement
MULTILIB_OPTIONS += mno-red-zone
MULTILIB_DIRNAMES += no-red-zone
```

Edit `gcc/config.gcc` with your favorite editor and search for the case `x86_64-*-elf*)`

Add the following line above the `tm_file` line:
```
tmake_file="${tmake_file} i386/t-x86_64-elf" # include the new multilib configuration
```

#### Out-of-source GCC build

```
cd $XGCC/src; mkdir build-gcc; cd build-gcc
../gcc-X.Y.Z/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c --without-headers
make -j12 all-gcc
make install-gcc
make -j12 all-target-libgcc
make install-target-libgcc
```

to check LibGCC compiled with no-red-zone, the following command
```
x86_64-elf-gcc -mno-red-zone -print-libgcc-file-name
```
should return someting like
```
$XGCC/lib/gcc/x86_64-elf/X.Y.Z/no-red-zone/libgcc.a
```

Source:
- [Libgcc on OSDEV ](https://wiki.osdev.org/Libgcc_without_red_zone)
- [Official GCC page on compilation](https://gcc.gnu.org/install/configure.html)

## Build KFF

To launch KFF in a VM, execute `make run`

To generate a UEFI app, execute `make efi`


# How to build (Docker) [obsolete]

The build takes place in a Docker container.

The following shall be installed on the build machine:
- make
- docker

Then:
- Clone the repository
- Run `make efi`


## Testing

Execute `make run` to start KFF in Qemu/KVM

# Installation

If your are mad enough to run KFF on your actual computer...

The following lines consider that your EFI system partition is mounted under `/boot/EFI` on the disk `/dev/nvme0n1`.

 - Copy `kff.efi` to `/boot/EFI/BOOT/`
 - Run `sudo efibootmgr -c -LKFF -l\EFI\Boot\kff.efi -d /dev/nvme0n1`

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

# TODO

GCC requires the freestanding environment provide memcpy, memmove, memset and memcmp.
