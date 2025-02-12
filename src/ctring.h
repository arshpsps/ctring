#ifndef STR_H_
#define STR_H_

#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Ctring {
    char *literal;
    size_t len;
    size_t capacity;

#if defined __cplusplus

    char operator[](int pos) {

        if (this->len <= pos || !this->literal) {
            exit(-1);
        }
        if (pos < 0) {
            if (this->len + pos < 0) {
                exit(-1);
            }
            return this->literal[this->len + pos];
        }
        return this->literal[pos];
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

#ifdef __cplusplus
}
#endif
#endif
