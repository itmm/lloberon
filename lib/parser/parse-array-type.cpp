#include "parser/parser.h"

bool Parser::parse_array_type(sema::Array_Type& array_type) {
    array_type.clear();
    if (consume(token::keyword_ARRAY)) { return true; }
    if (parse_length()) { return true; }
    while (token_.is(token::comma)) {
        advance();
        if (parse_length()) { return true; }
    }
    if (consume(token::keyword_OF)) { return true; }
    lloberon::sema::Type type { array_type.scope() };
    if (parse_type(type)) { return true; }
    return false;
}