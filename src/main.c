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
    strcpy(s->literal, string);
    s->len = strlen(s->literal);

    return s;
}

char *toCString(str *str) { return str->literal; }

void append(str *string, char *s) {
    if (strlen(s) + string->len >= string->capacity) {
        string->capacity = (strlen(s) * sizeof(char)) + string->capacity;
        char *tmp = string->literal;
        string->literal = malloc(string->capacity);
        strcpy(string->literal, tmp);
        free(tmp);
    }
    strcat(string->literal, s);
    string->len += strlen(s);
}
void prepend(str *string, char *s) {
    char *tmp = malloc((string->len + 1) * sizeof(char));
    strcpy(tmp, string->literal);
    if (strlen(s) + string->len >= string->capacity) {
        string->capacity = (strlen(s) * sizeof(char)) + string->capacity;
        free(string->literal);
        string->literal = malloc(string->capacity);
    }
    memcpy(string->literal, s, (strlen(s) + 1) * sizeof(char));
    strcat(string->literal, tmp);
    string->len += strlen(s);
    free(tmp);
}
void insert(str *str, int pos);

int main() {
    str *s = Str("Hihhhhhhhh");
    printf("%s\n", s->literal);
    printf("%zu/%zu\n", s->len, s->capacity);
    append(s, " hjjjjjiijjjjjjjjjjjjjjjjjjiiiiiiiiiiiiiiiiiiiiiiiiiii");
    printf("%s\n", s->literal);
    printf("%zu/%zu\n", s->len, s->capacity);
    prepend(s, "Oh ");
    printf("%s\n", s->literal);
    printf("%zu/%zu\n", s->len, s->capacity);
    prepend(s, "1234568888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888887");
    printf("%s\n", s->literal);
    printf("%zu/%zu\n", s->len, s->capacity);
    free(s->literal);
    free(s);

    return 0;
}
