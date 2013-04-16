#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "scanner.h"

#define BUFFER_SIZE 64

static struct token *return_bad_char(struct scanner *scanner) {
    struct token *ret = create_token(ERROR);
    ret->error.type = BAD_CHAR;
    ret->error.c = scanner->current;
    set_line_column(ret, scanner->line, scanner->column);
    return ret;
}

struct scanner *create_scanner(FILE *file) {
    struct scanner *ret = malloc(sizeof(struct scanner));
    ret->file = file;
    ret->current = 0;
    ret->next = fgetc(file);
    ret->line = 0;
    ret->column = -1;
    ret->new_line_encoutered = false;
    return ret;
}

void free_scanner(struct scanner *scanner) {
    free(scanner);
}

struct token *get_token(struct scanner *scanner) {
    struct token *token = NULL;
    char c = get_char(scanner);
    
    if (isalpha(c)) {
        int i = 0;
        struct token *second_token = create_token(KEYWORD);
        token = create_token(IDENT);
        
        set_line_column(token, scanner->line, scanner->column);
        set_line_column(second_token, scanner->line, scanner->column);
        
        token->ident[0] = c;
        while (isalnum(scanner->next)) {
            token->ident[++i] = get_char(scanner);
        }

        /* check for keyword */
        keyword_t keyword = str_to_keyword(token->ident);
        if (keyword != NOT_KEYWORD) {
            free_token(token);
            token = second_token;
            token->keyword = keyword;
        } else {
            free_token(second_token);
        }
    } else if (isdigit(c)) {
        int i = 0;
        char buffer[BUFFER_SIZE];
        memset(buffer, 0, BUFFER_SIZE);
        token = create_token(NUMBER);
        
        set_line_column(token, scanner->line, scanner->column);
        
        buffer[0] = c;
        while (isdigit(scanner->next)) {
            buffer[++i] = get_char(scanner);
        }
        
        token->number = atoi(buffer);
    } else if (c == '.') {
        token = create_token(DOT);
        set_line_column(token, scanner->line, scanner->column);
    } else if (c == ',') {
        token = create_token(COMMA);
        set_line_column(token, scanner->line, scanner->column);
    } else if (c == ';') {
        token = create_token(SEMICOLON);
        set_line_column(token, scanner->line, scanner->column);
    } else if (c == ':') {
        c = get_char(scanner);
        
        if (c == '=') {
            token = create_token(ASSIGNMENT);
            set_line_column(token, scanner->line, scanner->column - 1);
        } else {
            token = return_bad_char(scanner);
        }
    } else if (c == '=') {
        token = create_token(EQ);
        set_line_column(token, scanner->line, scanner->column); 
    } else if (c == '#') {
        token = create_token(NEQ);
        set_line_column(token, scanner->line, scanner->column); 
    } else if (c == '<') {
        if (scanner->next == '=') {
            get_char(scanner);
            token = create_token(LE);
            set_line_column(token, scanner->line, scanner->column - 1);
        } else {
            token = create_token(LT);
            set_line_column(token, scanner->line, scanner->column);
        }
    } else if (c == '>') {
        if (scanner->next == '=') {
            get_char(scanner);
            token = create_token(GE);
            set_line_column(token, scanner->line, scanner->column - 1);
        } else {
            token = create_token(GT);
            set_line_column(token, scanner->line, scanner->column);
        }
    } else if (c == '/') {
        token = create_token(DIV);
        set_line_column(token, scanner->line, scanner->column); 
    } else if (c == '*') {
        token = create_token(MUL);
        set_line_column(token, scanner->line, scanner->column); 
    } else if (c == '-') {
        token = create_token(SUB);
        set_line_column(token, scanner->line, scanner->column); 
    } else if (c == '+') {
        token = create_token(ADD);
        set_line_column(token, scanner->line, scanner->column); 
    } else if (c == '(') {
        token = create_token(LEFTPAREN);
        set_line_column(token, scanner->line, scanner->column); 
    } else if (c == ')') {
        token = create_token(RIGHTPAREN);
        set_line_column(token, scanner->line, scanner->column); 
    } else if (c == ' ') {
        token = create_token(SPACE);
        set_line_column(token, scanner->line, scanner->column); 
    } else if (c == '\n') {
        token = create_token(EOL);
        set_line_column(token, scanner->line, scanner->column); 
    } else if (feof(scanner->file)) {
        token = create_token(EOF_T);
        set_line_column(token, scanner->line, scanner->column); 
    } else {
        token = return_bad_char(scanner);
    } 

    return token;
}

char get_char(struct scanner *scanner) {
    scanner->current = scanner->next;
    scanner->next = fgetc(scanner->file);

    if (scanner->new_line_encoutered) {
        ++scanner->line;
        scanner->column = 0;
    } else {
        ++scanner->column;
    }
    scanner->new_line_encoutered = scanner->current == '\n';

    return scanner->current;
}
