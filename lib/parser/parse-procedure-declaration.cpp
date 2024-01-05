#include "parser/parser.h"

using namespace lloberon;

bool Parser::parse_procedure_declaration(sema::Procedure_Declaration& procedure_declaration) {
    sema::Procedure_Heading procedure_heading { procedure_declaration.scope() };
    if (parse_procedure_heading(procedure_heading)) { return true; }
    if (consume(token::semicolon)) { return true; }
    sema::Procedure_Body procedure_body { procedure_declaration.scope() };
    if (parse_procedure_body(procedure_body)) { return true; }
    if (expect(token::identifier)) { return true; }
    advance();
    return false;
}