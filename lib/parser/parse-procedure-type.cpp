#include "parser/parser.h"

bool Parser::parse_procedure_type(lloberon::sema::Procedure_Type& procedure_type) {
    if (consume(token::keyword_PROCEDURE)) { return true; }
    lloberon::sema::Formal_Parameters formal_parameters { procedure_type.scope() };
    if (parse_formal_parameters(formal_parameters)) { return true; }
    return false;
}