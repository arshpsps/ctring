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

    s->capacity = 2 * strlen(string) * sizeof(char);
    s->literal = malloc(s->capacity);
    strcpy(string, s->literal);
    s->len = strlen(s->literal);

    return s;
}

char *toCString(str *str) { return str->literal; }
void append(str *string, char *s) {
    if (strlen(s) + string->len >= string->capacity) {
        string->capacity *= 2;
        char *tmp = string->literal;
        string->literal = malloc(string->capacity);
        strcpy(string->literal, tmp);
    }
    strcat(string->literal, s);
    string->len += strlen(s);
};
void prepend(str *string, char *s) {
    char *tmp = string->literal;
    if (strlen(s) + string->len >= string->capacity) {
        string->capacity *= 2;
        string->literal = malloc(string->capacity);
    }
    memcpy(string->literal, s, (strlen(s) + 1) * sizeof(char));
    strcat(string->literal, tmp);
    string->len += strlen(s);
};
void insert(str *str, int pos);

int main() {
    printf("hi");

    return 0;
}
