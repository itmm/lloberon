#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_formal_type() {
    while (token_.is(token::keyword_ARRAY)) {
        advance();
        if (consume(token::keyword_OF)) { return true; }
    }
    if (parse_qual_ident()) { return true; }
    return false;
}