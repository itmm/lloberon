#include "parser/parser.h"
#include "sema/ident-def.h"

bool Parser::parse_procedure_heading(lloberon::sema::Procedure_Heading& procedure_heading) {
    if (consume(token::keyword_PROCEDURE)) { return true; }
    lloberon::sema::Ident_Def ident_def;
    if (parse_ident_def(ident_def)) { return true; }
    lloberon::sema::Formal_Parameters formal_parameters { procedure_heading.scope() };
    if (parse_formal_parameters(formal_parameters)) { return true; }
    return false;
}