#include "error.h"

void print_error(FILE *file, struct error *error) {
    switch (error->type) {
    case BAD_CHAR:
        fprintf(file, "Unexpected character: %c", error->c);
    }
}

