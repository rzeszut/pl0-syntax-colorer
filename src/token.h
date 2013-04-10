#ifndef TOKEN_H
#define TOKEN_H

#include "error.h"

#define MAX_IDENT_LENGTH 64


/** Token types. */
typedef enum {
    /** Identifier. */
    IDENT,
    
    /** Integer number. */
    NUMBER,
    
    /** Keyword; one of the keywords from keyword_t. */
    KEYWORD,
    
    /** Dot: '.'. */
    DOT,
    
    /** Comma: ','. */
    COMMA,
    
    /** Semicolon: ';'. */
    SEMICOLON,
    
    /** Assignment operator: ':='. */
    ASSIGNMENT,
    
    /** Equality sign: '='. */
    EQ,
    
    /** Not equal: '#'. */
    NEQ,
    
    /** Less than: '<'. */
    LT,
    
    /** Greater than: '>'. */
    GT,
    
    /** Less or equal: '<='. */
    LE,
    
    /** Greater or equal: '>='. */
    GE,
    
    /** Division operator: '/'. */
    DIV,
    
    /** Multiplication operator: '*'. */
    MUL,
    
    /** Subraction operator: '-'. */
    SUB,
    
    /** Addition operator: '+'. */
    ADD,
    
    /** Left paren: '('. */
    LEFTPAREN,
    
    /** Right paren: ')'. */
    RIGHTPAREN,
    
    /** A space character. */
    SPACE,
    
    /** End-of-line character. */
    EOL,
    
    /** End-of-file token. */
    EOF_T,
    
    /** Scanning error. */
    ERROR
} type_t;

/** Keywords table. */
typedef enum {
    NOT_KEYWORD = -1,
    CONST = 0,
    VAR,
    PROCEDURE,
    CALL,
    BEGIN,
    END,
    IF,
    THEN,
    WHILE,
    DO,
    ODD
} keyword_t;

/** The token structure. */
struct token_t {
    /** Type of the token. */
    type_t type;
    
    /** Starting line. */
    unsigned line;
    
    /** Starting column */
    unsigned column;
    
    union {
        /** Identifier. */
        char *ident;
        
        /** Or number. */
        unsigned number;
        
        /** Or keyword. */
        keyword_t keyword;
        
        /** Or structure containing error info. */
        struct error_t error;
    };
};

/**
 * Creates a token with the given type.
 * \param type Type.
 * \return New token.
 */
struct token_t *create_token(type_t type);

/**
 * Frees the memory.
 * \param token Token.
 */
void free_token(struct token_t *token);

/**
 * Sets column and line members in token.
 * \param token Token.
 * \param line Line number.
 * \param column Column number.
 */
void set_line_column(struct token_t *token, unsigned line, unsigned column);

/**
 * Prints token info to the file.
 * \param file Output stream.
 * \param token Token to print.
 */
void print_token(FILE *file, struct token_t *token);

/**
 * Prints a string representation of the token ot the buffer.
 * \param token Token.
 * \param buffer Buffer.
 * \param size The size of the buffer.
 */
void token_to_str(struct token_t *token, char *buffer, unsigned size);

/**
 * Returns a string representing the keyword.
 * \param keyword Keyword.
 * \return A string representing the keyword.
 */
const char *keyword_to_str(keyword_t keyword);

/**
 * Converts the string into keyword_t.
 * \param str String.
 * \return Keyword, or -1 (NOT_KEYWORD) if a string is not a keyword.
 */
keyword_t str_to_keyword(const char *str);

#endif // TOKEN_H
