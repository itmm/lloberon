#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_term() {
    if (parse_factor()) { return true; }
    while (token_.is_one_of(
        token::star, token::slash, token::keyword_DIV,
        token::keyword_MOD, token::andop
    )) {
        advance();
        if (parse_factor()) { return true; }
    }
    return false;
}