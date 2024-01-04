#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_element() {
    Scope scope;
    sema::Expression expression { scope };
    if (parse_expression(expression)) { return true; }
    if (token_.is(token::range)) {
        advance();
        if (parse_expression(expression)) { return true; }
    }
    return false;
}