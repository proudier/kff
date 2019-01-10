TOPDIR := ..

include $(TOPDIR)/Make.defaults
CFLAGS += -isystem/usr/include/efi/ -isystem/usr/include/efi/x86_64/ -DEFI_FUNCTION_WRAPPER

all: $(SO)

include $(TOPDIR)/Make.rules

clean:
	$(RM) *.o *.so

.PHONY: clean
