#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_field_list(lloberon::Field_List& field_list) {
    Ident_List ident_list;
    if (parse_ident_list(ident_list)) { return true; }
    if (consume(token::colon)) { return true; }
    Scope scope;
    Type type { field_list.scope() };
    if (parse_type(type)) { return true; }
    return false;
}