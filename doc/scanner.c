#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 256

struct token_t *create_token();

void set_line_column(struct token_t *token, unsigned line, unsigned column);

void free_token(struct token_t *token);

void print_token(FILE *file, struct token_t *token);

void print_error(FILE *file, struct error_t *error);

struct token_t *get_token(FILE *file);

int main(int argc, char **argv) {
    FILE *file = NULL;
    FILE *out = NULL;
    
    if (argc < 2) {
        fprintf(stderr, "Pass filename as argument.\n");
        return 1;
    }
    file = fopen(argv[1], "r");
    if (argc == 3) {
        out = fopen(argv[2], "w");
    } else {
        out = stdout;
    }

    while (1) {
        struct token_t *token = get_token(file);
        print_token(out, token);

        if (token->type == EOF_T || token->type == ERROR) {
            free_token(token);
            break;
        } else {
            free_token(token);
        }
    }

    fclose(file);
    fclose(out);
    
    return 0;
}

void print_token(FILE *file, struct token_t *token) {
    fprintf(file, "(%d, %d) ", token->line, token->column);

    switch (token->type) {
    case IDENT:
        fprintf(file, "IDENT: %s", token->ident);
        break;

    case NUMBER:
        fprintf(file, "NUMBER: %d", token->number);
        break;

    case TEXT:
        fprintf(file, "TEXT: %s", token->text);
        break;

    case COMMENT:
        fprintf(file, "COMMENT: %s", token->comment);
        break;

    case LEFTBR:
        fprintf(file, "LEFTBR");
        break;

    case RIGHTBR:
        fprintf(file, "RIGHTBR");
        break;

    case EQ:
        fprintf(file, "EQ");
        break;

    case EOF_T:
        fprintf(file, "EOF");
        break;
        
    default:
        fprintf(file, "ERROR: ");
        print_error(file, &token->error);
    }
    fprintf(file, "\n");
}

struct token_t *create_token(type_t type) {
    struct token_t *ret = malloc(sizeof(struct token_t));
    ret->type = type;
    switch (type) {
    case IDENT:
    case TEXT:
    case COMMENT:
        ret->text = malloc(BUFFER_SIZE * sizeof(char));
        memset(ret->text, 0, BUFFER_SIZE);
        break;
    default:
        ret->number = 0;
    }
    return ret;
}

void set_line_column(struct token_t *token, unsigned line, unsigned column) {
    token->line = line;
    token->column = column;
}

void free_token(struct token_t *token) {
    switch (token->type) {
    case IDENT:
    case TEXT:
    case COMMENT:
        free(token->text);
    default:
        break;
    }
    free(token);
}

struct token_t *get_token(FILE *file) {
    static char c = 0;
    static char next = ' ';
    static unsigned line = 0, column = -1;
    struct token_t *token = NULL;
    int i = 0;

    while (isspace(next)) {
        if (next == '\n') {
            ++line;
            column = 0;
        } else {
            ++column;
        }
        next = fgetc(file);
    }
    c = next;
    next = fgetc(file);
    
    if (isalpha(c)) { /* ident */
        token = create_token(IDENT);
        set_line_column(token, line, column);
        token->ident[0] = c;
        ++column;
        while (isalnum(next)) {
            c = next;
            next = fgetc(file);
            ++column;
            token->ident[++i] = c;
        }
    } else if (isdigit(c)) { /* number */
        char buffer[BUFFER_SIZE];
        token = create_token(NUMBER);
        set_line_column(token, line, column);
        buffer[0] = c;
        ++column;
        while (isdigit(next)) {
            c = next;
            next = fgetc(file);
            ++column;
            buffer[++i] = c;
        }
        token->number = atoi(buffer);
    } else if (c == '"') { /* text */
        token = create_token(TEXT);
        ++column;
        set_line_column(token, line, column);
        do {
            c = next;
            next = fgetc(file);
            ++column;
            token->ident[i++] = c;
            if (feof(file)) {
                free_token(token);
                token = create_token(ERROR);
                set_line_column(token, line, column);
                token->error.type = BAD_EOF;
                return token;
            } else if (next == '\n') {
                free_token(token);
                token = create_token(ERROR);
                set_line_column(token, line, column);
                token->error.type = BAD_EOL;
                return token;
            }
        } while (next != '"');
        next = fgetc(file);
        ++column;
    } else if (c == '#') { /* comment */
        token = create_token(COMMENT);
        set_line_column(token, line, column);
        do {
            c = next;
            next = fgetc(file);
            token->ident[i++] = c;
            ++column;
        } while (next != '\n' && !feof(file));
    } else if (c == '[') {
        token = create_token(LEFTBR);
        set_line_column(token, line, column++);
    } else if (c == ']') {
        token = create_token(RIGHTBR);
        set_line_column(token, line, column++);
    } else if (c == '=') {
        token = create_token(EQ);
        set_line_column(token, line, column++);
    } else if (feof(file)) {
        token = create_token(EOF_T);
        set_line_column(token, line, column++);
    } else {
        token = create_token(ERROR);
        set_line_column(token, line, column++);
        token->error.type = BAD_CHAR;
        token->error.c = c;
    }

    return token;
}
