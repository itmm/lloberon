#include "parser/parser.h"

bool Parser::parse_variable_declaration(lloberon::sema::Var_Declaration& var_declaration) {
    lloberon::sema::Ident_List ident_list;
    if (parse_ident_list(ident_list)) { return true; }
    if (consume(token::colon)) { return true; }
    lloberon::sema::Type type { var_declaration.scope() };
    if (parse_type(type)) { return true; }
    return false;
}