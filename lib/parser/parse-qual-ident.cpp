#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_qual_ident() {
    if (consume(token::identifier)) { return true; }
    if (token_.is(token::period)) {
        advance();
        if (consume(token::identifier)) { return true; }
    }
    return false;
}