#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_element() {
    if (parse_expression()) { return true; }
    if (token_.is(token::range)) {
        advance();
        if (parse_expression()) { return true; }
    }
    return false;
}