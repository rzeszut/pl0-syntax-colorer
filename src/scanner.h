#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>

#include "token.h"

struct scanner {
    FILE *file;
    char current;
    char next;
    unsigned line;
    unsigned column;
};

struct scanner *create_scanner(FILE *file);

void free_scanner(struct scanner *scanner);

struct token *get_token(struct scanner *scanner);

char get_char(struct scanner *scanner);

#endif // SCANNER_H
