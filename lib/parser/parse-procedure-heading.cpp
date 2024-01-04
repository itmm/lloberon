#include "lloberon/parser/parser.h"
#include "lloberon/ast/ident-def.h"

using namespace lloberon;

bool Parser::parse_procedure_heading() {
    if (consume(token::keyword_PROCEDURE)) { return true; }
    Ident_Def ident_def;
    if (parse_ident_def(ident_def)) { return true; }
    if (parse_formal_parameters()) { return true; }
    return false;
}