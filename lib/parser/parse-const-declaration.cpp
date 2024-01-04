#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_const_declaration() {
    Ident_Def ident_def;
    if (parse_ident_def(ident_def)) { return true; }
    if (consume(token::equals)) { return true; }
    if (parse_const_expression()) { return true; }
    return false;
}