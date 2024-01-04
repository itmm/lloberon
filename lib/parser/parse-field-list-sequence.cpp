#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_field_list_sequence() {
    if (parse_field_list()) { return true; }
    while (token_.is(token::semicolon)) {
        advance();
        if (parse_field_list()) { return true; }
    }
    return false;
}