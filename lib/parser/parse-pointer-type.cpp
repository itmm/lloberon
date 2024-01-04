#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_pointer_type() {
    if (consume(token::keyword_POINTER)) { return true; }
    if (consume(token::keyword_TO)) { return true; }
    if (parse_type()) { return true; }
    return false;
}