/*
 * Console subsystem
 */

#ifndef KFF_CONSOLE_H
#define KFF_CONSOLE_H


/* ==== CONSOLE INTERFACE ===== */

typedef void (*CONSOLE_PRINT)(char *text);
typedef void (*CONSOLE_CLEAR)();

typedef struct {
    char *name;
    CONSOLE_PRINT print;
    CONSOLE_CLEAR clear;
} CONSOLE;

extern CONSOLE *console;


/* ==== CONSOLE IMPLEMENTATIONS INIT ===== */

void efi_console_init();


/* ==== CONSOLE SUBSYSTEM ===== */

// Choose the default implementation and init it
void console_init();

// Bind a new implementation and unbind the previous one without copying anything
void console_attach(CONSOLE *new_console);


#endif
