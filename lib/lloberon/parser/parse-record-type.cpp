#include "parser/parser.h"

bool Parser::parse_record_type(sema::Type& type) {
    sema::Record_Type record_type { type.scope() };
    if (consume(token::keyword_RECORD)) { return true; }
    if (token_.is(token::left_parenthesis)) {
        advance();
        if (parse_base_type(record_type)) { return true; }
        if (consume(token::right_parenthesis)) { return true; }
    }
    if (! token_.is(token::keyword_END)) {
        if (parse_field_list_sequence(record_type)) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    return false;
}