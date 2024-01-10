#include "parser/parser.h"

bool Parser::parse_simple_expression(sema::Expression& simple_expression) {
    if (token_.is_one_of(token::plus, token::minus)) {
        advance();
    }
    Scope scope;
    if (parse_term(simple_expression)) { return true; }
    while (token_.is_one_of(token::plus, token::minus, token::keyword_OR)) {
        advance();
        if (parse_term(simple_expression)) { return true; }
    }
    return false;
}