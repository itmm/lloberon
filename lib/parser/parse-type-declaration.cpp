#include "parser/parser.h"

bool Parser::parse_type_declaration(sema::Type_Declaration& type_declaration) {
    sema::Ident_Def ident_def;
    if (parse_ident_def(ident_def)) { return true; }
    if (consume(token::equals)) { return true; }
    sema::Type type { type_declaration.scope() };
    if (parse_type(type)) { return true; }
    return false;
}