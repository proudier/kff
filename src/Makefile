TOPDIR := .

SUBDIRS := efi core
ALL_SO  := $(foreach subdir, $(SUBDIRS), $(subdir)/$(subdir).so)

include $(TOPDIR)/Make.defaults


all: kff.efi

$(SUBDIRS):
	$(MAKE) -C $(TOPDIR)/$@

kff.so: $(SUBDIRS)
	@echo LIGCC $(LIBGCC)
	$(LD) $(ALL_SO) $(EFI_CRT0) -o $@ -T$(EFI_LD_SCRIPT) -znocombreloc -shared -Bsymbolic \
		-nostdlib $(GCC_LIBS) $(EFI_LIBS) $(LDFLAGS) --no-undefined

kff.efi: kff.so
	$(OBJCOPY) $(foreach sec, $(EFI_SECTIONS), -j $(sec)) --target=efi-app-x86_64 kff.so kff.efi
	$(OBJCOPY) $(foreach sec, $(EFI_SECTIONS) $(EFI_DEBUG_SECTIONS), -j $(sec)) --target=efi-app-x86_64 kff.so kff-debug.efi

kff.img: kff.efi startup.nsh
	dd if=/dev/zero of=/tmp/part.img bs=512 count=91669
	mformat -i /tmp/part.img -h 32 -t 32 -n 64 -c 1
	#mcopy -i /tmp/part.img $(EFI_APP) ::
	mcopy -i /tmp/part.img startup.nsh ::
	mmd -i /tmp/part.img EFI
	mmd -i /tmp/part.img EFI/BOOT
	mcopy -i /tmp/part.img kff.efi ::EFI/BOOT/BOOTX64.EFI
	dd if=/dev/zero of=kff.img bs=512 count=98304
	parted kff.img -s -a minimal mklabel gpt
	parted kff.img -s -a minimal mkpart EFI FAT32 2048s 100%
	parted kff.img -s -a minimal toggle 1 boot
	dd if=/tmp/part.img of=kff.img bs=512 count=91669 seek=2048 conv=notrunc
	rm /tmp/part.img

nvram: $(OVMF_PATH)/OVMF_VARS.fd
	cp $(OVMF_PATH)/OVMF_VARS.fd nvram

run: run-kvm

run-kvm: kff.img nvram
	qemu-system-x86_64 -name kff \
		-machine q35 -cpu host -accel kvm -vga virtio -net none -s \
		-drive if=pflash,format=raw,unit=0,file=$(OVMF_PATH)/OVMF_CODE.fd,readonly=on \
		-drive if=pflash,format=raw,unit=1,file=nvram \
		-drive if=virtio,format=raw,file=kff.img

run-qemu: kff.img nvram
	qemu-system-x86_64 -name kff \
		-machine q35 -cpu qemu64 -vga std -net none -s  \
		-drive if=pflash,format=raw,unit=0,file=$(OVMF_PATH)/OVMF_CODE.fd,readonly=on \
		-drive if=pflash,format=raw,unit=1,file=nvram \
		-drive if=ide,format=raw,file=kff.img


BASE=0x6319000
TEXT_OFFSET := $(shell rax2 -k 0x$(shell objdump -hw kff.efi | grep .text | sed 's/[ ]* / /g' | cut -d' ' -f6))
DATA_OFFSET := $(shell rax2 -k 0x$(shell objdump -hw kff.efi | grep .data | sed 's/[ ]* / /g' | cut -d' ' -f6))
TEXT_START:=$$(( $(BASE) + $(TEXT_OFFSET) ))
DATA_START:=$$(( $(BASE) + $(DATA_OFFSET) ))
gdb:
	gdb \
		-ex 'file kff.efi' \
		-ex "add-symbol-file kff-debug.efi $(TEXT_START) -s .data $(DATA_START)" \
		-ex 'set architecture i386:x86-64:intel' \
		-ex 'target remote localhost:1234' \
		-ex 'set wait = 0'


clean:
	rm nvram kff.so kff*.efi kff.img
	for subdir in $(SUBDIRS); do \
		$(MAKE) -C $$subdir clean; \
	done

.PHONY: clean $(SUBDIRS) gdb
