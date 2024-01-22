#include "parser/parser.h"

void Parser::parse_procedure_heading(
	sema::Procedure_Declaration& procedure_declaration
) {
	consume(token::keyword_PROCEDURE);
	parse_ident_def(procedure_declaration.name);
	parse_formal_parameters(procedure_declaration.procedure_type);
	procedure_declaration.procedure->type =
		procedure_declaration.procedure_type;
}