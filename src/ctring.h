#ifndef STR_H_
#define STR_H_

#include <stddef.h>

typedef struct Ctring {
    char *literal;
    size_t len;
    size_t capacity;

#if defined __cplusplus
    Ctring &operator[](int pos) {
        this->literal;
    }

#endif
} Ctring;

Ctring *ctring(char *string);
char *toCString(
    Ctring *ctring); // FIXME: strcpy and return the pointer to new allocd space
void append(Ctring *ctring, char *s);
void prepend(Ctring *ctring, char *s);
void insert(Ctring *ctring, char *s, int pos);
int removeFromCtring(Ctring *ctring, size_t pos, size_t size);
char get(Ctring *ctring, size_t pos);

#endif
