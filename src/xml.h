#ifndef XML_H
#define XML_H

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#define TAG(file, tag, ...) if ((__xml_tag_open = 0)) {} else       \
        for (print_opening_tag(file, false, tag, ##__VA_ARGS__, NULL);  \
             !__xml_tag_open;                                       \
             print_closing_tag(file, tag), __xml_tag_open = 1)

#define CTAG(file, tag, ...) print_opening_tag(file, true, tag, ##__VA_ARGS__, NULL)

extern int __xml_tag_open;

/**
 * Prints a tag opening (<tag>) to the file.
 * \param file File.
 * \param closep Should the tag be closed.
 * \param tag Tag name.
 * \param ... A list of pairs "attribute", "value", terminated by NULL
 *          value.
 */
void print_opening_tag(FILE *file, bool closep, const char *tag, ...);

/**
 * Prints a closing tag (</tag>) to the file.
 * \param file File.
 * \param tag Tag name.
 */
void print_closing_tag(FILE *file, const char *tag);

void print_escaped(FILE *file, const char *str);

#endif // XML_H
