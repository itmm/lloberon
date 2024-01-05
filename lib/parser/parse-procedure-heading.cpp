#include "lloberon/parser/parser.h"
#include "lloberon/sema/ident-def.h"

using namespace lloberon;

bool Parser::parse_procedure_heading(sema::Procedure_Heading& procedure_heading) {
    if (consume(token::keyword_PROCEDURE)) { return true; }
    sema::Ident_Def ident_def;
    if (parse_ident_def(ident_def)) { return true; }
    sema::Formal_Parameters formal_parameters { procedure_heading.scope() };
    if (parse_formal_parameters(formal_parameters)) { return true; }
    return false;
}