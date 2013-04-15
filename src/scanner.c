#include "scanner.h"

static struct token *return_bad_char(struct scanner *scanner){
    struct token *ret = create_token(ERROR);
    ret->error.type = BAD_CHAR;
    ret->error.c = scanner->current;
    set_line_column(ret, scanner->line, scanner->column);
    return ret;
}

struct scanner *create_scanner(FILE *file) {
    struct scanner ret = malloc(sizeof(struct scanner));
    ret->current = 0;
    ret->next = fgetc(file);
    ret->line = 0;
    ret->column = -1;
    return ret;
}

void free_scanner(struct scanner *scanner) {
    free(scanner);
}

struct token *get_token(struct scanner *scanner) {
    struct token *token = NULL;
    char c = get_char(scanner);
    
    if (isalpha(c)) {
        /* IDENT, KEYWORD */
        
    } else if (isdigit(c)) {
        /* NUMBER */
        
    } else if (c == '.') {
        /* DOT */
        
        token = create_token(DOT);
        set_line_column(token, scanner->line, scanner->column);
    } else if (c == ',') {
        /* COMMA */
        
        token = create_token(COMMA);
        set_line_column(token, scanner->line, scanner->column);
    } else if (c == ';') {
        /* SEMICOLON */
        
        token = create_token(SEMICOLON);
        set_line_column(token, scanner->line, scanner->column);
    } else if (c == ':') {
        /* ASSIGNMENT */
        
        c = get_char(scanner);
        if (c == '=') {
            token = create_token(ASSIGNMENT);
            set_line_column(token, scanner->line, scanner->column);
        } else {
            token = return_bad_char(scanner);
        }
    } else if (c == '=') {
        /* EQ */

        token = create_token(EQ);
        set_line_column(token, scanner->line, scanner->column); 
    } else if (c == '#') {
        /* NEQ */

        token = create_token(NEQ);
        set_line_column(token, scanner->line, scanner->column); 
    } else if (c == '<') {
        /* LT, LE */
        
        if (scanner->next == '=') {
            get_char(scanner);
            token = create_token(LE);
            set_line_column(token, scanner->line, scanner->column - 1);
        } else {
            token = create_token(LT);
            set_line_column(token, scanner->line, scanner->column);
        }
    }

    return token;
}

char get_char(struct scanner *scanner) {
    scanner->current = scanner->next;
    scanner->next = fgetc(file);

    if (scanner->current == '\n') {
        ++scanner->line;
        scanner->column = 0;
    } else {
        ++scanner->column;
    }

    return scanner->current;
}
