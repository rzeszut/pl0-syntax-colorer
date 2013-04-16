#include "xml.h"
#include "token_html.h"

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

    scan_and_print_tokens(argc > 1 ? argv[1] : "untitled", file, out);

    fclose(file);
    fclose(out);
    
    return 0;
}
