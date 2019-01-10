FROM base/devel
RUN pacman --noconfirm -Sy gnu-efi-libs parted mtools colorgcc
RUN mkdir /data
WORKDIR /data
CMD ["make"]
