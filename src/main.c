#include "./str.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    str *s = Str(NULL);
    printf("%s\n", s->literal);
    printf("%zu/%zu\n", s->len, s->capacity);
    removeFromStr(s, 0, 1);
    printf("%s\n", s->literal);
    printf("%zu/%zu\n", s->len, s->capacity);
    insert(s, NULL, 2);
    printf("%s\n", s->literal);
    printf("%zu/%zu\n", s->len, s->capacity);
    append(s, "ih");
    printf("%s\n", s->literal);
    printf("%zu/%zu\n", s->len, s->capacity);
    prepend(s, NULL);
    printf("%s\n", s->literal);
    printf("%zu/%zu\n", s->len, s->capacity);
    append(s, NULL);
    printf("%s\n", s->literal);
    printf("%zu/%zu\n", s->len, s->capacity);
    append(s, "");
    printf("%s\n", s->literal);
    printf("%zu/%zu\n", s->len, s->capacity);
    prepend(s, "");
    printf("%s\n", s->literal);
    printf("%zu/%zu\n", s->len, s->capacity);
    prepend(s, "123456888888888888888888888888888888888888888888888888888888888"
               "888888888888888888888888888888888888888888888888888888888888888"
               "8888888888888888888888887");
    printf("%s\n", s->literal);
    printf("%zu/%zu\n", s->len, s->capacity);
    insert(s, "Oh", 2);
    printf("%s\n", s->literal);
    printf("%zu/%zu\n", s->len, s->capacity);
    removeFromStr(s, 2, 200);
    printf("%s\n", s->literal);
    printf("%zu/%zu\n", s->len, s->capacity);
    removeFromStr(s, 0, 1);
    printf("%s\n", s->literal);
    printf("%zu/%zu\n", s->len, s->capacity);
    removeFromStr(s, 19, 1);
    printf("%s\n", s->literal);
    printf("%zu/%zu\n", s->len, s->capacity);

    free(s->literal);
    free(s);

    return 0;
}
