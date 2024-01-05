#include "parser/parser.h"

bool Parser::parse_record_type(lloberon::sema::Record_Type& record_type) {
    if (consume(token::keyword_RECORD)) { return true; }
    if (token_.is(token::left_parenthesis)) {
        advance();
        sema::Base_Type base_type { record_type.scope() };
        if (parse_base_type(base_type)) { return true; }
        if (consume(token::right_parenthesis)) { return true; }
    }
    if (! token_.is(token::keyword_END)) {
        lloberon::sema::Field_List_Sequence field_list_sequence { record_type.scope() };
        if (parse_field_list_sequence(field_list_sequence)) { return true; }
    }
    if (consume(token::keyword_END)) { return true; }
    return false;
}