#ifndef XML_H
#define XML_H

#include <stdio.h>
#include <stdarg.h>

#define TAG(file, tag, ...) if ((__o = 0)) {} else                  \
        for (print_opening_tag(file, 0, tag, ##__VA_ARGS__, NULL);  \
             !__o;                                                  \
             print_closing_tag(file, tag), __o = 1)

#define STAG(file, tag, ...) print_opening_tag(file, 1, tag, ##__VA_ARGS__, NULL)

extern int __o;

/**
 * Prints a tag opening (<tag>) to the file.
 * \param file File.
 * \param tag Tag name.
 * \param ... A list of pairs "attribute", "value", terminated by NULL value.
 */
void print_opening_tag(FILE *file, int closep, const char *tag, ...);

/**
 * Prints a closing tag (</tag>) to the file.
 * \param file File.
 * \param tag Tag name.
 */
void print_closing_tag(FILE *file, const char *tag);

void print_escaped(FILE *file, const char *str);

#endif // XML_H
