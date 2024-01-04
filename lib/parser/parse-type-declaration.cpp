#include "lloberon/parser/parser.h"

using namespace lloberon;

bool Parser::parse_type_declaration(sema::Type_Declaration& type_declaration) {
    Ident_Def ident_def;
    if (parse_ident_def(ident_def)) { return true; }
    if (consume(token::equals)) { return true; }
    Type type { type_declaration.scope() };
    if (parse_type(type)) { return true; }
    return false;
}