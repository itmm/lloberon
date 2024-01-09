#include "parser/parser.h"

#include "type/pointer.h"

bool Parser::parse_pointer_type(sema::Type& type) {
    type.clear();
    if (consume(token::keyword_POINTER)) { return true; }
    if (consume(token::keyword_TO)) { return true; }
    sema::Type points_to { type.scope() };
    if (parse_type(points_to)) { return true; }
    type.type = std::make_shared<type::Pointer>(points_to.type);
    return false;
}