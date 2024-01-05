#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_field_list_sequence(sema::Field_List_Sequence& field_list_sequence) {
    sema::Field_List field_list { field_list_sequence.scope() };
    if (parse_field_list(field_list)) { return true; }
    while (token_.is(token::semicolon)) {
        advance();
        if (parse_field_list(field_list)) { return true; }
    }
    return false;
}