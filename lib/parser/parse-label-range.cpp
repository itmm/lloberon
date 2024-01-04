#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_label_range() {
    if (parse_label()) { return true; }
    if (token_.is(token::range)) {
        advance();
        if (parse_label()) { return true; }
    }
    return false;
}