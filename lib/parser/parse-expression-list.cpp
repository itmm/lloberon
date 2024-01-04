#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_expression_list() {
    if (parse_expression()) { return true; }
    while (token_.is(token::comma)) {
        advance();
        if (parse_expression()) { return true; }
    }
    return false;
}