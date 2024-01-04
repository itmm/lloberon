#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_actual_parameters() {
    if (consume(token::left_parenthesis)) { return true; }
    if (!token_.is(token::right_parenthesis)) {
        if (parse_expression_list()) { return true; }
    }
    if (consume(token::right_parenthesis)) { return true; }
    return false;
}