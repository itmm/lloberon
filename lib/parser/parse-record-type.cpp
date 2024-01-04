#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_record_type() {
    if (consume(token::keyword_RECORD)) { return true; }
    if (token_.is(token::left_parenthesis)) {
        advance();
        if (parse_base_type()) { return true; }
        if (consume(token::right_parenthesis)) { return true; }
    }
    if (! token_.is(token::keyword_END)) {
        if (parse_field_list_sequence()) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    return false;
}