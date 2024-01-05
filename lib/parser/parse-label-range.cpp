#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_label_range() {
    Scope scope;
    sema::Label label { scope };
    if (parse_label(label)) { return true; }
    if (token_.is(token::range)) {
        advance();
        if (parse_label(label)) { return true; }
    }
    return false;
}