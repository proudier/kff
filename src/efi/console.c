/*
 * Implementation of the CONSOLE interface based on UEFI
 */

#include "kff.h"

#include <efi.h>
#include <efilib.h>


CONSOLE _eficon;

void _print(char *);
void _clear();


void efi_console_init () {
    _eficon.name = "UEFI text console";
    _eficon.print = _print;
    _eficon.clear = _clear;
    console_attach (&_eficon);
}

void _print (char *text) {
    APrint ((unsigned char *)text);
}

void _clear () {

}
