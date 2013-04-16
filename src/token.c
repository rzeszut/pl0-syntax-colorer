#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "token.h"

static const char *keywords[] = {
    "CONST",
    "VAR",
    "PROCEDURE",
    "CALL",
    "BEGIN",
    "END",
    "IF",
    "THEN",
    "WHILE",
    "DO",
    "ODD"
};

static bool string_compare_case_insensitive(const char *s1, const char *s2) {
    for ( ; toupper(*s1) == toupper(*s2); s1++, s2++) {
        if (*s1 == '\0') {
            return true;
        }
    }
    return *s1 == *s2;
}

struct token *create_token(type_t type) {
    struct token *ret = malloc(sizeof(struct token));
    ret->type = type;
    
    switch (type) {
    case IDENT:
        ret->ident = malloc(MAX_IDENT_LENGTH * sizeof(char));
        memset(ret->ident, 0, MAX_IDENT_LENGTH);
        break;

    case KEYWORD:
        ret->keyword = NOT_KEYWORD;
        break;
        
    default:
        ret->number = 0;
    }
    
    return ret;
}

void free_token(struct token *token)  {
    switch (token->type) {
    case IDENT:
        free(token->ident);
        
    default:
        break;
    }
    free(token);
}

void set_line_column(struct token *token, unsigned line, unsigned column)  {
    token->line = line;
    token->column = column;
}

void print_token(FILE *file, struct token *token) {
    fprintf(file, "(%d, %d) ", token->line, token->column);

    switch (token->type) {
    case IDENT:
        fprintf(file, "IDENT: %s", token->ident);
        break;

    case NUMBER:
        fprintf(file, "NUMBER: %d", token->number);
        break;

    case KEYWORD:
        fprintf(file, "KEYWORD: %s", keyword_to_str(token->keyword));
        break;

    case DOT:
        fprintf(file, "DOT");
        break;

    case COMMA:
        fprintf(file, "COMMA");
        break;

    case SEMICOLON:
        fprintf(file, "SEMICOLON");
        break;

    case ASSIGNMENT:
        fprintf(file, "ASSIGNMENT");
        break;

    case EQ:
        fprintf(file, "EQ");
        break;

    case NEQ:
        fprintf(file, "NEQ");
        break;

    case LT:
        fprintf(file, "LT");
        break;

    case GT:
        fprintf(file, "GT");
        break;

    case LE:
        fprintf(file, "LE");
        break;

    case GE:
        fprintf(file, "GE");
        break;

    case DIV:
        fprintf(file, "DIV");
        break;

    case MUL:
        fprintf(file, "MUL");
        break;

    case SUB:
        fprintf(file, "SUB");
        break;

    case ADD:
        fprintf(file, "ADD");
        break;

    case LEFTPAREN:
        fprintf(file, "LEFTPAREN");
        break;

    case RIGHTPAREN:
        fprintf(file, "RIGHTPAREN");
        break;

    case SPACE:
        fprintf(file, "SPACE");
        break;

    case EOL:
        fprintf(file, "EOL");
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

void token_to_str(struct token *token, char *buffer, unsigned size) {
    switch (token->type) {
    case IDENT:
        memcpy(buffer, token->ident,
               MAX_IDENT_LENGTH > size ? size : MAX_IDENT_LENGTH);
        break;

    case NUMBER:
        snprintf(buffer, size, "%d", token->number);
        break;

    case KEYWORD:
        snprintf(buffer, size, "%s", keyword_to_str(token->keyword));
        break;

    case DOT:
        sprintf(buffer, ".");
        break;

    case COMMA:
        sprintf(buffer, ",");
        break;

    case SEMICOLON:
        sprintf(buffer, ";");
        break;

    case ASSIGNMENT:
        sprintf(buffer, ":=");
        break;

    case EQ:
        sprintf(buffer, "=");
        break;

    case NEQ:
        sprintf(buffer, "#");
        break;

    case LT:
        sprintf(buffer, "<");
        break;

    case GT:
        sprintf(buffer, ">");
        break;

    case LE:
        sprintf(buffer, "<=");
        break;

    case GE:
        sprintf(buffer, ">=");
        break;

    case DIV:
        sprintf(buffer, "/");
        break;

    case MUL:
        sprintf(buffer, "*");
        break;

    case SUB:
        sprintf(buffer, "-");
        break;

    case ADD:
        sprintf(buffer, "+");
        break;

    case LEFTPAREN:
        sprintf(buffer, "(");
        break;

    case RIGHTPAREN:
        sprintf(buffer, ")");
        break;

    case SPACE:
        sprintf(buffer, " ");
        break;

    case EOL:
        sprintf(buffer, "\n");
        break;

    default:
        break;
    }
}

const char *keyword_to_str(keyword_t keyword) {
    if (keyword == NOT_KEYWORD) {
        return NULL;
    } else {
        return keywords[keyword];
    }
}

keyword_t str_to_keyword(const char *str) {
    keyword_t ret = NOT_KEYWORD;
    int i = 0;
    
    for (; i <= ODD; ++i) {
        if (string_compare_case_insensitive(str, keywords[i])) {
            ret = i;
            break;
        }
    }
    
    return ret;
}
