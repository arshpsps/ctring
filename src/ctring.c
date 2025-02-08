#include "./ctring.h"
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

void freeStr(Ctring *ctring) {
    free(ctring->literal);
    free(ctring);
}

Ctring *ctring(char *ctring) {
    Ctring *s = malloc(sizeof(Ctring));
    if (isEmpty(ctring)) {
        s->capacity = 1 * sizeof(char);
        s->literal = malloc(s->capacity);
        s->len = 0;
        return s;
    }

    s->capacity = 2 * strlen(ctring) * sizeof(char);
    s->literal = malloc(s->capacity);
    strcpy(s->literal, ctring);
    s->len = strlen(s->literal);

    return s;
}

char *toCString(Ctring *ctring) { return ctring->literal; }

void append(Ctring *ctring, char *s) {
    if (isEmpty(s)) {
        return;
    }
    if (strlen(s) + ctring->len >= ctring->capacity) {
        ctring->capacity = ((strlen(s) * sizeof(char)) + ctring->capacity) * 2;
        char *tmp = ctring->literal;
        ctring->literal = malloc(ctring->capacity);
        if (!isEmpty(tmp)) {
            strcpy(ctring->literal, tmp);
        }
        free(tmp);
    }
    strcat(ctring->literal, s);
    ctring->len += strlen(s);
}

void prepend(Ctring *ctring, char *s) {
    if (isEmpty(s)) {
        return;
    }
    if (isEmpty(ctring->literal)) {
        return append(ctring, s);
    }
    char *tmp = malloc((ctring->len + 1) * sizeof(char));
    strcpy(tmp, ctring->literal);
    if (strlen(s) + ctring->len >= ctring->capacity) {
        ctring->capacity = ((strlen(s) * sizeof(char)) + ctring->capacity) * 2;
        free(ctring->literal);
        ctring->literal = malloc(ctring->capacity);
    }
    memcpy(ctring->literal, s, (strlen(s) + 1) * sizeof(char));
    strcat(ctring->literal, tmp);
    ctring->len += strlen(s);
    free(tmp);
}

void insert(Ctring *ctring, char *s, int pos) {
    if (pos > ctring->len) {
        freeStr(ctring);
        fprintf(stderr,
                ANSI_COLOR_RED "Invalid pos.\nPoint of error: "
                               "insert()\nTerminating!" ANSI_COLOR_RESET "\n");
        exit(-1);
    }
    if (isEmpty(s)) {
        return;
    }
    if (pos == 0) {
        return append(ctring, s);
    } else if (pos == ctring->len) {
        return prepend(ctring, s);
    }
    if ((strlen(s) + ctring->len) >= ctring->capacity) {
        char *re = realloc(ctring->literal,
                           (strlen(s) + ctring->len + 1) * sizeof(char) * 2);
        if (!re) {
            freeStr(ctring);
            exit(-1);
        }
        ctring->literal = re;
        ctring->capacity = (strlen(s) + ctring->len + 1) * sizeof(char) * 2;
    }
    char *tmp = malloc((ctring->len - pos + 1) * sizeof(char));
    int j = 0;
    for (int i = pos; i < ctring->len + 1; i++) {
        tmp[j] = ctring->literal[i];
        j++;
    }
    ctring->literal[pos] = '\0';
    strcat(ctring->literal, s);
    strcat(ctring->literal, tmp);
    free(tmp);
    ctring->len += strlen(s);
}

int removeFromCtring(Ctring *ctring, size_t pos, size_t size) {
    if (pos < 0 || pos >= ctring->len || pos + size > ctring->capacity) {
        freeStr(ctring);
        fprintf(stderr, ANSI_COLOR_RED
                "Invalid pos/size or str empty.\nPoint of error: "
                "removeFromStr()\nTerminating!" ANSI_COLOR_RESET "\n");
        exit(-1);
    };
    int prev_len = strlen(ctring->literal);

    int i = pos;
    for (int j = pos + size; ctring->literal[j] != '\0'; j++) {
        ctring->literal[i] = ctring->literal[j];
        i++;
    }
    ctring->literal[i] = '\0';
    ctring->len = strlen(ctring->literal);

    if (ctring->len < ctring->capacity / 2) {
        ctring->capacity = (ctring->len + 1) * 1.5 * sizeof(char);
        char *tmp = realloc(ctring->literal, ctring->capacity);
        if (!tmp) {
            freeStr(ctring);
            exit(-1);
        }
        ctring->literal = tmp;
    }

    return prev_len - ctring->len;
}
