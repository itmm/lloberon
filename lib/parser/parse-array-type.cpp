#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_array_type() {
    if (consume(token::keyword_ARRAY)) { return true; }
    if (parse_length()) { return true; }
    while (token_.is(token::comma)) {
        advance();
        if (parse_length()) { return true; }
    }
    if (consume(token::keyword_OF)) { return true; }
    if (parse_type()) { return true; }
    return false;
}