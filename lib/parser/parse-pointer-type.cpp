#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_pointer_type(Pointer_Type& pointer_type) {
    if (consume(token::keyword_POINTER)) { return true; }
    if (consume(token::keyword_TO)) { return true; }
    Type type { pointer_type.scope() };
    if (parse_type(type)) { return true; }
    return false;
}