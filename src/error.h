#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

/** Possible error types. */
typedef enum {
    /** Bad character input. */
    BAD_CHAR
} error_type_t;

/** Error structure. */
struct error_t {
    error_type_t type;
    char c;
};

/**
 * Prints error to the output.
 * \param file Output stream.
 * \param error Error to print.
 */
void print_error(FILE *file, struct error_t *error);

#endif // ERROR_H
