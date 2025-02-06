#ifndef STR_H_
#define STR_H_

#include <stddef.h>

typedef struct {
    char *literal;
    size_t len;
    size_t capacity;
} str;

str *Str(char *string);
char *toCString(str *str);
void append(str *string, char *s);
void prepend(str *string, char *s);
void insert(str *str, char *s, int pos);

#endif
