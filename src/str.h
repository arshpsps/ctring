#ifndef STR_H_
#define STR_H_

#include <stddef.h>

typedef struct {
    char *literal;
    size_t len;
    size_t capacity;
} str;

str *Str(char *string);
char *toCString(str *str); // FIXME: strcpy and return the pointer to new allocd space
void append(str *string, char *s);
void prepend(str *string, char *s);
void insert(str *str, char *s, int pos);
int removeFromStr(str *str, size_t pos, size_t size);

#endif
