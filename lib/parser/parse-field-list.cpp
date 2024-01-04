#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_field_list() {
    Ident_List ident_list;
    if (parse_ident_list(ident_list)) { return true; }
    if (consume(token::colon)) { return true; }
    if (parse_type()) { return true; }
    return false;
}