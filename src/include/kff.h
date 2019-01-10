#ifndef KFF_H
#define KFF_H


// Freestanding standard C headers
#include <float.h>
#include <iso646.h>
#include <limits.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdnoreturn.h>
#include <stdalign.h>

// Macros
#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x)[0]))
#define ALIGN(x) __attribute__((__aligned__(x)))


// GCC built-ins
#define strcpy(d, s)    __builtin_strcpy ((d), (s))
#define my_toupper(i)      __builtin_toupper (i)
#define strlen(s)       __builtin_strlen (s)


#include "console.h"



void log_init();
void log_info(const char *message);
void log_error(const char *message);


#endif
