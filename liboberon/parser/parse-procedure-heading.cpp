#include "parser/parser.h"

void Parser::parse_procedure_heading(
	sema::Procedure_Declaration& procedure_declaration
) {
	consume(token::keyword_PROCEDURE);
	procedure_declaration.name = parse_ident_def();
	parse_formal_parameters(*procedure_declaration.procedure);
}