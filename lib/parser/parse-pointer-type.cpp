#include "parser/parser.h"

bool Parser::parse_pointer_type(lloberon::sema::Pointer_Type& pointer_type) {
    if (consume(token::keyword_POINTER)) { return true; }
    if (consume(token::keyword_TO)) { return true; }
    lloberon::sema::Type type { pointer_type.scope() };
    if (parse_type(type)) { return true; }
    return false;
}