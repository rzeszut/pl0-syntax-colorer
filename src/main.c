#include "xml.h"

int main(int argc, char **argv) {
    TAG(stdout, "div", "class", "some-div", "id", "asdf") {
        TAG(stdout, "p") {
            fprintf(stdout, "Lorem ipsum...");
        }
        print_escaped(stdout, "<&>\"");
        STAG(stdout, "br");
    }

    fprintf(stdout, "\n");
    
    return 0;
}
