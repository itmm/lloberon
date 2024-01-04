#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_simple_expression(sema::Simple_Expression& simple_expression) {
    if (token_.is_one_of(token::plus, token::minus)) {
        advance();
    }
    Scope scope;
    Term term { simple_expression.scope() };
    if (parse_term(term)) { return true; }
    while (token_.is_one_of(token::plus, token::minus, token::keyword_OR)) {
        advance();
        if (parse_term(term)) { return true; }
    }
    return false;
}