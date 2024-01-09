#include "parser/parser.h"

bool Parser::parse_field_list_sequence(sema::Record_Type& record_type) {
    if (parse_field_list(record_type)) { return true; }
    while (token_.is(token::semicolon)) {
        advance();
        if (parse_field_list(record_type)) { return true; }
    }
    return false;
}