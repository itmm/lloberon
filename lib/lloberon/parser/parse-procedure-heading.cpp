#include "parser/parser.h"

bool Parser::parse_procedure_heading(
	sema::Procedure_Declaration& procedure_declaration
) {
	if (consume(token::keyword_PROCEDURE)) { return true; }
	if (parse_ident_def(procedure_declaration.name)) { return true; }
	if (parse_formal_parameters(procedure_declaration.procedure_type)) {
		return true;
	}
	procedure_declaration.procedure->type =
		procedure_declaration.procedure_type.procedure;
	return false;
}