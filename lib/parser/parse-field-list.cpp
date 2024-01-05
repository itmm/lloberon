#include "parser/parser.h"

bool Parser::parse_field_list(lloberon::sema::Field_List& field_list) {
    lloberon::sema::Ident_List ident_list;
    if (parse_ident_list(ident_list)) { return true; }
    if (consume(token::colon)) { return true; }
    Scope scope;
    lloberon::sema::Type type { field_list.scope() };
    if (parse_type(type)) { return true; }
    return false;
}