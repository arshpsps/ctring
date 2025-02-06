#include "./str.h"
#include <stdlib.h>
#include <string.h>

int isEmpty(char *s) {
    if (strlen(s) <= 0) {
        return 1;
    }
    return 0;
}

str *Str(char *string) {
    str *s = malloc(sizeof(str));
    if (isEmpty(string)) {
        s->capacity = 0;
        s->len = 0;
    }

    s->capacity = 2 * strlen(string) * sizeof(char);
    s->literal = malloc(s->capacity);
    strcpy(s->literal, string);
    s->len = strlen(s->literal);

    return s;
}

char *toCString(str *str) { return str->literal; }

void append(str *string, char *s) {
    if (isEmpty(s)) {
        return;
    }
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
    if (isEmpty(s)) {
        return;
    }
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

void insert(str *str, char *s, int pos) {
    if (isEmpty(s)) {
        return;
    }
    if (pos == 0) {
        return append(str, s);
    } else if (pos == str->len) {
        return prepend(str, s);
    }
    if ((strlen(s) + str->len) >= str->capacity) {
        char *re = realloc(str->literal,
                           (strlen(s) + str->len + 1) * sizeof(char) * 2);
        if (!re) {
            exit(-1);
        }
        str->literal = re;
        str->capacity = (strlen(s) + str->len + 1) * sizeof(char) * 2;
    }
    char *tmp = malloc((str->len - pos + 1) * sizeof(char));
    int j = 0;
    for (int i = pos; i < str->len + 1; i++) {
        tmp[j] = str->literal[i];
        j++;
    }
    str->literal[pos] = '\0';
    strcat(str->literal, s);
    strcat(str->literal, tmp);
    free(tmp);
    str->len += strlen(s);
}

int removeFromStr(str *str, size_t pos, size_t size) {
    if (pos < 0 || pos >= str->len || pos + size > str->capacity) {
        exit(-1);
    };
    int prev_len = strlen(str->literal);

    int i = pos;
    for (int j = pos + size; str->literal[j] != '\0'; j++) {
        str->literal[i] = str->literal[j];
        i++;
    }
    str->literal[i] = '\0';
    str->len = strlen(str->literal);

    if (str->len < str->capacity / 2) {
        str->capacity = (str->len + 1) * 1.5 * sizeof(char);
        char *tmp = realloc(str->literal, str->capacity);
        if (!tmp) {
            exit(-1);
        }
        str->literal = tmp;
    }

    return prev_len - str->len;
}
