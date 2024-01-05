#include "parser/parser.h"

bool Parser::parse_const_declaration() {
    lloberon::sema::Ident_Def ident_def;
    if (parse_ident_def(ident_def)) { return true; }
    if (consume(token::equals)) { return true; }
    if (parse_const_expression()) { return true; }
    return false;
}