#include <string.h>

#include "xml.h"
#include "token_html.h"

static void print_help(const char *program_name) {
    fprintf(stdout, "Usage: %s [input_file] [output_file]\n", program_name);
}

int main(int argc, char **argv) {
    FILE *in = NULL;
    FILE *out = NULL;
    
    if (argc < 2) {
        in = stdin;
    } else {
        if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
            print_help(argv[0]);
            return 1;
        }
        
        in = fopen(argv[1], "r");
    }
    
    if (argc == 3) {
        out = fopen(argv[2], "w");
    } else {
        out = stdout;
    }

    scan_and_print_tokens(argc > 1 ? argv[1] : "untitled", in, out);

    fclose(in);
    fclose(out);
    
    return 0;
}
