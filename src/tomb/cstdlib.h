/*
 * Subset of the C stdlib for usage in the kernel
 * Shamelessly based on musl
 */

#ifndef KFF_CSTDLIB_H
#define KFF_CSTDLIB_H

typedef unsigned int size_t;
typedef wchar wchar_t;
typedef uint32 uint32_t;

typedef struct __mbstate_t { unsigned __opaque1, __opaque2; } mbstate_t;

size_t mbstowcs(wchar_t *restrict ws, const char *restrict s, size_t wn);
size_t mbsrtowcs(wchar_t *restrict ws, const char **restrict src, size_t wn, mbstate_t *restrict st);

#endif
