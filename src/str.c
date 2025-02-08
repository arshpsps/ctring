#include "./str.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

int isEmpty(char *s) {
    if (s == NULL || strlen(s) <= 0) {
        return 1;
    }
    return 0;
}

void freeStr(str *str) {
    free(str->literal);
    free(str);
}

str *Str(char *string) {
    str *s = malloc(sizeof(str));
    if (isEmpty(string)) {
        s->capacity = 1 * sizeof(char);
        s->literal = malloc(s->capacity);
        s->len = 0;
        return s;
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
        string->capacity = ((strlen(s) * sizeof(char)) + string->capacity) * 2;
        char *tmp = string->literal;
        string->literal = malloc(string->capacity);
        if (!isEmpty(tmp)) {
            strcpy(string->literal, tmp);
        }
        free(tmp);
    }
    strcat(string->literal, s);
    string->len += strlen(s);
}

void prepend(str *string, char *s) {
    if (isEmpty(s)) {
        return;
    }
    if (isEmpty(string->literal)) {
        return append(string, s);
    }
    char *tmp = malloc((string->len + 1) * sizeof(char));
    strcpy(tmp, string->literal);
    if (strlen(s) + string->len >= string->capacity) {
        string->capacity = ((strlen(s) * sizeof(char)) + string->capacity) * 2;
        free(string->literal);
        string->literal = malloc(string->capacity);
    }
    memcpy(string->literal, s, (strlen(s) + 1) * sizeof(char));
    strcat(string->literal, tmp);
    string->len += strlen(s);
    free(tmp);
}

void insert(str *str, char *s, int pos) {
    if (pos > str->len) {
        freeStr(str);
        fprintf(stderr,
                ANSI_COLOR_RED "Invalid pos.\nPoint of error: "
                               "insert()\nTerminating!" ANSI_COLOR_RESET "\n");
        exit(-1);
    }
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
            freeStr(str);
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
        freeStr(str);
        fprintf(stderr, ANSI_COLOR_RED
                "Invalid pos/size or str empty.\nPoint of error: "
                "removeFromStr()\nTerminating!" ANSI_COLOR_RESET "\n");
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
            freeStr(str);
            exit(-1);
        }
        str->literal = tmp;
    }

    return prev_len - str->len;
}
