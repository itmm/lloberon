#include "parser/parser.h"

bool Parser::parse_expression(sema::Expression& expression) {
    sema::Simple_Expression simple_expression { expression.scope() };
    if (parse_simple_expression(simple_expression)) { return true; }
    while (token_.is_one_of(
        token::equals, token::not_equals, token::less, token::less_or_equal,
        token::greater, token::greater_or_equal, token::keyword_IS, token::keyword_IN
    )) {
        advance();
        if (parse_simple_expression(simple_expression)) { return true; }
    }
    return false;
}