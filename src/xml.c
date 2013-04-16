#include "xml.h"

int __xml_tag_open = 0;

void print_opening_tag(FILE *file, bool closep, const char *tag, ...) {
    va_list vl;
    const char *attr;
    const char *val;
    
    fprintf(file, "<%s", tag);

    va_start(vl, tag);
    while ((attr = va_arg(vl, const char *))) {
        val = va_arg(vl, const char *);
        if (!val) {
            break;
        }
        fprintf(file, " %s=\"%s\"", attr, val);
    }
    va_end(vl);
    
    if (closep) {
        fprintf(file, " />");
    } else {
        fprintf(file, ">");
    }
}

void print_closing_tag(FILE *file, const char *tag) {
    fprintf(file, "</%s>", tag);
}

void print_escaped(FILE *file, const char *str) {
    while (*str) {
        if (*str == '&') {
            fprintf(file, "&amp;");
        } else if (*str == '<') {
            fprintf(file, "&lt;");
        } else if (*str == '>') {
            fprintf(file, "&gt;");
        } else if (*str == '"') {
            fprintf(file, "&quot;");
        } else {
            fputc(*str, file);
        }
        ++str;
    }
}
