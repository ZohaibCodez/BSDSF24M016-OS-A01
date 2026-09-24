#include "../include/mystrfunctions.h"
#include <stddef.h>   // for NULL

// Count characters until we reach '\0'.
int mystrlen(const char* s) {
    if (s == NULL) return -1;
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

// Copy src into dest, including the '\0'. Returns number of chars copied.
int mystrcpy(char* dest, const char* src) {
    if (dest == NULL || src == NULL) return -1;
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';   // don't forget the terminator!
    return i;
}

// Copy at most n chars. Works like the standard strncpy:
// if src is shorter than n, the rest of dest is filled with '\0'.
// If src is n chars or longer, dest is NOT null-terminated (caller must handle it).
int mystrncpy(char* dest, const char* src, int n) {
    if (dest == NULL || src == NULL || n < 0) return -1;
    int i = 0;
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    int copied = i;
    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    return copied;
}

// Append src to the end of dest. Returns the new length of dest.
int mystrcat(char* dest, const char* src) {
    if (dest == NULL || src == NULL) return -1;
    int d = mystrlen(dest);   // position of dest's '\0'
    int i = 0;
    while (src[i] != '\0') {
        dest[d + i] = src[i];  // overwrite the old '\0' and continue
        i++;
    }
    dest[d + i] = '\0';
    return d + i;
}
