/*
 * Console subsystem
 */

#include "kff.h"

CONSOLE *console;

void efi_console_init ();

void console_init () {
    efi_console_init();
}

void console_attach (CONSOLE *new_console) {
    if(new_console != 0 && new_console->print != 0 && new_console->clear != 0) {
        console = new_console;
        console->print("New console attached successfully\n");
    } else {
        // TODO
    }
}
