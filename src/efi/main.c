#include "kff.h"

#include <efi.h>
#include <efilib.h>

volatile int wait = 666;

void efi_dump_memmap(const EFI_BOOT_SERVICES *bootsrv);
void _wait_for_gdb(EFI_HANDLE imghdl, const EFI_BOOT_SERVICES *bootsrv);

void efi_check_error (EFI_STATUS status, const char *msg) {
    if (EFI_ERROR (status)) {
        Print(L"%s failed: %r\n", msg, status);
    }
}

EFI_STATUS EFIAPI efi_main (EFI_HANDLE imghdl, EFI_SYSTEM_TABLE *systab)
{
    InitializeLib (imghdl, systab);
    Print (L"Entering efi_main\n");

    _wait_for_gdb(imghdl, systab->BootServices);


    console_init();

    //efi_check_error (uefi_call_wrapper (systab->ConOut->SetMode, 2, systab->ConOut, 2), "SetMode");
    // efi_check_error(uefi_call_wrapper(systab->ConOut->SetMode, 2, systab->ConOut, 2));

    Print (L"FirmwareVendor is '%s', FirmwareRevision is '%u'\n", systab->FirmwareVendor, systab->FirmwareRevision);
    //efi_dump_memmap (systab->BootServices);

    // int c = 'c';
    // int C = my_toupper(c);
    // Print (L"Upper %x is %x \n", c, C);

    Print (L"Hard coded value is %u\n", 50);
    UINTN u = 60;
    Print (L"Stack value is %u\n", u);
    size_t l = 70;
    Print (L"size_t value is %lu\n", l);
    char *src = "Hello GCC";
    Print (L"l = %lu \n", l);
    l = strlen(src);
    Print (L"strlen l = %lu \n", l);

    console->print("fin\n");

    return EFI_SUCCESS;
}



void efi_dump_memmap (const EFI_BOOT_SERVICES *bootsrv) {
    volatile INT8 buf[16 * 1024];
    volatile UINTN buf_size = 16 * 1024 * sizeof(INT8);
    volatile UINTN key = 666;
    volatile UINTN desc_size = 666;
    volatile UINT32 desc_ver = 666;

    Print(L"GetMemoryMap (MemoryMapSize=%u &MemoryMapSize=%lx &MemoryMap=%lx &MapKey=%lx &DescriptorSize=%lx &DescriptorVersion=%lx)\n",
        buf_size, &buf_size, &buf, &key, &desc_size, &desc_ver);
    EFI_STATUS st = uefi_call_wrapper(bootsrv->GetMemoryMap, 5, &buf_size, &buf[0], &key, &desc_size, &desc_ver);
    if (EFI_ERROR(st) ) {
        Print(L"GetMemoryMap Failed: %u\n", st);
        if (st == EFI_BUFFER_TOO_SMALL)
            Print(L"Buffer was tool small, needs %u\n", buf_size);
        return;
    } else {
        Print(L"GetMemoryMap returned: %r\n", st);
    }

    Print(L"<UEFI memory map (key=%u, buf_size=%u, desc_size=%u, desc_ver=%u)\n", key, buf_size, desc_size, desc_ver);

    int i = 0;
    for (void *ptr = (void *)&buf ; ptr < (void *)(buf + buf_size) ; ptr += desc_size ) {
        EFI_MEMORY_DESCRIPTOR *mem_desc = ptr;
        Print(L"%u\tType %u, PhyStart %u, VirtStart %u, NbPages %u\n", i, mem_desc->Type, mem_desc->PhysicalStart, mem_desc->VirtualStart, mem_desc->NumberOfPages);
        i++;
    }
}


void _wait_for_gdb(EFI_HANDLE imghdl, const EFI_BOOT_SERVICES *bootsrv) {
    EFI_LOADED_IMAGE *loaded_image = NULL;
    efi_check_error(uefi_call_wrapper(bootsrv->HandleProtocol, 3,
        imghdl, &LoadedImageProtocol, (void **)&loaded_image), "HandleProtocol");
    Print(L"Waiting for wait to be unset; image base is 0x%lx\n", loaded_image->ImageBase);


    while (wait == 666) {
        __asm__ __volatile__("pause");
    }

    return;
}
