#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *literal;
    size_t len;
    size_t capacity;
} str;

str *Str(char *string) {
    str *s = malloc(sizeof(str));
    s->literal = malloc(2 * strlen(string) * sizeof(char));
    strcpy(string, s->literal);
    s->len = strlen(s->literal);

    return s;
}

char *toCString(str *str) { return str->literal; }
void append(str *string, str s);
void prepend(str *string, str s);
void insert(str *str, int pos);

int main() {
    printf("hi");

    return 0;
}
