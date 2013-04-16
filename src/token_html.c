#include "token_html.h"
#include "xml.h"
#include "token.h"
#include "scanner.h"

static void print_css_stylesheet(FILE *out) {
    fputs(".code { white-space: pre; font-family: \"Courier\", monospace; }", out);
    fputs(".code .keyword { color: blue; font-weight: bold; }", out);
    fputs(".code .number { color: #a66; }", out);
    fputs(".code .operator { color: gray; }", out);
    fputs(".code .error { color: red; font-weight: bold; }", out);
}

static void print_token_html(FILE *out, struct token *token) {
    switch (token->type) {
    case IDENT:
        fputs(token->ident, out);
        break;

    case NUMBER:
        TAG(out, "span", "class", "number") {
            fprintf(out, "%d", token->number);
        }
        break;

    case KEYWORD:
        TAG(out, "span", "class", "keyword") {
            fprintf(out, "%s", keyword_to_str(token->keyword));
        }
        break;

    case DOT:
        fputs(".", out);
        break;

    case COMMA:
        fputs(",", out);
        break;

    case SEMICOLON:
        fputs(";", out);
        break;

    case ASSIGNMENT:
        TAG(out, "span", "class", "operator") {
            fputs(":=", out);
        }
        break;

    case EQ:
        TAG(out, "span", "class", "operator") {
            fputs("=", out);
        }
        break;

    case NEQ:
        TAG(out, "span", "class", "operator") {
            fputs("#", out);
        }
        break;

    case LT:
        TAG(out, "span", "class", "operator") {
            fputs("<", out);
        }
        break;

    case GT:
        TAG(out, "span", "class", "operator") {
            fputs(">", out);
        }
        break;

    case LE:
        TAG(out, "span", "class", "operator") {
            fputs("<=", out);
        }
        break;

    case GE:
        TAG(out, "span", "class", "operator") {
            fputs(">=", out);
        }
        break;

    case DIV:
        TAG(out, "span", "class", "operator") {
            fputs("/", out);
        }
        break;

    case MUL:
        TAG(out, "span", "class", "operator") {
            fputs("*", out);
        }
        break;

    case SUB:
        TAG(out, "span", "class", "operator") {
            fputs("-", out);
        }
        break;

    case ADD:
        TAG(out, "span", "class", "operator") {
            fputs("+", out);
        }
        break;

    case LEFTPAREN:
        fputs("(", out);
        break;

    case RIGHTPAREN:
        fputs(")", out);
        break;

    case SPACE:
        fputs(" ", out);
        break;

    case EOL:
        fputs("\n", out);
        break;

    case ERROR:
        fprintf(out, "Error at line %d, column %d: ", token->line, token->column);
        print_error(out, &token->error);
        fputs("\n", out);
        
    default:
        break;
    }
}

void scan_and_print_tokens(const char *title, FILE *in, FILE *out) {
    struct scanner *scanner = create_scanner(in);

    fprintf(out, "<!DOCTYPE html>");
    TAG(out, "html") {
        TAG(out, "head") {
            TAG(out, "title") {
                fputs(title, out);
            }
            TAG(out, "style", "type", "text/css") {
                print_css_stylesheet(out);
            }
        }
        TAG(out, "body"){
            TAG(out, "div", "class", "code") {
                while (true) {
                    struct token *token = get_token(scanner);
                    print_token_html(out, token);

                    if (token->type == EOF_T || token->type == ERROR) {
                        free_token(token);
                        break;
                    } else {
                        free_token(token);
                    }
                }

            }
        }
    }
    
    free_scanner(scanner);
}
