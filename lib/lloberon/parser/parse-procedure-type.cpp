#include "parser/parser.h"

bool Parser::parse_procedure_type(sema::Type& type) {
	sema::Procedure_Type procedure_type;
	if (consume(token::keyword_PROCEDURE)) { return true; }
	if (parse_formal_parameters(procedure_type)) { return true; }
	type.type = procedure_type.procedure;
	return false;
}